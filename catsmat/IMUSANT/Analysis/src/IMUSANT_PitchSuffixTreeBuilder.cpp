//
//  IMUSANT_PitchSuffixTreeBuilder.cpp
//  
//
//  Created by Jason Stoessel on 13/06/2016.
//
//

#include "IMUSANT_PitchSuffixTreeBuilder.h"

namespace IMUSANT {
    
    void
    IMUSANT_PitchSuffixTreeBuilder::Visit(const IMUSANT_processing& processing)
    {
        IMUSANT_processing::COLLECTIONMAP collections = processing.getCollections();
        
        BuildVectorMap(collections);
        
        //tree_ptr_ = buildSuffixTree(id_vec_map_); //Undefined symbols for architecture x86_64: IMUSANT_pitch::operator!=(IMUSANT::IMUSANT_pitch const&) const
    }
    
    void
    IMUSANT_PitchSuffixTreeBuilder::
    BuildVectorMap(IMUSANT_processing::COLLECTIONMAP& collections)
    {
        //get first part from first file
        int ID = 0;
        
        for (auto i = collections.begin(); i!=collections.end(); i++)
        {
            IMUSANT_collection_visitor collection = i->second;
            for (auto j = collection.getPartwisePitchVectors().begin(); j!=collection.getPartwisePitchVectors().end(); j++)
            {
                ++ID;
                id_vec_map_[ID] = (*j)->getPitches();
            }
        }
    }

    /*string
    IMUSANT_PitchSuffixTreeBuilder::
    findAndPrintLcsPairsPitches(bool consecutive)
    {
        SUBSTR_VECTOR the_result;
        the_result = findLcsPairsPitches(consecutive);
        
        stringstream the_result_as_stringstream;
        for(int index = 0 ; index < the_result.size(); index++)
        {
            the_result_as_stringstream << the_result[index];
        }
        
        the_result_as_stringstream << endl;
        
        return the_result_as_stringstream.str();
    }*/

    //Find longest common subsequence of pitches for pairs of file/works
    /*IMUSANT_PitchSuffixTreeBuilder::SUBSTR_VECTOR
    IMUSANT_PitchSuffixTreeBuilder::
    findLcsPairsPitches(bool consecutive)
    {
        SUBSTR_VECTOR ret_val;
        
        for (auto i = id_vec_map_.begin(); i!=id_vec_map_.end(); i++)
        {
            vector<IMUSANT_pitch> x = i->second;
            vector<IMUSANT_pitch>::size_type m = x.size();
            
            auto j = i;
            
            for (++j; j!=id_vec_map_.end(); j++)
            {
                vector<IMUSANT_pitch> y = j->second;
                int a = 0, b = 0;
                vector<IMUSANT_interval>::size_type n = y.size();
                int_2d_array_t lcs(boost::extents[m][n]); //ints auto zeroed
                
                for (a=0; a< m-1; a++)
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
                
                deque<pair<IMUSANT_pitch,IMUSANT_pitch> > z;
                while (a > 0 && b > 0)
                {
                    if(lcs[a][b]==lcs[a-1][b-1]+1 && x[a-1]==y[b-1])
                    {
                        pair<IMUSANT_pitch,IMUSANT_pitch> p(x[a-1],y[b-1]);
                        z.push_front(p);
                        a--; b--;
                    }
                    else if (lcs[a-1][b] > lcs[a][b-1]) a--;
                    else b--;
                }
                
                IMUSANT_repeated_pitch_substring ps;
                for (deque<pair<IMUSANT_pitch,IMUSANT_pitch> >::iterator iv=z.begin(); iv!=z.end(); iv++)
                {
                    ps.sequence.push_back(iv->first);
                }
                if (!ps.sequence.empty()) {
                    ret_val.push_back(ps);
                }
                
            }
        }
        
         return ret_val;
        
    }*/
    
    IMUSANT_range
    IMUSANT_PitchSuffixTreeBuilder::
    CalcRange(IMUSANT_pitch& pitch) const
    {
        return IMUSANT_range(); //nothing for now
    }
   

}
