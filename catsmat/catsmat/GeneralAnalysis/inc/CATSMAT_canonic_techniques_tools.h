//
//  CATSMAT_CanonicTechniquesTools.hpp
//  catsmat
//
//  Created by Jason Stoessel on 10/03/2017.
//
//

#ifndef CATSMAT_canonic_techniques_tools_hpp
#define CATSMAT_canonic_techniques_tools_hpp

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
    struct CATSMAT_CanonType
    {
        typedef pair<IMUSANT_duration,int>  CATSMAT_IOI_pair;
        
        bool    retrograde_inversion() { return retrograde_ && contrary_motion_; }
        friend  ostream& operator<< (ostream& os, const CATSMAT_CanonType& type );
        
        //data members
        S_IMUSANT_score             score_;                 //lookback to source score
        vector<S_IMUSANT_part>      parts_;                 //refs to parts of score that form the canon
        unsigned long               number_of_voices_ = 2;  //assume 2 in 1, but change for 3 in 1, etc
        vector<CATSMAT_IOI_pair>    ioi_pairs_;             //there are >2 vv. canons with different iois
        vector<IMUSANT_interval>    intervals_;             //there are 2 vv. canon with different intervals, eg. 5th and octave
        bool                        imitative_ = false;     //exact melodic relationship
        bool                        strict_ = false;        //string exact rhythmic relation
        bool                        retrograde_ = false;    //crab canon
        bool                        contrary_motion_ = false;
        bool                        proportional_ = false;
        bool                        stacked_ = false;
        bool                        tonal_ = false;         //not considered in first iteration project
        vector<TRational>           proportions_;
        vector<IMUSANT_time::symbol> mensurations_;
        
    };
    
    class CATSMAT_CanonicTechniquesTools : public smartable
    {
    public:
        friend  IMUSANT_SMARTP<CATSMAT_CanonicTechniquesTools> new_CATSMAT_object<CATSMAT_CanonicTechniquesTools>();
        bool    Initialise(S_IMUSANT_score the_score, double threshold = 0.1);
        
        vector<CATSMAT_CanonType> GetCanonTypes() { return canon_types_; }
        
    protected:
        CATSMAT_CanonicTechniquesTools() {}
        ~CATSMAT_CanonicTechniquesTools() {}
    private:
        void    Detect_Canon_Type(IMUSANT_PartEntry& first_part, IMUSANT_PartEntry& second_part, double error_threshold);
        void    Insert(CATSMAT_CanonType canon_type);
        bool    IsMelodicallyExact(const IMUSANT_PartEntry& first_part, const IMUSANT_PartEntry& second_part, const double error_threshold);
        bool    IsIntervallicallyExact(const IMUSANT_PartEntry& first_part, const IMUSANT_PartEntry& second_part, const double error_threshold);
        bool    IsRhythmicallyExact(const IMUSANT_PartEntry& first_part, const IMUSANT_PartEntry& second_part, double error_threshold, bool retrograde=false);
        bool    IsRetrograde(const IMUSANT_PartEntry& first_part, const IMUSANT_PartEntry& second_part, const double error_threshold);
        bool    IsContraryMotion(const IMUSANT_PartEntry& first_part, const IMUSANT_PartEntry& second_part, double error_threshold);
        bool    IsRetrogradeContraryMotion(const IMUSANT_PartEntry& first_part, const IMUSANT_PartEntry& second_part, double error_threshold);
        bool    IsProportionalCanon(const IMUSANT_PartEntry& first_part, const IMUSANT_PartEntry& second_part, TRational& result, const double error_threshold, bool retrograde=false);
        static TRational   IsProportionalCanonBinaryOperator(S_IMUSANT_note& first, const S_IMUSANT_note& second);
        bool    IsMensurationCanon(const IMUSANT_PartEntry& first_part, const IMUSANT_PartEntry& second_part, double error_threshold);
        IMUSANT_interval   GetIntervalBetweenParts(IMUSANT_PartEntry& first_part, IMUSANT_PartEntry& second_part, bool retrograde=false);
        IMUSANT_duration   CalculateIOIUnit(IMUSANT_PartEntry& first_part, IMUSANT_PartEntry& second_part);
        void    OrderPartsByLength(const IMUSANT_PartEntry& first_part, const IMUSANT_PartEntry& second_part, IMUSANT_vector<S_IMUSANT_note> &part_one_notes, IMUSANT_vector<S_IMUSANT_note>& part_two_notes);
        
        S_IMUSANT_score             score_;
        double                      error_threshold_ = 0;
        vector<CATSMAT_CanonType>   canon_types_;
        
    };
    typedef IMUSANT_SMARTP<CATSMAT_CanonicTechniquesTools> S_CATSMAT_CanonicTechniquesTools;
}

#endif /* CATSMAT_canonic_tools_hpp */

