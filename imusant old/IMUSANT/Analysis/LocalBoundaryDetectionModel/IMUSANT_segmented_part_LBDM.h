//
//  IMUSANT_segmented_part_LBDM.h
//  imusant
//
//  Created by Derrick Hill on 19/03/2016.
//
//

#ifndef __imusant__IMUSANT_segmented_part_LBDM__
#define __imusant__IMUSANT_segmented_part_LBDM__

#include <stdio.h>

#include "IMUSANT_part.h"
#include "IMUSANT_interval_profile_LBDM.h"
#include "IMUSANT_consolidated_interval_profile_LBDM.h"

using namespace std;

namespace IMUSANT
{
    typedef vector<S_IMUSANT_note> IMUSANT_segment;
    
    class IMUSANT_segmented_part_LBDM : public smartable
    {
    public:

        friend IMUSANT_SMARTP<IMUSANT_segmented_part_LBDM> new_IMUSANT_segmented_part_LBDM(S_IMUSANT_part the_part);
        
        IMUSANT_segmented_part_LBDM(S_IMUSANT_part the_part)
        {
            fPart = the_part;
        }
        
        virtual ~IMUSANT_segmented_part_LBDM() {}
        
        
        //
        // You must call this function to initialise the class from the data in the Part.
        //
        vector<float>& getOverallLocalBoundaryStrengthProfile();
        
        vector< IMUSANT_segment > getSegments();
        vector< int >             getSegmentBoundaries();
        void                      setSegmentBoundaryCalculationSpan(int segment_boundary_calculation_span) {SEGMENT_BOUNDARY_CALCULATION_SPAN = segment_boundary_calculation_span; };
        IMUSANT_consolidated_interval_profile_vector_LBDM  getConsolidatedProfiles();
        

        
        // This output operator produces a table that lists the notes used for calculating
        // boundary strength, together with the strength vectors.  Output is as follows:
        //
        //        PART NAME - Alto
        //        STRENGTH VECTORS
        //        NOTE1                       NOTE2                                  PITCH             IOI            REST    WEIGHTED AVG
        //        {
        //            {-,                         {1.1, 72, 512},                      5184.50,       262144.00,            0.00,        66184.06},             // 0
        //            {{1.1, 72, 512},            {1.2, 71, 512},                         1.51,            0.00,            0.00,            0.19},             // 1
        //            [...snip...]
        //            {{6.1, 72, 512},            {6.2, -, 512, rest},                    0.00,            0.00,          512.00,           64.00},             // 11
        //        }
        //
        // Where:
        // NOTE1 = The first note in the interval from which change was calculated.
        // NOTE2 = The second note in the interval.
        // PITCH = The value of the strength vector for the Pitch Interval Profile
        // IOI = The value of the strength vector for the IOI Interval Profile
        // REST = The value of the strength vector for the Rest Interval Profile
        // WEIGHTED AVG = The overall local boundary strength profile for the interval.
        //
        // Where the note values represented by this {1.1, 72, 512} are
        // {MeasureNumber.NoteIndex, MidiKeyNumber, DurationAsAbsoluteNumeric}
        //
        friend ostream& operator<< (ostream& os, const IMUSANT_segmented_part_LBDM& segmented_part);
        
        // This output operator produces compilable output that can be extracted as an
        // array initialisation for the purposes of capturing test case expected output.
        // The format is as follows:
        //
        // PITCH		IOI             REST			WEIGHTED AVG
        // {5184,		65536,			0.0000,			17032},             // 0
        // {0,			0,              0.0000,			0},                 // 1
        // {0,			0,              0.0000,			0},                 // 2
        // ...
        //
        string printForTesting() const;
        string print(bool include_notes, bool include_boundaries = false) const;

        
        S_IMUSANT_part getPart()
        {
            return fPart;
        }
 
    private:
        
        S_IMUSANT_part fPart;
        vector<float> overall_local_boundary_strength_profile;
        
        const float WEIGHT_INTERONSET_INTERVAL = 0.5;
        const float WEIGHT_PITCH = 0.25;
        const float WEIGHT_REST = 0.25;
        
        int SEGMENT_BOUNDARY_CALCULATION_SPAN = 4;
        
        IMUSANT_pitch_interval_profile pitch_interval_profile;
        IMUSANT_IOI_interval_profile ioi_interval_profile;
        IMUSANT_rest_interval_profile rest_interval_profile;
        
        // IOI's calculated using Duration.asAbsoluteNumeric() on each Note.
        // Pitch is calculated using a numeric representation of Pitch yet to be implemented.
        // Rests are calculated using the getType property of IMUSANT_note.
        void buildIntervalProfiles();
        
        void calculateOverallLocalBoundaryStrengthVector();
        
        // REVISIT - not implemented yet
        vector< IMUSANT_segment > getSegments(vector< int > segment_boundaries);
        
        int findNextSegmentBoundary(int start_index);
        bool isThisASegmentBoundary(int strength_profile_index_position) const;
        int getArrayPositionsWithoutOverflowingLowerBound(int index_position, int span) const;
        int getArrayPositionsWithoutOverflowingUpperBound(int index_position, int span) const;
        // REVISIT - not implemenmted yet.
        IMUSANT_segment buildSegment(int start_index, int end_index);

    };
    
    typedef IMUSANT_SMARTP<IMUSANT_segmented_part_LBDM> S_IMUSANT_segmented_part_LBDM;
    IMUSANT_SMARTP<IMUSANT_segmented_part_LBDM> new_IMUSANT_segmented_part_LBDM(S_IMUSANT_part the_part);
}

#endif /* defined(__imusant__IMUSANT_segmented_part_LBDM__) */
