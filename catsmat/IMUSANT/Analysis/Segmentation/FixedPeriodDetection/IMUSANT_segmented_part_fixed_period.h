//
//  IMUSANT_segmented_part_fixed_period.h
//  catsmat
//
//  Created by Derrick Hill on 29/10/2016.
//
//

#ifndef __catsmat__IMUSANT_segmented_part_fixed_period__
#define __catsmat__IMUSANT_segmented_part_fixed_period__

#include <stdio.h>

#include "IMUSANT_note.h"
#include "IMUSANT_score.h"

using namespace std;

namespace IMUSANT
{
    class IMUSANT_segmented_part_fixed_period : public smartable
    {
    public:
        
        static const int SUCCESS = 0;
        static const int ERR_NOT_ENOUGH_PARTS = 1;
        static const int ERR_MORE_THAN_ONE_PART_AT_BEGINNING = 2;
        static const int ERR_PARTS_DONT_MATCH = 3;
        
        friend IMUSANT_SMARTP<IMUSANT_segmented_part_fixed_period> new_IMUSANT_segmented_part_fixed_period();

        
        IMUSANT_segmented_part_fixed_period()
        {
        }
        
        virtual ~IMUSANT_segmented_part_fixed_period() {}
        
        int initialise(S_IMUSANT_score the_score);
        
        //
        // This method returns you segments in the form of note vectors.  Each element of the
        // returned vector is a segment.
        //
        vector<IMUSANT_note_vector> getSegmentsAsNoteVectors();
        
        friend ostream& operator<< (ostream& os, const IMUSANT_segmented_part_fixed_period& segmented_part);
        
        int get_period_length() { return fPeriodLength; };
        
    private:
        S_IMUSANT_score fScore;
        
        int fPeriodLength = 0;
        
    };
    
    typedef IMUSANT_SMARTP<IMUSANT_segmented_part_fixed_period> S_IMUSANT_segmented_part_fixed_period;
    IMUSANT_SMARTP<IMUSANT_segmented_part_fixed_period> new_IMUSANT_segmented_part_fixed_period();
}


#endif /* defined(__catsmat__IMUSANT_segmented_part_fixed_period__) */
