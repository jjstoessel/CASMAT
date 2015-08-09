/*
 *  Search.h
 *	A template class for searching vectors of data
 *
 *  Created by Jason Stoessel on 30/06/06.
 *  Copyright 2006 Jason Stoessel. All rights reserved.
 *
 *	Although there is some sacrifice of speed for convenience, this class is designed to work for
 *	all arrays of elements will operators == and < (necessary for map sorting) implemented.
 */

#include <vector>
#include <map>
#include <algorithm>

using namespace std;

template <class T>
class Search
{
	public:
		Search();
		Search(const vector<T>& v);
		Search(const Search<T>& s);
		~Search() {}
		void operator=(const Search<T>& s);
		
		const vector<int>& GetFinds() { return finds; }
		
		void MorrisPratt(const vector<T>& pattern);
		void KnuthMorrisPratt(const vector<T>& pattern);
		void QuickSearch(const vector<T>& pattern);
		
		void ClearFinds() { finds.clear(); }
		
	private:
	
		void copy(const Search<T>& other);
		
		void MorrisPrattCommon(const vector<T>& pattern, int mpJmpTbl[]);
		void PrepMorrisPratt(const vector<T>& pattern, int jmpTbl[]);
		void PrepKnuthMorrisPratt(const vector<T>& pattern, int jmpTbl[]);
		
		vector<T>	data;
		vector<int> finds;
};

template <class T>
Search<T>::Search()
{
}

template <class T>
Search<T>::Search(const vector<T>& v)
{
	data=v;
}

template <class T>
Search<T>::Search(const Search<T>& s)
{
	*this = s;
}

template <class T> 
void Search<T>::operator=(const Search<T>& s)
{
	copy(s);
}

template <class T>
void Search<T>::copy( const Search<T>& other)
{
	data = other.data;
	finds = other.finds;
}

template <class T>
void Search<T>::MorrisPratt(const vector<T>& pattern)
{
	int mpJmpTbl[pattern.size()];
	
	PrepMorrisPratt(pattern,mpJmpTbl);
	MorrisPrattCommon(pattern,mpJmpTbl);
}

//The Morris-Pratt and Knuth-Morris-Pratt searcher only differ
//in their preparation
template <class T>
void Search<T>::MorrisPrattCommon(const vector<T>& pattern, int mpJmpTbl[])
{
	int i, j;
	int m = pattern.size();
	
	i = j = 0;
	
	while (j < data.size())
	{		
		while ( i > -1 && pattern[i]!=data[j])
			i = mpJmpTbl[i];
		i++;
		j++;
		if (i>=m)
		{
			finds.push_back(j-i);
			i = mpJmpTbl[i];
		}
	}
}

template <class T>
void Search<T>::PrepMorrisPratt(const vector<T>& pattern, int mpJmpTbl[])
{
	int i = 0;
	int j = mpJmpTbl[i] = -1;
	
	while ( i < pattern.size() )
	{
		while (j > -1 && pattern[i]!=pattern[j] )
			j = mpJmpTbl[j];
		mpJmpTbl[++i] = ++j;
	}
}

template <class T>
void Search<T>::KnuthMorrisPratt(const vector<T>& pattern)
{
	int mpJmpTbl[pattern.size()];
	
	PrepKnuthMorrisPratt(pattern,mpJmpTbl);
	MorrisPrattCommon(pattern,mpJmpTbl);
}

template <class T>
void Search<T>::PrepKnuthMorrisPratt(const vector<T>& pattern, int jmpTbl[])
{
   int i, j;

   i = 0;
   j = jmpTbl[0] = -1;
   while (i < pattern.size()) 
   {	
		while (j > -1 && pattern[i] != pattern[j])
			j = jmpTbl[j];
		i++;
		j++;
		//here's the optimisation
		if (pattern[i] == pattern[j])
			jmpTbl[i] = jmpTbl[j];
		else
			jmpTbl[i] = j;
   }
}

//simplified Boyer-Moore - modified by JS so that complete alphabet is not mapped, only those
//present in the key/pattern
//fast in practice, but can have O(mn)
template <class T>
void Search<T>::QuickSearch(const vector<T>& pattern)
{
	map<T,int> qsBc;
	int m = pattern.size();
	int n = data.size();
	
	/* Preprocessing */
	//modified version - only maps shifts for elements in pattern
	//any other element in data maps to maximum shift m + 1
	//repeated keys are overwritten by last instance
	for (int i = 0; i < m; ++i)
		qsBc[pattern[i]] = m - i;
 
	/* Searching */
	int j = 0;
	
	while (j <= n - m) 
	{
		if (equal(pattern.begin(), pattern.end(), data.begin() + j))
			finds.push_back(j);
		if (qsBc.count(data[j + m])==1)
			j += qsBc[data[j+m]];               /* shift */
		else
			j += m;								//default shift
	}
}









