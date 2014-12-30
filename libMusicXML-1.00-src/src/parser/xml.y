%{
/* 
	Basic xml grammar definition
	This is a basic definition of the xml grammar necessary to cover 
	the MusicXML format. It is a simplified form based on the XML document
	grammar as defined in 
	"XML in a nutshell - 2nd edition" E.R.Harold and W.S.Means,
	O'Reilly, June 2002, pp:366--371
*/


#include <stdio.h>
#include <string.h>
#include <string>
#include <iostream>
#include "reader.h"

using namespace std;

int yyline = 1;

#ifdef __cplusplus
extern "C" {
#endif
int		yyparse (void);
void	yyerror(char *s);
int		yywrap();
bool	readfile (const char * file, reader * r);
#ifdef __cplusplus
}
#endif

int	 yylex (void);
void lexinit(void);

extern char * yytext;
extern int yylineno;
extern FILE * yyin;

#define ERROR(str)	{ yyerror(str); YYABORT; }
#define MAXLEN	1024
#define VLEN	256
char attributeName[MAXLEN];
char attributeVal[MAXLEN];

char xmlversion[VLEN];
char xmlencoding[MAXLEN];
int xmlStandalone = -1;

char eltName[MAXLEN];
char doctypeStart[MAXLEN];
char doctypePub[MAXLEN];
char doctypeSys[MAXLEN];

reader * gReader;

static void init (reader * r) {
	gReader = r;
	xmlStandalone = -1;
	eltName[0]		= 0;
	attributeName[0] = 0;
	attributeVal[0] = 0;
	xmlversion[0]   = 0;
	xmlencoding[0]  = 0;
	doctypeStart[0]	= 0;
	doctypePub[0]	= 0;
	doctypeSys[0]	= 0;
}

static char * unquote (char * text) {
	int n = strlen(text);
	if (n > 0) {
		text[n-1]=0;
		return &text[1];
	}
	return text;
}

static void store (char * dst, const char * text) {
	strcpy (dst, text);
}

%}


%start document

%token XMLDECL VERSION ENCODING STANDALONE YES NO ENDXMLDECL
%token DOCTYPE PUBLIC SYSTEM
%token NAME DATA QUOTEDSTR SPACE
%token LT GT ENDXMLS ENDXMLE EQ


%%      				/* beginning of rules section */


document	: prolog element misc ;

prolog		: xmldecl doctype;

element		: eltstart data eltstop
			| emptyelt ;

eltstart	: LT eltname GT
			| LT eltname SPACE attributes GT ;

eltstop		: ENDXMLS endname GT;

emptyelt	: LT eltname ENDXMLE					{ if (!gReader->endElement(eltName)) ERROR("end element error") }
			| LT eltname SPACE attributes ENDXMLE   { if (!gReader->endElement(eltName)) ERROR("end element error") }

eltname		: NAME							{ store(eltName, yytext); if (!gReader->newElement(yytext)) ERROR("element error") }
endname		: NAME							{ if (!gReader->endElement(yytext)) ERROR("end element error") }

attribute	: attrname EQ value			{ if (!gReader->newAttribute (attributeName, attributeVal)) ERROR("attribute error") }
attrname	: NAME							{ store(attributeName, yytext); }
value		: QUOTEDSTR					{ store(attributeVal, unquote(yytext)); }

attributes  : attribute	
			| attributes SPACE attribute;

data		: /* empty */
			| cdata
			| elements ;

cdata		: DATA							{ gReader->setValue (yytext); }

elements	: element
			| elements element;


xmldecl		: /* empty */
			| XMLDECL versiondec decl ENDXMLDECL { if (!gReader->xmlDecl (xmlversion, xmlencoding, xmlStandalone)) ERROR("xmlDecl error") }

decl		: /* empty */
			| encodingdec 
			| stdalonedec
			| encodingdec stdalonedec ;

versiondec	: SPACE VERSION EQ QUOTEDSTR 		{ store(xmlversion, unquote(yytext)); }
encodingdec	: SPACE ENCODING EQ QUOTEDSTR 		{ store(xmlencoding, unquote(yytext)); }
stdalonedec	: SPACE STANDALONE EQ bool  		{ xmlStandalone = yylval; }
bool		: YES | NO ;

doctype		: DOCTYPE SPACE startname SPACE id GT
startname	: NAME 							{ store(doctypeStart, yytext); }
id			: PUBLIC SPACE publitteral SPACE syslitteral	{ gReader->docType (doctypeStart, true, doctypePub, doctypeSys); }
			| SYSTEM SPACE syslitteral						{ gReader->docType (doctypeStart, false, doctypePub, doctypeSys); }
publitteral : QUOTEDSTR 						{ store(doctypePub, unquote(yytext)); }
syslitteral : QUOTEDSTR 						{ store(doctypeSys, unquote(yytext)); }

misc		: /* empty */
			| SPACE ;


%%

bool readfile (const char * file, reader * r) 
{
	FILE * fd = fopen (file, "r");
	int ret;
	if (!fd) {
		r->error ("can't open file", 0);
		return false;
	}
	lexinit();
	init(r);
	yyin = fd;
 	ret = yyparse();
 	fclose (fd);
 	return ret==0;
}

void	yyerror(char *s)	{ gReader->error (s, yylineno); }
int		yywrap()			{ return(1); }

#ifdef MAIN

class testreader : public reader
{ 
	public:
		bool	xmlDecl (const char* version, const char *encoding, bool standalone) {
			cout << "xmlDecl: " << version << " " << encoding << " " << standalone << endl;
			return true;
		}
		bool	docType (const char* start, bool status, const char *pub, const char *sys) {
			cout << "docType: " << start << " " << (status ? "PUBLIC" : "SYSTEM") << " " << pub << " " << sys << endl;
			return true;
		}

		bool	newElement (const char* eltName) {
			cout << "newElement: " << eltName << endl;
			return true;
		}
		bool	newAttribute (const char* eltName, const char *val) {
			cout << "    newAttribute: " << eltName << "=" << val << endl;
			return true;
		}
		void	setValue (const char* value) {
			cout << "  -> value: " << value << endl;
		}
		bool	endElement (const char* eltName) {
			cout << "endElement: " << eltName << endl;
			return true;
		}
		void	error (const char* s, int lineno) {
			cerr << s  << " on line " << lineno << endl;
		}

};


int main (int argc, char * argv[])
{
	if (argc > 1) {
		testreader r;
		return readfile (argv[1], &r) ? 0 : 1;
	}
 	return 0;
}
#endif
