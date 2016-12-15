//
//  CATSMAT_score_profile.hpp
//  catsmat
//
//  Created by Jason Stoessel on 15/12/16.
//
//

#ifndef CATSMAT_score_profile_hpp
#define CATSMAT_score_profile_hpp

#include <stdio.h>
#include <tuple>
#include <string>
#include <vector>
#include <map>
#include <numeric>
#include "CATSMAT_partdata.h"
#include "CATSMAT_t_utilities.h"

using namespace std;
using namespace IMUSANT;

namespace CATSMAT {
    
    template <typename T>
    class CATSMAT_score_profile : public smartable
    {
    public:
        friend  VEXP IMUSANT_SMARTP<CATSMAT_score_profile> new_CATSMAT_object<CATSMAT_score_profile>();
        
        typedef tuple<string,T,int> TABLE_TUPLE; //Part, T, count
        typedef map<T,int>          PROFILE; //count of T
        
        CATSMAT_score_profile(const string& profile_type) { fType = profile_type; }
        ~CATSMAT_score_profile() {}
        
        void Gather(const string& partname, const PROFILE& pp);
        void Sort();
        void PrintTable(ostream& os);
    private:
        string              fType;
        vector<TABLE_TUPLE> fTable; //a sparse "table" of T
        PROFILE             fProfile; //a summative profile of T in a score
        vector<string>      fPartNames;
        int                 fCount = 0;
    };
    
    template <typename T> struct SS_CATSMAT_score_profile{ typedef IMUSANT_SMARTP<CATSMAT_score_profile<T> > S_CATSMAT_score_profile; };
    
    //-----------
    
    template <typename T>
    void
    CATSMAT_score_profile<T>::Gather(const string& partname, const PROFILE& pp)
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
    CATSMAT_score_profile<T>::PrintTable(ostream& os)
    {
        ostringstream header;
        ostringstream lines;
        header << fType << "\t";
        
        for (auto data : fProfile)
        {
            //add pitch name to header
            header << data.first << "\t";
        }
        
        for (auto s : fPartNames)
        {
            ostringstream line;
            line << s.c_str() << "\t";
            
            for (auto data : fProfile)
            {
                T t = data.first; //pitch type
                //search table for occurrences of pitch in part
                auto it = std::find_if(fTable.begin(), fTable.end(), [&s,&t](const tuple<string,T,int>& item)
                                       {
                                           return s == get<0>(item) && t == get<1>(item);
                                       }); //returns iterator
                if (it!=fTable.end())
                    line << get<2>(*it) << "\t";
                else //not found
                    line << "0" << "\t";
                
            }
            
            lines << line.str() << endl;
        }
        
        header << endl;
        
        os << header.str();
        os << lines.str();
        
    }


}

#include "CATSMAT_score_profile.tpp"

#endif /* CATSMAT_score_profile_hpp */
