/**
    \class      CATSMAT_score_profile
    \file       CATSMAT_score_profile.tpp
    \namespace  catsmat
    \author     Jason Stoessel
    \date       Created by Jason Stoessel on 15/12/16.

    Template function for CATSMAT_score_profile, with explicit instantiations for:
        IMUSANT_pitch
        IMUSANT_duration
        IMUSANT_interval
 */

#include <numeric>
#include <iostream>
#include "CATSMAT_score_profile.hpp"
#include "CATSMAT_partdata.h"

namespace CATSMAT
{
    
    //-----------
    
    template <typename T>
    void
    CATSMAT_score_profile<T>::Accumulate(const string& partname, const PROFILE& pp)
    {
        
        //store local ref to part names
        fPartNames.push_back(partname);
        //accumulate T data maps - check that accumulate is non-destructive
        
        fProfile = std::accumulate(pp.begin(),pp.end(),fProfile,
                                   [](std::map<T,int> &m, const std::pair<const T, int> p)
                                   {
                                       return (m[p.first] +=p.second, m);
                                   });
        //tabulate T occurrence for each part
        for (auto p : pp)
        {
            fTable.push_back(std::make_tuple(partname,p.first,p.second));
        }
    }
    
    template <typename T>
    void
    CATSMAT_score_profile<T>::Sort()
    {
        std::sort(fTable.begin(),
                  fTable.end(),
                  [](TABLE_TUPLE const &tuple1, TABLE_TUPLE const &tuple2)
                  {
                      return get<0>(tuple1) > get<0>(tuple2) && get<1>(tuple1) > get<1>(tuple2);
                  });
    }
    
    template <typename T>
    void
    CATSMAT_score_profile<T>::print(ostream& os) const
    {
        ostringstream header,lines,total;
        header << fType << fDelimiter;
        total << "Total" << fDelimiter;
        
        for (auto data : fProfile)
        {
            //add pitch name to header
            header << data.first << fDelimiter;
            total << data.second << fDelimiter;
        }
        
        for (auto s : fPartNames)
        {
            ostringstream line;
            line << s.c_str() << fDelimiter;
            
            for (auto data : fProfile)
            {
                T t = data.first; //pitch type
                //search table for occurrences of pitch in part
                auto it = std::find_if(fTable.begin(), fTable.end(), [&s,&t](const tuple<string,T,int>& item)
                                       {
                                           return s == get<0>(item) && t == get<1>(item);
                                       }); //returns iterator
                if (it!=fTable.end())
                    line << get<2>(*it) << fDelimiter;
                else //not found
                    line << "0" << fDelimiter;
                
            }
            
            lines << line.str() << endl;
        }
        
        header << endl;
        
        os << header.str();
        os << lines.str();
        os << total.str() << endl;
        
    }
    
    
    //explicit instantiations of templated classes
    template class CATSMAT_score_profile<IMUSANT_pitch>;
    template class CATSMAT_score_profile<IMUSANT_interval>;
    template class CATSMAT_score_profile<IMUSANT_duration>;
    
}

