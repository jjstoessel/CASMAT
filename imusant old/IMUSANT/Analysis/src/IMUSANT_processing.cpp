/*
 *  IMUSANT_processing.cpp
 *  imusant
 *
 *  Created by Jason Stoessel on 26/07/06.
 *  Copyright 2006. All rights reserved.
 *
 */
#include <iostream>
#include <deque>
#include <utility>
#include <exception>

#include "boost/filesystem/path.hpp"
#include "boost/filesystem/operations.hpp"
#include "boost/filesystem/convenience.hpp"
#include "boost/multi_array.hpp"

#include "IMUSANT_processing.h"
#include "TMusicXMLFile.h"
#include "IMUSANT_XMLFile.h"
#include "TXML2IMUSANTVisitor.h"
#include "IMUSANT_XMLVisitor.h"
#include "IMUSANT_XMLReader.h"
#include "TScore.h"
#include "suffixtree.h"
#include "iterator.h"
#include "repeats.h"

// MusicXML2

#include "elements/xml.h"
#include "parser/reader.h"
#include "files/xmlfile.h"
#include "files/xmlreader.h"
#include "elements/xml_tree_browser.h"
// #include "elements/unrolled_xml_tree_browser.h"

#include "IMUSANT_mxmlv3_to_imusant_visitor.h"


#define MAX(X,Y) ( (X>Y)? (X) : (Y) )


using namespace std;
using namespace ns_suffixtree;
using namespace boost;



namespace IMUSANT
{
    
    typedef suffixtree< vector<IMUSANT_contour_symbol> > contour_tree;
    typedef boost::multi_array<int, 2> int_2d_array_t;
    
    void
    IMUSANT_processing::
    process_directory_files(const filesystem::path& full_path)
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
                    add_file(*iter);
                }
            }
        }
    }
    
    void
    IMUSANT_processing::
    add_file(const filesystem::path& path)
    {
        // All the IMUSANT objects (such as IMUSANT_interval) inherit from SMARTTABLE or use SMARTP which are MusicXML v1 objects.
        // Not sure that this is a problem at this point, but something to be aware of.
        
        IMUSANT_processing::music_file_format file_format;
        file_format = decide_file_type(path);
        
        switch (file_format)
        {
            case musicxml1:
                process_musicxml1_file(path);
                break;
                
            case musicxml3:
                process_musicxml3_file(path);
                break;
                
            case imusant:
                process_imusant_file(path);
                break;
                
            case unknown:
                break;
                
            default:
                break;
                
        }
    }
    
    IMUSANT_processing::music_file_format
    IMUSANT_processing::
    decide_file_type(const filesystem::path& path)
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
        }
        
        return return_val;
    }
    
    
    S_IMUSANT_score
    IMUSANT_processing::
    process_musicxml1_file(const filesystem::path& path)
    {
        // This is a IMUSANT object which derives from a MusicXML v1 object.
        TXML2IMUSANTVisitor c;
        
        // This is a MusicXML v1 object.
        MusicXML::TMusicXMLFile reader;
        
        //convert first
        SScore score = reader.read((string&)path);  // This is a MusicXML v1 object.
        if (score == NULL)
        {
            cerr << "Parse error in " << path.leaf() << endl;
            throw "Parse error";
        }
        
        //ensure unique ID
        int i = 1;
        while (find(IDs.begin(), IDs.end(), i)!=IDs.end()) i++;
        
        //error checking required!
        score->accept(c);
        processed_files[i].ignoreRepeatedPitches(false);
        c.get_imusant_score()->accept(processed_files[i]);
        
        IDs.push_back(i);
        
        return c.get_imusant_score();
    }
    
    S_IMUSANT_score
    IMUSANT_processing::
    process_musicxml3_file(const filesystem::path& path)
    {
        string file_path = path.generic_string();
        
        MusicXML2::xmlreader r;
        MusicXML2::SXMLFile sxml_file = r.read(file_path.c_str());

        MusicXML2::Sxmlelement sxml_element;
        if (sxml_file)
        {
            sxml_element = sxml_file->elements();
            
//            string element_name = sxml_element->getName();
//            cout << "Element Name: " << element_name << endl;
        }
        
        IMUSANT_mxmlv3_to_imusant_visitor parser;
        if (sxml_element)
        {
            tree_browser<MusicXML2::xmlelement> browser(&parser);
            browser.browse(*sxml_element);
        }
        
        return parser.get_imusant_score();
    }
    
    bool
    IMUSANT_processing::
    process_imusant_file(const filesystem::path& path)
    {
        // TODO - this doesn't do anything at the moment...
        
        filesystem::path mutable_path = path;
        IMUSANT_XMLFile ixml;
        ixml.read((string&)mutable_path); //reader file
        //verify, catalogue to default directory
        
        return false;
    }
    
    string
    IMUSANT_processing::find_and_print_repeated_interval_substrings(int min_length)
    {
        vector<IMUSANT_repeated_interval_substring> the_result;
        the_result = find_repeated_interval_substrings(min_length);
        
        stringstream the_result_as_stringstream;
        for(int index = 0 ; index < the_result.size(); index++)
        {
            the_result_as_stringstream << the_result[index];
        }
        
        the_result_as_stringstream << endl;
        
        return the_result_as_stringstream.str();
    }
    
    vector<IMUSANT_repeated_interval_substring>
    IMUSANT_processing::
    find_repeated_interval_substrings(int min_length)
    {
        vector<IMUSANT_repeated_interval_substring> ret_val;
        
        if (IDs.size()<=0)  // No fies have been added...
        {
            return ret_val;
        }
        
        interval_tree tree = build_suffix_tree();
        
        vector< pair<vector<interval_tree::number>, int> > common_substrings;
        common_substrings = tree.find_common_subsequences(IDs, min_length);
        
        vector< pair<vector<interval_tree::number>, int> >::iterator common_substrings_iter;
        for (common_substrings_iter = common_substrings.begin();
             common_substrings_iter != common_substrings.end();
             common_substrings_iter++)
        {
            IMUSANT_repeated_interval_substring repeated_interval_substring;
            
            vector< interval_tree::number >::const_iterator substring_iter;
            bool int_sequence_added_to_ret_value = false;
            
            for (substring_iter = common_substrings_iter->first.begin();
                 substring_iter != common_substrings_iter->first.end();
                 substring_iter++)
            {
                IMUSANT_collection_visitor movement = processed_files[substring_iter->first];
                vector<IMUSANT_interval> intervals = movement.getIntervalVector()->getIntervals();
                
                if (! int_sequence_added_to_ret_value)
                {
                    // Add the interval sequence into the return value.
                    for (interval_tree::size_type t = substring_iter->second;
                         t < substring_iter->second + common_substrings_iter->second;
                         t++)
                    {
                        repeated_interval_substring.interval_sequence->add(intervals[t]);
                    }
                    int_sequence_added_to_ret_value = true;
                }
                
                // Add the loction of this repetition of the interval sequence into the return value.
                IMUSANT_interval interval = intervals[substring_iter->second];
                IMUSANT_range range = interval.getLocation();
                repeated_interval_substring.add_occurrence(substring_iter->first,
                                                           range.partID,
                                                           range.first.measure,
                                                           range.first.note_index );
            }
            
            ret_val.push_back(repeated_interval_substring);
            
        }
        return ret_val;
    }
    
    
    IMUSANT_processing::interval_tree
    IMUSANT_processing::
    build_suffix_tree()
    {
        vector<IMUSANT_interval> intervals_from_next_processed_file;
        intervals_from_next_processed_file = processed_files[*IDs.begin()].getIntervalVector()->getIntervals();
        
        interval_tree tree(intervals_from_next_processed_file,*IDs.begin());
        
        for (vector<int>::iterator j = IDs.begin()+1; j!=IDs.end(); j++)
        {
            intervals_from_next_processed_file = processed_files[*j].getIntervalVector()->getIntervals();
            tree.add_sentence(intervals_from_next_processed_file, *j);
        }
        return tree;
    }
    
    void
    IMUSANT_processing::find_repeated_contour_substrings(int min_length)
    {
        if (IDs.size()>0)
        {
            //construct contour tree
            contour_tree cont_tree(*(processed_files[*IDs.begin()].getMelodicContour()),*IDs.begin());
            
            for (vector<int>::iterator j = IDs.begin()+1; j!=IDs.end(); j++)
            {
                cont_tree.add_sentence(*(processed_files[*j].getMelodicContour()),*j);
            }
            
            vector< pair<vector<contour_tree::number>, int> > mc_results;
            mc_results = cont_tree.find_common_subsequences(IDs,min_length);
            cout << "Melodic contour tree created."<< endl;
            cout << "Found common contour subsequences of " << min_length << " or more elements at: " << endl;
            vector< pair<vector<contour_tree::number>, int> >::iterator iter_mc=mc_results.begin();
            for (;iter_mc!=mc_results.end(); iter_mc++)
            {
                
                cout << "Instance: ";
                vector< contour_tree::number >::const_iterator mc_c=iter_mc->first.begin();
                bool first_time = true;
                for (;mc_c!=iter_mc->first.end(); mc_c++)
                {
                    IMUSANT_contour_symbol symbol = (*(processed_files[mc_c->first].getMelodicContour()))[mc_c->second];
                    if (first_time)
                    {
                        for (contour_tree::size_type t = mc_c->second; t < mc_c->second+iter_mc->second; t++)
                        {
                            cout << (*(processed_files[mc_c->first].getMelodicContour()))[t] << " ";
                        }
                        first_time=false;
                    }
                    IMUSANT_range range=symbol.getLocation();
                    cout << "(" << mc_c->first << "," <<range.partID << "," << range.first.measure << "," << range.first.note_index << ")";
                }
                
                cout << endl;
                cout << "Length: " << iter_mc->second << " Occurrences: " << iter_mc->first.size() << endl << endl;
            }
            cout << endl;
            
        }
    }
    
    void IMUSANT_processing::find_supermaximals_intervals(int min_length, int min_percent)
    {
        if (IDs.size()>0)
        {
            interval_tree tree(processed_files[*IDs.begin()].getIntervalVector()->getIntervals(),*IDs.begin());
            
            for (vector<int>::iterator j = IDs.begin()+1; j!=IDs.end(); j++)
            {
                tree.add_sentence(processed_files[*j].getIntervalVector()->getIntervals(),*j);
            }
            
            repeats<vector<IMUSANT_interval> > rep(&tree);
            list<repeats<vector<IMUSANT_interval> >::supermax_node*> supermaxs = rep.supermax_find(min_percent, min_length);
            list<repeats<vector<IMUSANT_interval> >::supermax_node*>::const_iterator q=supermaxs.begin();
            for (; q!=supermaxs.end(); q++)
            {
                for (repeats<vector<IMUSANT_interval> >::index t = (*q)->begin_i; t!=(*q)->end_i; t++)
                {
                    cout << *t;
                }
                cout << " ";
                cout << "Witnesses: " << (*q)->num_witness << " number of leaves: " << (*q)->num_leaves << " Percent: " << (*q)->percent << endl;
            }
        }
    }
    
    void IMUSANT_processing::find_supermaximals_contours(int min_length, int min_percent)
    {
        if (IDs.size()>0)
        {
            contour_tree cont_tree(*(processed_files[*IDs.begin()].getMelodicContour()),*IDs.begin());
            
            for (vector<int>::iterator j = IDs.begin()+1; j!=IDs.end(); j++)
            {
                cont_tree.add_sentence(*(processed_files[*j].getMelodicContour()),*j);
            }
            
            repeats<vector<IMUSANT_contour_symbol> > rep(&cont_tree);
            list<repeats<vector<IMUSANT_contour_symbol> >::supermax_node*> supermaxs = rep.supermax_find(min_percent, min_length);
            list<repeats<vector<IMUSANT_contour_symbol> >::supermax_node*>::const_iterator q=supermaxs.begin();
            for (; q!=supermaxs.end(); q++)
            {
                for (repeats<vector<IMUSANT_contour_symbol> >::index t = (*q)->begin_i; t!=(*q)->end_i; t++)
                {
                    cout << *t;
                }
                cout << " ";
                cout << "Witnesses: " << (*q)->num_witness << " number of leaves: " << (*q)->num_leaves << " Percent: " << (*q)->percent << endl;
            }
        }
    }
    
    // Find longest common subsequence of intervals for pairs of file/works
    // This example of dynamic programming is adapted from Crochemore and Lecroq,
    // Pattern MAtching and text compression algorithms, available from:
    // http://www-igm.univ-mlv.fr/~mac/REC/DOC/03-CRC.ps
    
    void IMUSANT_processing::find_lcs_pairs_intervals(bool consecutive)
    {
        if (IDs.size()>1)
        {
            for (vector<int>::iterator IDiter1=IDs.begin(); IDiter1!=IDs.end(); IDiter1++)
            {
                vector<IMUSANT_interval> x = processed_files[*IDiter1].getIntervalVector()->getIntervals();
                int m = x.size();
                
                for (vector<int>::iterator IDiter2=IDiter1+1; IDiter2!=IDs.end(); IDiter2++)
                {
                    
                    cout << "Longest common subsequence of " << processed_files[*IDiter1].getMovementTitle() << " with "
                    << processed_files[*IDiter2].getMovementTitle() << endl;
                    
                    vector<IMUSANT_interval> y = processed_files[*IDiter2].getIntervalVector()->getIntervals();
                    int i, j;
                    int n = y.size();
                    int_2d_array_t lcs(boost::extents[m][n]); //ints auto zeroed
                    
                    
                    for (i=0; i < m-1; i++)
                    {
                        for (j=0; j<n-1; j++)
                        {
                            if (x[i]==y[j])
                            {
                                lcs[i+1][j+1]=lcs[i][j]+1;
                            }
                            else
                            {
                                lcs[i+1][j+1]=MAX(lcs[i+1][j],lcs[i][j+1]);
                            }
                        }
                    }
                    
                    //now trace back to find lcs
                    //i--;
                    //j--;
                    deque<pair<IMUSANT_interval,IMUSANT_interval> > z;
                    while (i > 0 && j > 0)
                    {
                        if(lcs[i][j]==lcs[i-1][j-1]+1 && x[i-1]==y[j-1])
                        {
                            z.push_front(make_pair<IMUSANT_interval,IMUSANT_interval>(x[i-1],y[j-1]));
                            i--; j--;
                        }
                        else if (lcs[i-1][j] > lcs[i][j-1]) i--;
                        else j--;
                    }
                    
                    cout << "Common subsequence: " << endl;
                    for (deque<pair<IMUSANT_interval,IMUSANT_interval> >::iterator iv=z.begin(); iv!=z.end(); iv++)
                    {
                        IMUSANT_range loc1 = iv->first.getLocation();
                        IMUSANT_range loc2 = iv->second.getLocation();
                        if (consecutive)
                        {
                            if (iv+1!=z.end())
                            {
                                IMUSANT_range loc1next = (iv+1)->first.getLocation();
                                IMUSANT_range loc2next = (iv+1)->second.getLocation();
                                
                                if ((loc1.last.measure==loc1next.first.measure
                                     && loc1.last.note_index==loc1next.first.note_index)
                                    && (loc2.last.measure==loc2next.first.measure
                                        && loc2.last.note_index==loc2next.first.note_index) )
                                {
                                    cout	<< iv->first << " (" << loc1.partID << "," << loc1.first.measure << ","
                                    << loc1.first.note_index << "; " << loc2.partID << ","
                                    << loc2.first.measure << "," << loc2.first.note_index << ") " << endl;
                                }
                                else
                                {
                                    cout << "====" << endl;
                                }
                            }
                        }
                        else
                        {
                            cout	<< iv->first << " (" << loc1.partID << "," << loc1.first.measure << ","
                            << loc1.first.note_index << "; " << loc2.partID << ","
                            << loc2.first.measure << "," << loc2.first.note_index << ") " << endl ;
                        }
                    }
                    cout << endl;
                    
                }
            }
        }
    }
    
    void IMUSANT_processing::find_lcs_pairs_intervals_reverse(bool consecutive)
    {
        if (IDs.size()>1)
        {
            for (vector<int>::iterator IDiter1=IDs.begin(); IDiter1!=IDs.end(); IDiter1++)
            {
                vector<IMUSANT_interval> x = processed_files[*IDiter1].getIntervalVector()->getIntervals();
                x.pop_back();
                reverse(x.begin(), x.end()); //added routine - reverse vector
                int m = x.size();
                
                for (vector<int>::iterator IDiter2=IDiter1+1; IDiter2!=IDs.end(); IDiter2++)
                {
                    
                    cout << "Longest common subsequence of " << processed_files[*IDiter1].getMovementTitle() << " with "
                    << processed_files[*IDiter2].getMovementTitle() << endl;
                    
                    vector<IMUSANT_interval> y = processed_files[*IDiter2].getIntervalVector()->getIntervals();
                    y.pop_back();
                    reverse(y.begin(), y.end()); //added routine - reverse vector
                    int i, j;
                    int n = y.size();
                    int_2d_array_t lcs(boost::extents[m+1][n+1]); //ints auto zeroed
                    
                    //skip unique end flag, now at end
                    for (i=0; i < m; i++)
                    {
                        for (j=0; j<n; j++)
                        {
                            if (x[i]==y[j])
                            {
                                lcs[i+1][j+1]=lcs[i][j]+1;
                            }
                            else
                            {
                                lcs[i+1][j+1]=MAX(lcs[i+1][j],lcs[i][j+1]);
                            }
                        }
                    }
                    
                    //now trace back to find lcs
                    //i--;
                    //j--;
                    deque<pair<IMUSANT_interval,IMUSANT_interval> > z;
                    while (i > 1 && j > 1)
                    {
                        if(lcs[i][j]==lcs[i-1][j-1]+1 && x[i-1]==y[j-1])
                        {
                            z.push_front(make_pair<IMUSANT_interval,IMUSANT_interval>(x[i-1],y[j-1]));
                            i--; j--;
                        }
                        else if (lcs[i-1][j] > lcs[i][j-1]) i--;
                        else j--;
                    }
                    
                    reverse (z.begin(), z.end()); //added routine - reverse vector
                    cout << "Common subsequence: " << endl;
                    for (deque<pair<IMUSANT_interval,IMUSANT_interval> >::iterator iv=z.begin(); iv!=z.end(); iv++)
                    {
                        IMUSANT_range loc1 = iv->first.getLocation();
                        IMUSANT_range loc2 = iv->second.getLocation();
                        if (consecutive)
                        {
                            if (iv+1!=z.end())
                            {
                                IMUSANT_range loc1next = (iv+1)->first.getLocation();
                                IMUSANT_range loc2next = (iv+1)->second.getLocation();
                                
                                if ((loc1.last.measure==loc1next.first.measure
                                     && loc1.last.note_index==loc1next.first.note_index)
                                    && (loc2.last.measure==loc2next.first.measure
                                        && loc2.last.note_index==loc2next.first.note_index) )
                                {
                                    cout	<< iv->first << " (" << loc1.partID << "," << loc1.first.measure << ","
                                    << loc1.first.note_index << "; " << loc2.partID << ","
                                    << loc2.first.measure << "," << loc2.first.note_index << ") " << endl;
                                }
                                else
                                {
                                    cout << "====" << endl;
                                }
                            }
                        }
                        else
                        {
                            cout	<< iv->first << " (" << loc1.partID << "," << loc1.first.measure << ","
                            << loc1.first.note_index << "; " << loc2.partID << ","
                            << loc2.first.measure << "," << loc2.first.note_index << ") " << endl ;
                        }
                    }
                    cout << endl;
                    
                }
            }
        }
    }
    
    //Find longest common subsequence of pitches for pairs of file/works
    void IMUSANT_processing::find_lcs_pairs_pitches(bool consecutive)
    {
        if (IDs.size()>1)
        {
            for (vector<int>::iterator IDiter1=IDs.begin(); IDiter1!=IDs.end(); IDiter1++)
            {
                vector<IMUSANT_pitch> x = *(processed_files[*IDiter1].getPitchVector());
                int m = x.size();
                
                for (vector<int>::iterator IDiter2=IDiter1+1; IDiter2!=IDs.end(); IDiter2++)
                {
                    
                    cout << "Longest common subsequence of " << processed_files[*IDiter1].getMovementTitle() << " with "
                    << processed_files[*IDiter2].getMovementTitle() << endl;
                    
                    vector<IMUSANT_pitch> y = *(processed_files[*IDiter2].getPitchVector());
                    int i, j;
                    int n = y.size();
                    int_2d_array_t lcs(boost::extents[m][n]); //ints auto zeroed
                    
                    
                    for (i=0; i < m-1; i++)
                    {
                        for (j=0; j<n-1; j++)
                        {
                            if (x[i]==y[j])
                            {
                                lcs[i+1][j+1]=lcs[i][j]+1;
                            }
                            else
                            {
                                lcs[i+1][j+1]=MAX(lcs[i+1][j],lcs[i][j+1]);
                            }
                        }
                    }
                    
                    //now trace back to find lcs
                    //i--;
                    //j--;
                    deque<pair<IMUSANT_pitch,IMUSANT_pitch> > z;
                    while (i > 0 && j > 0)
                    {
                        if(lcs[i][j]==lcs[i-1][j-1]+1 && x[i-1]==y[j-1])
                        {
                            z.push_front(make_pair<IMUSANT_pitch,IMUSANT_pitch>(x[i-1],y[j-1]));
                            i--; j--;
                        }
                        else if (lcs[i-1][j] > lcs[i][j-1]) i--;
                        else j--;
                    }
                    
                    cout << "Common subsequence: ";
                    for (deque<pair<IMUSANT_pitch,IMUSANT_pitch> >::iterator iv=z.begin(); iv!=z.end(); iv++)
                    {
                        cout << iv->first;
                    }
                    cout << endl;
                    
                }
            }
        }
    }
    
} //namespace IMUSANT