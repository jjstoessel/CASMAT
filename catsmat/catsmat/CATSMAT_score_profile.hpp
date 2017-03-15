/**
    \class      CATSMAT_score_profile
    \file       CATSMAT_score_profile.hpp
    \namespace  catsmat
    \date       Created by Jason Stoessel on 15/12/16.
    \author     Jason Stoessel
    \copyright  [add licence name]
    \brief      Template class for storing frequency of elements in score

    CATSMAT_score_profile is a template class for storing basic frequency of IMUSANT elements as T in a score. Currently tested for IMUSANT_pitch, IMUSANT_duration and IMUSANT_interval. Element must have ostream and comparison operators.

*/

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
        
        template typedef tuple<string,T,int> TABLE_TUPLE;    //!< \typedef TABLE_TUPLE. A tuple of part name, T, and T count
        template typedef map<T,int>          PROFILE;        //!< \typedef PROFILE. A map for T and T count
        
        /// CATSMAT_score_profile constructor.
        /**
            \param profile_type  string describing element to be captured.
         */
        CATSMAT_score_profile(const string& profile_type) : fDelimiter('\t') { fType = profile_type; }
        ~CATSMAT_score_profile() {}
        
        /// Accumulate
        /**
            Use Accumulate to profiles of type map<element, count> from each part using, for example, an external call to loop through parts or duets, etc. Accumulate builds a profile for the score and a table of frequencies for each part.
            \param  partname    string containing name of part or string of element from score
            \param  pp          profile (map<element, int> counting frequency (as int) of elements in part/element string
         */
        void Accumulate(const string& partname, const PROFILE& pp);
        /// Sort
        /**
            Call Sort after accumulating all profiles.
         */
        void Sort();
        /// print
        /**
            Prints table with summative profile in delimited format, i.e.
            Type    E1, E2, …
            Part1   count of E1, count of E2, …
            Part2 …
            Total   Sum of E1 across Part1 … Partn
            \param  os an output stream
         */
        void print(ostream& os) const;
        /// SetDeminiter
        /**
            Change delimiter using by print from default tab, e.g comma
            /param  c   new delimter char
         */
        void setDelimiter(char c) { fDelimiter = c; }
        /// profile()
        /**
         returns member variable
         */
        PROFILE& profile() { return fProfile; }
        
    private:
        
        string              fType;      //!< /var fType. Name of element T in profile
        vector<TABLE_TUPLE> fTable;     //!< /var fTable. A sparse "table" of T
        PROFILE             fProfile;   //!< /var fProfile. An accumulated profile of T in a score
        vector<string>      fPartNames; //!< /var fPartNames. Internal storage of partNames for accessing fTable
        char                fDelimiter; //!< /var fDelimiter. Delimiter character used in print function
        int                 fCount = 0; //!< /var fCount. Total number of elements in fTable.
    };
    
    template <typename T> struct SS_CATSMAT_score_profile{ typedef IMUSANT_SMARTP<CATSMAT_score_profile<T> > S_CATSMAT_score_profile; };
    
    /// Output operator
    /**
        Friend output operator function for CATSMAT_score_profile
     */
    template <typename T>
    ostream& operator<< (ostream& os, const CATSMAT_score_profile<T>& elt )
    {
        elt.print(os);
        
        return os;
    }
    
}

#endif /* CATSMAT_score_profile_hpp */
