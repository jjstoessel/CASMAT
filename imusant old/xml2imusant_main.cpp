#include <iostream>

#include "boost/filesystem/operations.hpp"
#include "boost/filesystem/path.hpp"
#include "boost/filesystem/convenience.hpp"

//#include <libmusicxml2/xmlfile.h>
#include "IMUSANT_XMLFile.h"
//#include "TXML2IMUSANTVisitor.h"
#include "xml2imusantvisitor.h"
#include "IMUSANT_XMLVisitor.h"
#include "IMUSANT_XMLReader.h"

#include "TScore.h"

#define __DEBUG__ 1

using namespace boost;
using namespace std;
using namespace IMUSANT;

extern int convert(filesystem::path& p);

int main (int argc, char * const argv[]) 
{
	
	filesystem::path full_path(filesystem::initial_path());
	
	if (argc != 2) {
		cerr << "/nusage:imusant <xml file>" << endl;
		return 1;
	}
	else
		full_path = filesystem::system_complete( filesystem::path(argv[1]) );
	
	if (!filesystem::exists( full_path ))
	{
		cerr << full_path << " not found." << endl;
		return 1;
	}
	
	if (filesystem::is_directory( full_path ) )
	{
        filesystem::directory_iterator end;
		for (	filesystem::directory_iterator iter(full_path);
				iter != end;
				++iter )
		{
			try
			{
				if (!filesystem::is_directory(*iter))
				{
					if (*iter!=0) return 1;
				}
			}
			
			catch (const runtime_error& ex)
			{
				cerr << ((filesystem::path)*iter).leaf() << " " << ex.what() << endl;
			}
		}
	}
	else //is file
		return convert(full_path);
	
	return 0;

}

int convert(filesystem::path& p)
{
	xml2imusantvisitor c;
    TMusicXMLFile reader;
	string xml(".xml"), imusant(".ims");
	
	//check extension
	if (filesystem::extension(p)==xml)
	{
		SScore score = reader.read((string&)p);
		if (score == NULL) {
			cerr << "Parse error";
			return 0;
		}
		score->accept(c);
		
		filesystem::path new_path = filesystem::change_extension(p, imusant);
		
		//confirm overwrite?
		
		IMUSANT_XMLFile ixml;
#if __DEBUG__
		ixml.write(c.getIMUSANTScore(),cout); //write to standard io
#endif
		ixml.write(c.getIMUSANTScore(),(string&)new_path); //write to file
#if __DEBUG__
		ixml.write(ixml.read(new_path.native_file_string()),cout); //reader file to io
#endif
	}

	return 0;
}
