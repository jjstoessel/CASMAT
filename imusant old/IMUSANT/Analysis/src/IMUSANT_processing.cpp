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

#include "IMUSANT_segmented_part_LBDM.h"

#include "IMUSANT_processing.h"

#include "IMUSANT_XMLReader.h"  // This brings in SMRTP from MXML v1.
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

#define MAX(X,Y) ( (X>Y)? (X) : (Y) )


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
                        cerr << "Error Adding file to processor.  Skipping " << full_path.string() << endl << "Exception :" << e.what() << endl;
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
        UnknownFormatException uknownex;
        
        switch (file_format)
        {
            case musicxml1:
                cerr << mxml1ex.what() << endl;
                throw mxml1ex;
                break;
                
            case musicxml3:
                ret_val = processMusicxml3File(path);
                break;
                
            case unknown:
                cerr << uknownex.what() << endl;
                throw uknownex;
                break;
                
            default:
                cerr << uknownex.what() << endl;
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
        //ensure unique ID
        int i = 1;
        while (find(IDs.begin(),
                    IDs.end(),
                    i) != IDs.end())
        {
            i++;
        }
        
        collection_visitors[i].ignoreRepeatedPitches(false);
        score->accept(collection_visitors[i]);
        IDs.push_back(i);
    }
    
    vector<string>
    IMUSANT_processing::
    listWorksAndMovements()
    {
        vector<string> ret_val;
        
        if (IDs.size()>0)
        {
            IMUSANT_collection_visitor next;
            string work_title;
            string mvt_title;
            string work_and_mvt_title;
            
            for (vector<int>::iterator j = IDs.begin(); j!=IDs.end(); j++)
            {
                next = collection_visitors[*j];
                mvt_title = next.getMovementTitle().empty() ? "?" : next.getMovementTitle()  ;
                work_title = next.getWorkTitle().empty() ? "?" : next.getWorkTitle()  ;
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
    
    string
    IMUSANT_processing::
    findAndPrintRepeatedIntervalSubstrings(int min_length)
    {
        //vector<IMUSANT_repeated_interval_substring> the_result;
        //the_result = findRepeatedIntervalSubstrings(min_length);
        vector<IMUSANT_t_repeated_substring<IMUSANT_interval> > the_result;
        
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
    findRepeatedIntervalSubstrings(int min_length)
    {
        vector<IMUSANT_repeated_interval_substring> ret_val;
        
        if (IDs.size()<=0)  // No files have been added...
        {
            return ret_val;
        }
        
        
        ID_ivec_map id_ivec_map;
        interval_tree* tree = buildIntervalSuffixTree(id_ivec_map);
        
#ifdef VERBOSE
        tree->print(cout);
#endif
        vector< pair<vector<interval_tree::number>, int> > common_substrings;
        
        
        //get IDS from map of ID to each interval_vector
        vector<int> local_ids;
        for (auto ivm = id_ivec_map.begin(); ivm != id_ivec_map.end(); ivm++) {
            local_ids.push_back(ivm->first);
        }
        //iterate tree for each ID
        common_substrings = tree->find_common_subsequences(local_ids, min_length);
        
        //iterate through substring results
        vector< pair<vector<interval_tree::number>, int> >::iterator common_substrings_iter;
        for (common_substrings_iter = common_substrings.begin();
             common_substrings_iter != common_substrings.end();
             common_substrings_iter++)
        {
            IMUSANT_repeated_interval_substring repeated_interval_substring;
            
            vector< interval_tree::number >::const_iterator substring_iter;
            bool int_sequence_added_to_ret_value = false;
            
            //interate through substring
            for (substring_iter = common_substrings_iter->first.begin();
                 substring_iter != common_substrings_iter->first.end();
                 substring_iter++)
            {
                vector<IMUSANT_interval> intervals = id_ivec_map[substring_iter->first];

                if (! int_sequence_added_to_ret_value)
                {
                    // Add the interval sequence into the return value.
                    for (interval_tree::size_type t = substring_iter->second;
                         t < substring_iter->second + common_substrings_iter->second;
                         t++)
                    {
                         repeated_interval_substring.sequence.push_back(intervals[t]);
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
        
        delete tree;
        
        return ret_val;
    }
    
    //Prepare list of interval strings and feed to template class to create actual tree
    IMUSANT_processing::interval_tree*
    IMUSANT_processing::
    buildIntervalSuffixTree(ID_ivec_map& id_ivec_map)
    {
        //get first part from first file
        interval_tree* tree = NULL;
        int ID = 0;
        
        for (auto i = collection_visitors.begin(); i!=collection_visitors.end(); i++)
        {
            IMUSANT_collection_visitor collection = i->second;
            for (auto j = collection.getPartwiseIntervalVectors().begin(); j!=collection.getPartwiseIntervalVectors().end(); j++)
            {
                ++ID;
                id_ivec_map[ID] = (*j)->getIntervals();
                
            }
        }
        
        tree = buildSuffixTree(id_ivec_map);
        
        return tree;
    }
    
    template<class T> suffixtree< vector<T> >*
    IMUSANT_processing::
    buildSuffixTree(const map<int, vector<T> >& id_vec_map)
    {
        //get first part from first file
        suffixtree< vector<T> >* tree = NULL;
        
        for (auto i = id_vec_map.begin(); i!=id_vec_map.end(); i++)
        {
            
            if (tree==NULL) {
                tree=new suffixtree< vector<T> >(i->second, i->first);
            }
            else
                tree->add_sentence(i->second, i->first);
        }
        
        return tree;
    }

    vector<IMUSANT_repeated_contour_substring>
    IMUSANT_processing::
    findRepeatedContourSubstrings(int min_length)
    {
        
        vector<IMUSANT_repeated_contour_substring> ret_val;
        
        if (IDs.size()>0)
        {
            ID_cvec_map id_cvec_map;
            //construct contour tree
            contour_tree* tree = buildContourSuffixTree(id_cvec_map);
            //construct contour tree
            
            vector<int> local_ids;
            for (auto cvm = id_cvec_map.begin(); cvm != id_cvec_map.end(); cvm++) {
                local_ids.push_back(cvm->first);
            }
            vector< pair<vector<contour_tree::number>, int> > mc_results;
            mc_results = tree->find_common_subsequences(local_ids, min_length);
            
            for (auto iter_mc=mc_results.begin();iter_mc!=mc_results.end(); iter_mc++)
            {
                IMUSANT_repeated_contour_substring repeated_contour_substring;
                vector< contour_tree::number >::const_iterator mc_c=iter_mc->first.begin();
                bool first_time = true;
                for (;mc_c!=iter_mc->first.end(); mc_c++)
                {
                    if (first_time)
                    {
                        for (contour_tree::size_type t = mc_c->second; t < mc_c->second+iter_mc->second; t++)
                        {
                            repeated_contour_substring.sequence.push_back(id_cvec_map[mc_c->first][t]);
                        }

                        first_time=false;
                    }
                    
                    IMUSANT_contour_symbol symbol = id_cvec_map[mc_c->first][mc_c->second];
                    IMUSANT_range range=symbol.getLocation();
                    repeated_contour_substring.add_occurrence( mc_c->first,
                                                               range.partID,
                                                               range.first.measure,
                                                               range.first.note_index );

                }
                ret_val.push_back(repeated_contour_substring);
            }
            cout << endl;
            
            delete tree;
        }
        
        return ret_val;
    }
    
    IMUSANT_processing::contour_tree*
    IMUSANT_processing::
    buildContourSuffixTree(ID_cvec_map& id_cvec_map)
    {
        //get first part from first file
        contour_tree* tree = NULL;
        int ID = 0;
        
        for (auto i = collection_visitors.begin(); i!=collection_visitors.end(); i++)
        {
            IMUSANT_collection_visitor collection = i->second;
            for (auto j = collection.getPartwiseContourVectors().begin(); j!=collection.getPartwiseContourVectors().end(); j++)
            {
                ++ID;
                id_cvec_map[ID] = (*j)->getContours();
            }
        }
        
        tree = buildSuffixTree(id_cvec_map);
        
        return tree;
    }

    void IMUSANT_processing::findSupermaximalsIntervals(int min_length, int min_percent)
    {
        if (IDs.size()>0)
        {
            
            ID_ivec_map id_ivec_map;
            interval_tree* tree = buildIntervalSuffixTree(id_ivec_map);
            repeats<vector<IMUSANT_interval> > rep(tree);

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

            delete tree;
        }
    }
    
    void
    IMUSANT_processing::
    findSupermaximalsContours(int min_length, int min_percent)
    {
//        if (IDs.size()>0)
//        {
//            contour_tree cont_tree(*(collection_visitors[*IDs.begin()].getMelodicContour()),*IDs.begin());
//            
//            for (vector<int>::iterator j = IDs.begin()+1; j!=IDs.end(); j++)
//            {
//                cont_tree.add_sentence(*(collection_visitors[*j].getMelodicContour()),*j);
//            }
//            
//            repeats<vector<IMUSANT_contour_symbol> > rep(&cont_tree);
//            list<repeats<vector<IMUSANT_contour_symbol> >::supermax_node*> supermaxs = rep.supermax_find(min_percent, min_length);
//            list<repeats<vector<IMUSANT_contour_symbol> >::supermax_node*>::const_iterator q=supermaxs.begin();
//            for (; q!=supermaxs.end(); q++)
//            {
//                for (repeats<vector<IMUSANT_contour_symbol> >::index t = (*q)->begin_i; t!=(*q)->end_i; t++)
//                {
//                    cout << *t;
//                }
//                cout << " ";
//                cout << "Witnesses: " << (*q)->num_witness << " number of leaves: " << (*q)->num_leaves << " Percent: " << (*q)->percent << endl;
//            }
//        }
    }
    
    // Find longest common subsequence of intervals for pairs of file/works
    // This example of dynamic programming is adapted from Crochemore and Lecroq,
    // Pattern MAtching and text compression algorithms, available from:
    // http://www-igm.univ-mlv.fr/~mac/REC/DOC/03-CRC.ps
    
    void
    IMUSANT_processing::
    findLcsPairsIntervals(bool consecutive)
    {
#ifdef OLD
        if (IDs.size()>1)
        {
            for (vector<int>::iterator IDiter1=IDs.begin(); IDiter1!=IDs.end(); IDiter1++)
            {
                vector<IMUSANT_interval> x = scores[*IDiter1].getIntervalVector()->getIntervals();
                int m = x.size();
                
                for (vector<int>::iterator IDiter2=IDiter1+1; IDiter2!=IDs.end(); IDiter2++)
                {
                    
                    cout << "Longest common subsequence of " << scores[*IDiter1].getMovementTitle() << " with "
                    << scores[*IDiter2].getMovementTitle() << endl;
                    
                    vector<IMUSANT_interval> y = scores[*IDiter2].getIntervalVector()->getIntervals();
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
#endif
    }
    
    void
    IMUSANT_processing::
    findLcsPairsIntervalsReverse(bool consecutive)
    {
#ifdef OLD
        if (IDs.size()>1)
        {
            for (vector<int>::iterator IDiter1=IDs.begin(); IDiter1!=IDs.end(); IDiter1++)
            {
                vector<IMUSANT_interval> x = scores[*IDiter1].getIntervalVector()->getIntervals();
                x.pop_back();
                reverse(x.begin(), x.end()); //added routine - reverse vector
                int m = x.size();
                
                for (vector<int>::iterator IDiter2=IDiter1+1; IDiter2!=IDs.end(); IDiter2++)
                {
                    
                    cout << "Longest common subsequence of " << scores[*IDiter1].getMovementTitle() << " with "
                    << scores[*IDiter2].getMovementTitle() << endl;
                    
                    vector<IMUSANT_interval> y = scores[*IDiter2].getIntervalVector()->getIntervals();
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
#endif
    }
    
    //Find longest common subsequence of pitches for pairs of file/works
    void
    IMUSANT_processing::
    findLcsPairsPitches(bool consecutive)
    {
        if (IDs.size()>1)
        {
            for (vector<int>::iterator IDiter1=IDs.begin(); IDiter1!=IDs.end(); IDiter1++)
            {
                vector<IMUSANT_pitch> x = *(collection_visitors[*IDiter1].getPitchVector());
                int m = x.size();
                
                for (vector<int>::iterator IDiter2=IDiter1+1; IDiter2!=IDs.end(); IDiter2++)
                {
                    
                    cout << "Longest common subsequence of " << collection_visitors[*IDiter1].getMovementTitle() << " with "
                    << collection_visitors[*IDiter2].getMovementTitle() << endl;
                    
                    vector<IMUSANT_pitch> y = *(collection_visitors[*IDiter2].getPitchVector());
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
    
    vector<S_IMUSANT_segmented_part_LBDM>
    IMUSANT_processing::
    findMelodicSegments_LBDM()
    {
        vector<S_IMUSANT_segmented_part_LBDM> segmented_parts;
        
        // We have >1 score, each of which may have >1 part.
        for (vector<S_IMUSANT_score>::iterator scores_iter = scores.begin(); scores_iter != scores.end(); scores_iter++)
        {
            IMUSANT_vector<S_IMUSANT_part>& parts = (*scores_iter)->partlist()->parts();
            
            for(vector<S_IMUSANT_part>::iterator parts_iter = parts.begin(); parts_iter != parts.end(); parts_iter++)
            {
                S_IMUSANT_segmented_part_LBDM seg_part = new_IMUSANT_segmented_part_LBDM(*parts_iter);
                seg_part->getOverallLocalBoundaryStrengthProfile();
                segmented_parts.push_back(seg_part);
            }
        }
        
        return segmented_parts;
    }
    
    
} //namespace IMUSANT