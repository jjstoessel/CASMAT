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
        template <typename U>
        friend  ostream& operator<<(ostream& os, const CATSMAT_score_profile<U>& elt );
        
        typedef tuple<string,T,int> TABLE_TUPLE;    //Part, T, count
        typedef map<T,int>          PROFILE;        //count of T
        
        CATSMAT_score_profile(const string& profile_type) { fType = profile_type; }
        ~CATSMAT_score_profile() {}
        
        void Accumulate(const string& partname, const PROFILE& pp);
        void Sort();
        void print(ostream& os) const;
        
    private:
        
        string              fType;
        vector<TABLE_TUPLE> fTable; //a sparse "table" of T
        PROFILE             fProfile; //a summative profile of T in a score
        vector<string>      fPartNames;
        int                 fCount = 0;
    };
    
    template <typename T> struct SS_CATSMAT_score_profile{ typedef IMUSANT_SMARTP<CATSMAT_score_profile<T> > S_CATSMAT_score_profile; };
    
    
    template <typename T>
    ostream& operator<< (ostream& os, const CATSMAT_score_profile<T>& elt )
    {
        elt.print(os);
        
        return os;
    }
    
}

#endif /* CATSMAT_score_profile_hpp */
