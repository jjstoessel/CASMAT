%{
 
/* 
	Basic relaxed xml lexical definition.
	This is a basic definition of the lexical elements necessary to cover 
	the MusicXML format. It is a simplified form based on the XML document
	grammar as defined in 
	"XML in a nutshell - 2nd edition" E.R.Harold and W.S.Means,
	O'Reilly, June 2002, pp:366--371
*/


#include "xmlparse.h"


extern int yylval;

#if 0
#define DEBUG(name)				printf("token %s\n", name)
#else
#define DEBUG(name)
#endif
#define TOKEN(id,name)			DEBUG(name); return id;
#define BTOKEN(id,name,sect)	DEBUG(name); BEGIN sect; return id;

static int utf16 = 0;
static int bigendian = 1;
static int start = 1;

static int wgetc(FILE * fd) {
	int c = getc(fd);
	if (start) {
		if (c == 0xff) {
			utf16 = 1; bigendian = 0;
			getc(fd); c = getc(fd);
		}
		else if (c == 0xfe) {
			utf16 = 1; bigendian = 1;
			getc(fd); c = getc(fd);
		}
		start = 0;
	}
	if (utf16) {
		if (bigendian) c = getc(fd);
		else getc(fd);
	}

	return c;
}

static size_t wfread (void * buf, size_t size, size_t nmemb, FILE * fd) {
	char * ptr = (char *)buf;
	size_t n=0;
	while (nmemb--) {
		*ptr++ = wgetc(fd);
		if (feof(fd) || ferror(fd) ) break;
		n++;
	}
	return n;
}
		 
void lexinit() {
	utf16 = 0;
	bigendian = 1;
	start = 1;
}

#define getc	wgetc
#define fread	wfread

%}

letter		[a-zA-Z]
digit		[0-9]
space		[ \t]
S			[ \t\x0a\x0d]
firstchar	[a-zA-Z_]
namechar	[-a-zA-Z0-9_.:]
anychar		[^<>]
valchar		[^<>&"]
quote		["']


%option yylineno
%S DATASECT XMLSECT DOCTYPESECT

%%


{S}*"<!--"{anychar}*"-->"		/* eat up comments */

{S}*"<?xml"						{ BTOKEN(XMLDECL,"XMLDECL",XMLSECT); }
{space}*"?>"					{ BTOKEN(ENDXMLDECL,"ENDXMLDECL",0); }
<XMLSECT>"version"				{ TOKEN(VERSION,"VERSION"); }
<XMLSECT>"encoding"				{ TOKEN(ENCODING,"ENCODING"); }
<XMLSECT>"standalone"			{ TOKEN(STANDALONE,"STANDALONE"); }
<XMLSECT>{quote}"yes"{quote}	{ yylval=1; TOKEN(YES,"YES"); }
<XMLSECT>{quote}"no"{quote}		{ yylval=0; TOKEN(NO,"NO"); }

{S}*"<!DOCTYPE"					{ BTOKEN(DOCTYPE,"DOCTYPE",DOCTYPESECT); }
<DOCTYPESECT>"PUBLIC"			{ TOKEN(PUBLIC,"PUBLIC"); }
<DOCTYPESECT>"SYSTEM"			{ TOKEN(SYSTEM,"SYSTEM"); }

{S}*"<"{space}*					{ BTOKEN(LT,"LT",0); }
{space}*">"						{ BTOKEN(GT,"GT",DATASECT); }
{space}*"="{space}*				{ TOKEN(EQ,"EQ"); }
{S}*"</"						{ BTOKEN(ENDXMLS,"ENDXMLS",0); }
{space}*"/>"					{ TOKEN(ENDXMLE,"ENDXMLE"); }

{S}+							{ TOKEN(SPACE,"SPACE"); }
<DATASECT>{anychar}+			{ TOKEN(DATA,"DATA"); }
{firstchar}{namechar}*			{ TOKEN(NAME,"NAME"); }
{quote}{valchar}*{quote}		{ TOKEN(QUOTEDSTR,"QUOTEDSTR"); }

<<EOF>>		yyterminate();
