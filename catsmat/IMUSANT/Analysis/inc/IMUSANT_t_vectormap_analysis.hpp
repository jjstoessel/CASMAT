//
//  IMUSANT_T_VectorMapAnalysis.hpp
//  catsmat
//
//  Created by Jason James Stoessel on 7/03/2017.
//
//

#ifndef IMUSANT_t_vectormap_analysis_hpp
#define IMUSANT_t_vectormap_analysis_hpp

#include <stdio.h>
#include <utility>

#include "boost/multi_array.hpp"

#include "IMUSANT_t_vectormap.hpp"
#include "IMUSANT_t_repeated_substring.h"

namespace IMUSANT
{
    template <typename T, class C>
    class IMUSANT_T_VectorMapAnalysis : public IMUSANT_T_VectorMap<T,C>
    {
    public:
        typedef typename IMUSANT_T_VectorMap<T,C>::SUBSTR_VECTOR    SUBSTR_VECTOR;
        typedef boost::multi_array<int, 2>                          int_2d_array_t;
        //typedef typename IMUSANT_T_VectorMap<T,C>::id_vec_map       id_vec_map;
        typedef  deque<pair<T,T> >                                  DEQUE_PAIR;
        typedef typename DEQUE_PAIR::iterator                       DEQUE_PAIR_ITERATOR;
        
        IMUSANT_T_VectorMapAnalysis() {}
        ~IMUSANT_T_VectorMapAnalysis() {}
        
        SUBSTR_VECTOR  FindLCSPairs(bool consecutive=true, bool reverse_search=false, bool retrograde=false);
        string         FindAndPrintLCSPairs(bool consecutive=true, bool reverse_search=false, bool retrograde=false);
        
    protected:
        virtual void Localise( IMUSANT_T_RepeatedSubstring<T>&,
                               DEQUE_PAIR,
                               typename IMUSANT_T_VectorMap<T,C>::id_vec_map::iterator&,
                               typename IMUSANT_T_VectorMap<T,C>::id_vec_map::iterator&,
                               bool first, bool consecutive) = 0;
        
    };
    
    #define MAX(X,Y) ( (X>Y)? (X) : (Y) ) //move to general macros header
    
    // Find longest common subsequence of elements for pairs of file/works
    // This example of dynamic programming is adapted from Crochemore and Lecroq,
    // Pattern MAtching and text compression algorithms, available from:
    // http://www-igm.univ-mlv.fr/~mac/REC/DOC/03-CRC.ps
    template <typename T, class C>
    typename IMUSANT_T_VectorMapAnalysis<T,C>::SUBSTR_VECTOR
    IMUSANT_T_VectorMapAnalysis<T,C>::
    FindLCSPairs(bool consecutive, bool reverse_search, bool retrograde)
    {
        SUBSTR_VECTOR ret_val;
        
        for (auto i = this->id_vec_map_.begin(); i!=this->id_vec_map_.end(); i++)
        {
            vector<T> x = i->second;
            if (reverse_search) {
                x.pop_back();
                reverse(x.begin(),x.end());
                retrograde = true; //switch for double reverse search
            }
            typename vector<T>::size_type m = x.size();
            auto j = i;
            for ( ++j ; j!=this->id_vec_map_.end(); j++) //will bail if only one element
            {
                vector<T> y = j->second;
                if (retrograde) {
                    y.pop_back();
                    reverse(y.begin(), y.end());
                    //needs unique terminator preserved
                }
                int a = 0, b = 0;
                typename vector<T>::size_type n = y.size();
                int_2d_array_t lcs(boost::extents[m][n]); //ints auto zeroed
                
                for (a=0; a < m-1; a++)
                {
                    for (b=0; b<n-1; b++)
                    {
                        if (x[a]==y[b])
                        {
                            lcs[a+1][b+1]=lcs[a][b]+1;
                        }
                        else
                        {
                            lcs[a+1][b+1]=MAX(lcs[a+1][b],lcs[a][b+1]);
                        }
                    }
                }
                
#ifdef _DEBUG //remove underscore to DEBUG
                for (int f = 0; f<m; f++) {
                    for (int g = 0; g<n; g++) {
                        cout << lcs[f][g];
                    }
                    cout << endl;
                }
#endif
                //now trace back to find lcs
                int limit_a = 0, limit_b = 0;
                if (reverse_search) limit_a = 1;
                if (retrograde) limit_b = 1;
                
                deque<pair<T,T> > z;
                while (a > limit_a && b > limit_b )
                {
                    if(lcs[a][b]==lcs[a-1][b-1]+1 && x[a-1]==y[b-1])
                    {
                        pair<T,T> p(x[a-1],y[b-1]);
                        z.push_front(p);
                        a--; b--;
                    }
                    else if (lcs[a-1][b] > lcs[a][b-1]) a--;
                    else b--;
                }
                

                IMUSANT_T_RepeatedSubstring<T> repeated_substring;
                bool first_loc_set = false;
                Localise(repeated_substring, z, i, j, first_loc_set, consecutive); //virtual void in base class
                ret_val.push_back(repeated_substring);
            }
        }
        return ret_val;
    }
    
    template <typename T, class C>
    string
    IMUSANT_T_VectorMapAnalysis<T,C>::
    FindAndPrintLCSPairs(bool consecutive, bool reverse_search, bool retrograde)
    {
        SUBSTR_VECTOR the_result;
        the_result = FindLCSPairs(consecutive, reverse_search, retrograde);
        
        stringstream the_result_as_stringstream;
        for(int index = 0 ; index < the_result.size(); index++)
        {
            the_result_as_stringstream << the_result[index];
        }
        
        the_result_as_stringstream << endl;
        
        return the_result_as_stringstream.str();
    }

    
}

#endif /* IMUSANT_t_vectormap_analysis_hpp */
