//
//  CATSMAT_CanonicTools.hpp
//  catsmat
//
//  Created by Jason Stoessel on 10/03/2017.
//
//

#ifndef CATSMAT_canonic_tools_hpp
#define CATSMAT_canonic_tools_hpp

#include <stdio.h>
#include "smartpointer.h"
#include "IMUSANT_score.h"
#include "IMUSANT_interval.h"
#include "IMUSANT_partlist_ordered_by_part_entry.h" //we will use IMUSANT_PartEntry
#include "CATSMAT_t_utilities.h"

using namespace IMUSANT;

namespace CATSMAT
{
    //this records one canonic relation; use multiple canon_types to indicate double, triple, etc. canons.
    struct CATSMAT_Canon_Type
    {
        typedef pair<IMUSANT_duration,int>  CATSMAT_IOI_pair;
        
        bool    retrograde_inversion() { return retrograde_ && contrary_motion_; }
        friend  ostream& operator<< (ostream& os, const CATSMAT_Canon_Type& type );
        
        //data members
        vector<S_IMUSANT_part>      parts_;
        unsigned long               number_of_voices_ = 2; //assume 2 in 1, but change for 3 in 1, etc
        vector<CATSMAT_IOI_pair>    ioi_pairs_; //there are >2 vv. canons with different iois
        vector<IMUSANT_interval>    intervals_; //thre are 2 vv. canon with different intervals, eg. 5th and octave
        bool                        imitative_ = false; //exact melodic relationship
        bool                        strict_ = false;    //string exact rhythmic relation
        bool                        retrograde_ = false; //crab canon
        bool                        contrary_motion_ = false;
        bool                        proportional_ = false;
        bool                        stacked_ = false;
        bool                        tonal_ = false; //not considered in first iteration project
        vector<TRational>           proportions_;
        IMUSANT_time::symbol        mensur_1_ = IMUSANT_time::symbol::undefined;
        IMUSANT_time::symbol        mensur_2_ = IMUSANT_time::symbol::undefined;
        
    };
    
    class CATSMAT_CanonicTools : public smartable
    {
    public:
        friend  IMUSANT_SMARTP<CATSMAT_CanonicTools> new_CATSMAT_object<CATSMAT_CanonicTools>();
        bool    Initialise(S_IMUSANT_score the_score, double threshold = 0.1);
        
        vector<CATSMAT_Canon_Type> GetCanonTypes() { return canon_types_; }
        
    protected:
        CATSMAT_CanonicTools() {}
        ~CATSMAT_CanonicTools() {}
    private:
        void    Detect_Canon_Type(IMUSANT_PartEntry& first_part, IMUSANT_PartEntry& second_part, double error_threshold);
        void    Insert(CATSMAT_Canon_Type canon_type);
        bool    IsMelodicallyExact(IMUSANT_PartEntry& first_part, IMUSANT_PartEntry& second_part, double error_threshold);
        bool    IsIntervallicallyExact(IMUSANT_PartEntry& first_part, IMUSANT_PartEntry& second_part, double error_threshold);
        bool    IsRhythmicallyExact(IMUSANT_PartEntry& first_part, IMUSANT_PartEntry& second_part, double error_threshold);
        bool    IsRetrograde(IMUSANT_PartEntry& first_part, IMUSANT_PartEntry& second_part, double error_threshold);
        bool IsProportionalCanon(IMUSANT_PartEntry& first_part, IMUSANT_PartEntry& second_part, TRational& result, double error_threshold);
        bool IsMensurationCanon(IMUSANT_PartEntry& first_part, IMUSANT_PartEntry& second_part, double error_threshold);
        bool IsInversion(IMUSANT_PartEntry& first_part, IMUSANT_PartEntry& second_part, double error_threshold);
        IMUSANT_interval   GetIntervalBetweenParts(IMUSANT_PartEntry& first_part, IMUSANT_PartEntry& second_part);
        IMUSANT_duration    CalculateIOIUnit(IMUSANT_PartEntry& first_part, IMUSANT_PartEntry& second_part);
        
        S_IMUSANT_score             score_;
        double                      error_threshold_ = 0;
        vector<CATSMAT_Canon_Type>  canon_types_;
        
    };
    typedef IMUSANT_SMARTP<CATSMAT_CanonicTools> S_CATSMAT_Canonic_Tools;
}

#endif /* CATSMAT_canonic_tools_hpp */

