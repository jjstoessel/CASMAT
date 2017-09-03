/*
 *  IMUSANT_processing.cpp
 *  imusant
 *
 *  Created by Jason Stoessel on 26/07/06.
 *  Copyright 2006. All rights reserved.
 *
 */
#include <iostream>
#include <fstream>
#include <deque>
#include <utility>
#include <exception>

#include "boost/filesystem/path.hpp"
#include "boost/filesystem/operations.hpp"
#include "boost/filesystem/convenience.hpp"
#include "boost/multi_array.hpp"

#include "IMUSANT_processing.h"

#include "suffixtree.h"
#include "iterator.h"
#include "repeats.h"

// MusicXML2

#include "elements/xml.h"
#include "parser/reader.h"
#include "files/xmlfile.h"
#include "files/xmlreader.h"
#include "elements/xml_tree_browser.h"

#include "IMUSANT_mxmlv3_to_imusant_visitor.h"


using namespace std;
using namespace ns_suffixtree;
using namespace boost;



namespace IMUSANT
{
    
    typedef boost::multi_array<int, 2> int_2d_array_t;
    
    void
    IMUSANT_processing::
    processDirectoryFiles(const filesystem::path& full_path)
    {
        string xml_extn = ".xml";
        
        if (filesystem::is_directory( full_path ) )
        {
            filesystem::directory_iterator end;
            for (filesystem::directory_iterator iter(full_path);
                 iter != end;
                 ++iter )
            {
                filesystem::path extn = iter->path().extension();
                
                if (extn.compare(xml_extn) == 0)
                {
                    try
                    {
                        addFile(*iter);
                    }
                    catch (std::exception& e)
                    {
                        cerr << "Error Adding file to processor.  Skipping " << *iter << endl
                             << "Exception: " << e.what() << endl;
                    }
                }
            }
        }
    }
    
    S_IMUSANT_score
    IMUSANT_processing::
    addFile(const filesystem::path& path)
    {
        // Previously we supported MusicXML v1 and there has been talk of other file formats.
        // This method is stricty redundant at the moment, but when we use new formats, this is
        // where to hook them in.
        
        IMUSANT_processing::music_file_format file_format;
        file_format = decideFileType(path);
        
        S_IMUSANT_score ret_val;
        MusicXML1FormatException mxml1ex;
        MusicXML2FormatException mxml2ex;
        UnknownFormatException uknownex;
        
        switch (file_format)
        {
            case musicxml1:
                throw mxml1ex;
                break;
                
            case musicxml2:
                throw mxml2ex;
                break;
                
            case musicxml3:
                ret_val = processMusicxml3File(path);
                break;
                
            case unknown:
                throw uknownex;
                break;
                
            default:
                throw uknownex;
                break;
                
        }
        
        createCollectionVisitorForScore(ret_val);
        scores.push_back(ret_val);
        
        return ret_val;
    }
    
    void
    IMUSANT_processing::
    createCollectionVisitorForScore(const S_IMUSANT_score score)
    {
        collection_visitors[score].ignoreRepeatedPitches(false);
        score->accept(collection_visitors[score]);
    }
    
    vector<string>
    IMUSANT_processing::
    listWorksAndMovements()
    {
        vector<string> ret_val;
        
        if (scores.size()>0)
        {
            IMUSANT_collection_visitor next;
            string work_title;
            string mvt_title;
            string work_and_mvt_title;
            
            for (auto j = scores.begin(); j != scores.end();  j++)
            {
                mvt_title = (*j)->getMovementTitle().empty() ? "?" : (*j)->getMovementTitle()  ;
                work_title = (*j)->getWorkTitle().empty() ? "?" : (*j)->getWorkTitle()  ;
                work_and_mvt_title  = "WORK: " + work_title + "      MOVEMENT: " + mvt_title;
                
                ret_val.push_back(work_and_mvt_title);
            }
        }
        return ret_val;
    }
    
    IMUSANT_processing::music_file_format
    IMUSANT_processing::
    decideFileType(const filesystem::path& path)
    {
        IMUSANT_processing::music_file_format return_val = unknown;
        
        filesystem::file_status status = filesystem::status(path);
        if (!filesystem::exists(status)
            ||
            !filesystem::is_regular_file(status))
        {
            cerr << "Problem with the file " << path.leaf() << ".  Status is " << &status << endl;;
            cerr << "Path is: " << path << endl;
            return_val = unknown;
        }
        
        try
        {
            ifstream music_file;
            music_file.open(path.generic_string());
            
            const string xml_1_0 = "DTD MusicXML 1.0";
            const string xml_1_1 = "DTD MusicXML 1.1";
            const string xml_2 = "DTD MusicXML 2.0";
            const string xml_3 = "DTD MusicXML 3.0";
            
            bool found = false;
            string next_line;
            
            while (!music_file.eof() && !found)
            {
                getline(music_file, next_line);
                
                if (next_line.find(xml_1_0) != string::npos)
                {
                    found = true;
                    return_val = musicxml1;
                }
                else if (next_line.find(xml_1_1) != string::npos)
                {
                    found = true;
                    return_val = musicxml1;
                }
                else if (next_line.find(xml_2) != string::npos)
                {
                    found = true;
                    return_val = musicxml2;
                }
                else if (next_line.find(xml_3) != string::npos)
                {
                    found = true;
                    return_val = musicxml3;
                }
            }
            
            music_file.close();
            
        }
        catch (std::exception& e)
        {
            cerr << "exception occurred " << e.what() << endl;
            throw e;
        }
        
        return return_val;
    }
    
    S_IMUSANT_score
    IMUSANT_processing::
    processMusicxml3File(const filesystem::path& path)
    {
        string file_path = path.generic_string();
        // cout << "IMUSANT_processing::process_musicxml3_file() - File: " << file_path << endl;
        
        MusicXML2::xmlreader r;
        MusicXML2::SXMLFile sxml_file = r.read(file_path.c_str());
        
        MusicXML2::Sxmlelement sxml_element;
        if (sxml_file)
        {
            sxml_element = sxml_file->elements();
            
            string element_name = sxml_element->getName();
            //  cout << "IMUSANT_processing::process_musicxml3_file() - Element Name: " << element_name << endl;
        }
        
        IMUSANT_mxmlv3_to_imusant_visitor parser;
        if (sxml_element)
        {
            tree_browser<MusicXML2::xmlelement> browser(&parser);
            browser.browse(*sxml_element);
        }
        
        return parser.get_imusant_score();
    }

} //namespace IMUSANT
