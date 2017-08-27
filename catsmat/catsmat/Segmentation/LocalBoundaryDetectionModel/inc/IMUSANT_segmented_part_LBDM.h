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


#include "I_Segmented.h"
#include "IMUSANT_part.h"
#include "IMUSANT_interval_profile_LBDM.h"
#include "IMUSANT_consolidated_interval_profile_LBDM.h"
#include "IMUSANT_segmented_profile_vectors.h"
#include "IMUSANT_segmented_note_vectors.h"
#include "IMUSANT_weighted_strength_vectors.h"

using namespace std;

namespace CATSMAT
{
    class IMUSANT_segmented_part_LBDM : public smartable, I_Segmented
    {
    public:

        friend IMUSANT_SMARTP<IMUSANT_segmented_part_LBDM> new_IMUSANT_segmented_part_LBDM();
        
        IMUSANT_segmented_part_LBDM(SetOfSegment & segmentation_result) : I_Segmented(segmentation_result)
        {
        }
        
        virtual ~IMUSANT_segmented_part_LBDM() {}
        
        
        //
        // You must call this function to initialise the class from the data in the Part.
        // This method calculates the profile vectors.
        //
        void initialise(S_IMUSANT_part the_part);
        
        //
        // The algorithm for calculating segments looks either side of each interval
        // to determine whether the strength of the interval represents a peak in
        // strength.  This number determines how far either side of each interval
        // the algorithm looks.  You don't have to call this - the default value
        // for the class is 4.
        //
        void setSegmentBoundaryCalculationSpan(int segment_boundary_calculation_span)
        {
            SEGMENT_BOUNDARY_CALCULATION_SPAN = segment_boundary_calculation_span;
        };
        
        //
        // This method returns you the segments, as a set (no duplicates).
        //
        SetOfSegment & getSegmentsSet();
        
        
        
        //
        // This method returns all the data you really need. Each row is a note-to-note interval
        // with the associated strengths, and an indication of whether the row represents a
        // boundary between segments.  This data is not segmented - the return value contains
        // all the change intervals for the part.
        //
        // For the calculation of segments we always use the EndNote element of each
        // IMUSANT_consolidated_interval_profile_LBDM.
        //
        IMUSANT_consolidated_interval_profile_vector_LBDM  getConsolidatedProfiles();
        
        //
        // This method returns the weighted average change vector as a single (unsegmented) vector.
        // This is the raw data to which the segmentation algorithm is applied.
        //
        IMUSANT_strength_vector getWeightedAverageStrengthVector()
        {
            return overall_local_boundary_strength_profile;
        };
        
        //
        // This method returns you segments in the form of note vectors.  Each element of the
        // returned vector is a segment.
        //
        vector<IMUSANT_note_vector> getSegmentsAsNoteVectors();
        
        //
        // This method returns you segments including each of the profile
        // vectors for each segment. Each element of the
        // returned vector is a segment.
        //
        vector<IMUSANT_consolidated_interval_profile_vector_LBDM> getSegmentsWithProfileVectors();
        
        //
        // This method returns you segments with the weighted averages isolated
        // in the segments attribute of the return value. Each element of the
        // returned vector is a segment.
        //
        vector<IMUSANT_strength_vector> getSegmentsWithWeightedAverages();
        
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
        
        IMUSANT_pitch_interval_profile pitch_interval_profile;
        IMUSANT_IOI_interval_profile ioi_interval_profile;
        IMUSANT_rest_interval_profile rest_interval_profile;
 
    private:
        
        S_IMUSANT_part fPart;
        IMUSANT_strength_vector overall_local_boundary_strength_profile;
        
        const double WEIGHT_INTERONSET_INTERVAL = 0.5;
        const double WEIGHT_PITCH = 0.25;
        const double WEIGHT_REST = 0.25;
        
        int SEGMENT_BOUNDARY_CALCULATION_SPAN = 4;
        
        
        // IOI's calculated using Duration.asAbsoluteNumeric() on each Note.
        // Pitch is calculated using a numeric representation of Pitch (MIDI)
        // Rests are calculated using the getType property of IMUSANT_note.
        void buildIntervalProfiles();
        
        void calculateOverallLocalBoundaryStrengthVector();

        void getSegmentsUsingVisitor(IMUSANT_consolidated_interval_profile_LBDM_visitor &visitor);
        
        int             findNextSegmentBoundary(int start_index);
        bool            isThisASegmentBoundary(int strength_profile_index_position) const;
        int             getArrayPositionsWithoutOverflowingLowerBound(int index_position, int span) const;
        int             getArrayPositionsWithoutOverflowingUpperBound(int index_position, int span) const;

    };
    
    typedef IMUSANT_SMARTP<IMUSANT_segmented_part_LBDM> S_IMUSANT_segmented_part_LBDM;
    IMUSANT_SMARTP<IMUSANT_segmented_part_LBDM> new_IMUSANT_segmented_part_LBDM(SetOfSegment & segmentation_results);
}

#endif /* defined(__imusant__IMUSANT_segmented_part_LBDM__) */
