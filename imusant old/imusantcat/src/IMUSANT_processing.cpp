/*
 *  IMUSANT_processing.cpp
 *  imusant
 *
 *  Created by Jason Stoessel on 26/07/06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */
#include <iostream>
#include <deque>

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

#define MAX(X,Y) ( (X>Y)? (X) : (Y) )

using namespace std;
using namespace ns_suffixtree;
using namespace boost;

namespace IMUSANT
{

typedef suffixtree< vector<IMUSANT_interval> > int_tree;
typedef suffixtree< vector<IMUSANT_contour_symbol> > contour_tree;
typedef boost::multi_array<int, 2> int_2d_array_t;

void IMUSANT_processing::process_directory_files(const filesystem::path& full_path)
{
	if (filesystem::is_directory( full_path ) )
	{
		filesystem::directory_iterator end;
		for (	filesystem::directory_iterator iter(full_path);
				iter != end;
				++iter )
		{
			add_file(*iter);
		}		
	}
}

void
IMUSANT_processing::add_file(const filesystem::path& path)
{
	TMusicXMLFile reader;
	string xml(".xml"), imusant(".ims");
	filesystem::path mutable_path = path;
	TXML2IMUSANTVisitor c;    
	IMUSANT_XMLFile ixml;
	map<int,vector<IMUSANT_interval> > intervalTable;
	int i = 1;
	
	try
	{
		if (!filesystem::is_directory(path))
		{
			if (filesystem::extension(path)==xml)
			{
				//convert first
				SScore score = reader.read((string&)path);
				if (score == NULL) {
					cerr << "Parse error in " << path.leaf() << endl;
					return;
				}
				//ensure unique ID
				while (find(IDs.begin(), IDs.end(), i)!=IDs.end()) i++;
				//error checking required!
				score->accept(c);
				collections[i].ignoreRepeatedPitches(false);
				c.getIMUSANTScore()->accept(collections[i]);
				
				IDs.push_back(i);
				
			}
			//check extension
			if (filesystem::extension(path)==imusant)
			{
				ixml.read((string&)mutable_path); //reader file
				//verify, catalogue to default directory
			}

		}
	}
	catch (const runtime_error& ex)
	{
		cerr << path.leaf() << " " << ex.what() << endl;
	}
}

void
IMUSANT_processing::find_repeated_interval_substrings(int min_length)
{
	if (IDs.size()>0)
	{
		int_tree tree(collections[*IDs.begin()].getIntervalVector()->getIntervals(),*IDs.begin());
		
		cout << *IDs.begin() << ": " << collections[*IDs.begin()].getMovementTitle() << endl;
	
		for (vector<int>::iterator j = IDs.begin()+1; j!=IDs.end(); j++)
		{
			tree.add_sentence(collections[*j].getIntervalVector()->getIntervals(),*j);
			cout << *j << ": " << collections[*j].getMovementTitle() << endl;
		}
		
		vector< pair<vector<int_tree::number>, int> > results;
		results = tree.find_common_subsequences(IDs,min_length);
		cout << "Results are labeled (movement, voice, measure, note index)." << endl;
		cout << "Voices are designated from highest (1) to lowest." << endl;
		cout << "Found common exact intevallic subsequences of " << min_length << " or more elements at: " << endl;
		vector< pair<vector<int_tree::number>, int> >::iterator iter=results.begin();
		for (;iter!=results.end(); iter++)
		{
			
			cout << "Instance: ";
			vector< int_tree::number >::const_iterator c=iter->first.begin();
			bool first_time = true;
			for (;c!=iter->first.end(); c++) 
			{
				IMUSANT_interval interval = collections[c->first].getIntervalVector()->getIntervals()[c->second];
				if (first_time)
				{
					for (int_tree::size_type t = c->second; t < c->second+iter->second; t++)
					{	
						cout << collections[c->first].getIntervalVector()->getIntervals()[t] << " ";
					}
					first_time=false;
				}
				IMUSANT_range range=interval.getLocation();
				cout << "(" << c->first << "," <<range.partID << "," << range.first.measure << "," << range.first.note_index << ")";
			}
			
			cout << endl;
			cout << "Length: " << iter->second << " Occurences: " << iter->first.size() << endl << endl;
		}
		cout << endl;
	}
}

void
IMUSANT_processing::find_repeated_contour_substrings(int min_length)
{
	if (IDs.size()>0)
	{
		//construct contour tree
		contour_tree cont_tree(*(collections[*IDs.begin()].getMelodicContour()),*IDs.begin());
	
		for (vector<int>::iterator j = IDs.begin()+1; j!=IDs.end(); j++)
		{
			cont_tree.add_sentence(*(collections[*j].getMelodicContour()),*j);
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
				IMUSANT_contour_symbol symbol = (*(collections[mc_c->first].getMelodicContour()))[mc_c->second];
				if (first_time)
				{
					for (contour_tree::size_type t = mc_c->second; t < mc_c->second+iter_mc->second; t++)
					{	
						cout << (*(collections[mc_c->first].getMelodicContour()))[t] << " ";
					}
					first_time=false;
				}
				IMUSANT_range range=symbol.getLocation();
				cout << "(" << mc_c->first << "," <<range.partID << "," << range.first.measure << "," << range.first.note_index << ")";
			}
			
			cout << endl;
			cout << "Length: " << iter_mc->second << " Occurences: " << iter_mc->first.size() << endl << endl;
		}
		cout << endl;

	}
}

void IMUSANT_processing::find_supermaximals_intervals(int min_length, int min_percent)
{
	if (IDs.size()>0)
	{
		int_tree tree(collections[*IDs.begin()].getIntervalVector()->getIntervals(),*IDs.begin());
	
		for (vector<int>::iterator j = IDs.begin()+1; j!=IDs.end(); j++)
		{
			tree.add_sentence(collections[*j].getIntervalVector()->getIntervals(),*j);
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
		contour_tree cont_tree(*(collections[*IDs.begin()].getMelodicContour()),*IDs.begin());
	
		for (vector<int>::iterator j = IDs.begin()+1; j!=IDs.end(); j++)
		{
			cont_tree.add_sentence(*(collections[*j].getMelodicContour()),*j);
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

// Find longest common subsequenceof intervals for pairs of file/works
// This example of dynamic programming is adapted from Crochemore and Lecroq, 
// Pattern MAtching and text compression algorithms, available from:
// http://www-igm.univ-mlv.fr/~mac/REC/DOC/03-CRC.ps

void IMUSANT_processing::find_lcs_pairs_intervals(bool consecutive)
{
	if (IDs.size()>1)
	{
		for (vector<int>::iterator IDiter1=IDs.begin(); IDiter1!=IDs.end(); IDiter1++)
		{
			vector<IMUSANT_interval> x = collections[*IDiter1].getIntervalVector()->getIntervals();
			int m = x.size();
			
			for (vector<int>::iterator IDiter2=IDiter1+1; IDiter2!=IDs.end(); IDiter2++)
			{
			
				cout << "Longest common subsequence of " << collections[*IDiter1].getMovementTitle() << " with " 
					<< collections[*IDiter2].getMovementTitle() << endl;
					
				vector<IMUSANT_interval> y = collections[*IDiter2].getIntervalVector()->getIntervals();
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
			vector<IMUSANT_interval> x = collections[*IDiter1].getIntervalVector()->getIntervals();
			x.pop_back();
			reverse(x.begin(), x.end()); //added routine - reverse vector
			int m = x.size();
			
			for (vector<int>::iterator IDiter2=IDiter1+1; IDiter2!=IDs.end(); IDiter2++)
			{
			
				cout << "Longest common subsequence of " << collections[*IDiter1].getMovementTitle() << " with " 
					<< collections[*IDiter2].getMovementTitle() << endl;
					
				vector<IMUSANT_interval> y = collections[*IDiter2].getIntervalVector()->getIntervals();
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
			vector<IMUSANT_pitch> x = *(collections[*IDiter1].getPitchVector());
			int m = x.size();
			
			for (vector<int>::iterator IDiter2=IDiter1+1; IDiter2!=IDs.end(); IDiter2++)
			{
			
				cout << "Longest common subsequence of " << collections[*IDiter1].getMovementTitle() << " with " 
					<< collections[*IDiter2].getMovementTitle() << endl;
					
				vector<IMUSANT_pitch> y = *(collections[*IDiter2].getPitchVector());
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