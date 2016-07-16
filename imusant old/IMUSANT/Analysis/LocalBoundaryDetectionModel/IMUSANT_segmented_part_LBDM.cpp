//
//  IMUSANT_segmented_part_LBDM.cpp
//
//  Created by Derrick Hill on 19/03/2016.
//
//  C++ implimentation of Lower Boundary Detection Model as described in
//  Cambouropoulos, Emilios. 2001.
//  "The Local Boundary Detection Model (LBDM) and its Application in the
//   Study of Expressive Timing."
//  In Proceedings of the International Computer Music Conference (ICMC'2001)
//  17-22 September, Havana, Cuba.
//  International Computer Music Association.
//


#include "IMUSANT_segmented_part_LBDM.h"

#include <iomanip>
#include <iostream>

namespace IMUSANT
{
    //
    // IMUSANT_segmented_part_LBDM
    //
    
    vector<float> &
    IMUSANT_segmented_part_LBDM::
    getOverallLocalBoundaryStrengthProfile()
    {
        buildIntervalProfiles();
        calculateOverallLocalBoundaryStrengthVector();
        return overall_local_boundary_strength_profile;
    }
    
    
    void
    IMUSANT_segmented_part_LBDM::
    buildIntervalProfiles()
    {
        IMUSANT_vector<S_IMUSANT_note> notes = fPart->notes();
        
        ioi_interval_profile.initialise(notes.size());
        pitch_interval_profile.initialise(notes.size());
        rest_interval_profile.initialise(notes.size());
        
        for (int index = 0; index < notes.size(); index++)
        {
            ioi_interval_profile.addProfileEntry(index, notes);
            pitch_interval_profile.addProfileEntry(index, notes);
            rest_interval_profile.addProfileEntry(index, notes);
        }
        
        ioi_interval_profile.calculateChangeVector();
        pitch_interval_profile.calculateChangeVector();
        rest_interval_profile.calculateChangeVector();
        
        ioi_interval_profile.calculateStrengthVector();
        pitch_interval_profile.calculateStrengthVector();
        rest_interval_profile.calculateStrengthVector();
        
    }
    
    void
    IMUSANT_segmented_part_LBDM::
    calculateOverallLocalBoundaryStrengthVector()
    {
        overall_local_boundary_strength_profile.clear();
        
        float weighted_avg_strength = 0;
        for (int index = 0; index < ioi_interval_profile.strength_vector.size(); index++)
        {
            weighted_avg_strength =
                (
                 (ioi_interval_profile.strength_vector[index] * WEIGHT_INTERONSET_INTERVAL)
                 +
                 (pitch_interval_profile.strength_vector[index] * WEIGHT_PITCH)
                 +
                 (rest_interval_profile.strength_vector[index] * WEIGHT_REST)
                )
                / 2;
            overall_local_boundary_strength_profile.push_back(weighted_avg_strength);
        }
    }
    
    IMUSANT_consolidated_interval_profile_vector_LBDM
    IMUSANT_segmented_part_LBDM::
    getConsolidatedProfiles()
    {
        IMUSANT_consolidated_interval_profile_vector_LBDM ret_val;
        
        IMUSANT_vector<S_IMUSANT_note> notes = fPart->notes();
        
        for (int index = 0; index < pitch_interval_profile.strength_vector.size(); index++)
        {
            IMUSANT_consolidated_interval_profile_LBDM next_row;
            
            if (index == 0)
            {
                next_row.setStartNote(NULL);
            }
            else
            {
                next_row.setStartNote(notes[index - 1]);
            }
            
            next_row.setEndNote(notes[index]);
            next_row.setPitch(pitch_interval_profile.strength_vector[index]);
            next_row.setIOI(ioi_interval_profile.strength_vector[index]);
            next_row.setRest(rest_interval_profile.strength_vector[index]);
            next_row.setWeightedAverage(overall_local_boundary_strength_profile[index]);
            
            ret_val.push_back(next_row);
        }
        
        return ret_val;
    }
    
    
    vector< IMUSANT_segment >
    IMUSANT_segmented_part_LBDM::
    getSegments()
    {
        vector<IMUSANT_segment> ret_val;
        ret_val = getSegments(getSegmentBoundaries());
        return ret_val;
    }
    
    vector< IMUSANT_segment >
    IMUSANT_segmented_part_LBDM::
    getSegments(vector< int > segment_boundaries)
    {
        // REVISIT
        throw("IMUSANT_segmented_part_LBDM::getSegments(vector< int > segment_boundaries)  - Not implemented yet");
        
        vector<IMUSANT_segment> ret_val;
        
        IMUSANT_segment next_segment;
        
        int next_start_pos = segment_boundaries[0];
        for (int index =  next_start_pos; index < segment_boundaries.size(); index++)
        {
            
        }
        
        return ret_val;
    }
    
    vector< int >
    IMUSANT_segmented_part_LBDM::
    getSegmentBoundaries()
    {
        // REVISIT - assuming that calculateOverallLocalBoundaryStrengthVector() has already been called
        
        vector<int> ret_val;
        int next_start_index = 0;
        
        while (next_start_index < overall_local_boundary_strength_profile.size())
        {
            int new_boundary_index = findNextSegmentBoundary(next_start_index);
            
            ret_val.push_back(new_boundary_index);
            next_start_index = new_boundary_index + 1;
        }
        
        return ret_val;
    }
    
    int
    IMUSANT_segmented_part_LBDM::
    findNextSegmentBoundary(int start_index)
    {
        // Examine the values N positions either side of start_index.
        // If they are all less than the value at start_index, then start_index identifies a segment boundary.
        
        bool found = false;
        int boundary_index = start_index;
        
        while (boundary_index < overall_local_boundary_strength_profile.size() && !found)
        {
            if (isThisASegmentBoundary(boundary_index))
            {
                found = true;
            }
            else
            {
                boundary_index++;
            }
        }
        return boundary_index;
    }
    
    bool
    IMUSANT_segmented_part_LBDM::
    isThisASegmentBoundary(int strength_profile_index_position) const
    {
        int span = SEGMENT_BOUNDARY_CALCULATION_SPAN;
        
        int num_previous_positions_to_examine = getArrayPositionsWithoutOverflowingLowerBound(strength_profile_index_position, span);
        int num_succeeding_positions_to_examine = getArrayPositionsWithoutOverflowingUpperBound(strength_profile_index_position, span);
        
        //
        bool result = true;
        
        for (int index = num_previous_positions_to_examine; index > 0; index--)
        {
            if (overall_local_boundary_strength_profile[strength_profile_index_position] < overall_local_boundary_strength_profile[strength_profile_index_position - index])
            {
                result = false;
            }
        }
        
        for (int index = num_succeeding_positions_to_examine; index > 0 ; index--)
        {
            if (overall_local_boundary_strength_profile[strength_profile_index_position] < overall_local_boundary_strength_profile[strength_profile_index_position + index])
            {
                result = false;
            }
        }
        
        return result;
    }
    
    int
    IMUSANT_segmented_part_LBDM::
    getArrayPositionsWithoutOverflowingLowerBound(int index_position, int span) const
    {
        // make sure we don't overrun the start of the array going backwards;
        int ret_val = (index_position >= span) ? span : index_position;
        return ret_val;
    }
    
    int
    IMUSANT_segmented_part_LBDM::
    getArrayPositionsWithoutOverflowingUpperBound(int index_position, int span) const
    {
        // make sure we don't overrun the end of the array going forwards;
        int ret_val;
        int array_upper_bound = (int) overall_local_boundary_strength_profile.size() - 1;
        
        if (array_upper_bound - index_position > span)
        {
            ret_val = span;
        }
        else
        {
           ret_val = array_upper_bound - index_position;
        }
        
        return ret_val;
    }
    
    IMUSANT_segment
    IMUSANT_segmented_part_LBDM::
    buildSegment(int start_index, int end_index)
    {
        // REVISIT
        throw("IMUSANT_segmented_part_LBDM::buildSegment()  - Not implemented yet");

        IMUSANT_segment ret_val;
        return ret_val;
        
    }
    
    
#define NOTE_WIDTH 28
#define DATA_WIDTH 16
#define SEPARATOR ' '
#define FILL_NOTE left << setw(NOTE_WIDTH) << setfill(SEPARATOR)
#define FILL_DATA right << setw(DATA_WIDTH) << setfill(SEPARATOR) << std::setprecision(2) << std::fixed           // Set the number of decimal places in the putput.
    

    ostream&
    operator<< (ostream& os, const IMUSANT_segmented_part_LBDM& segmented_part)
    {
        os << segmented_part.print(true);
        return os;
    }
    
    string
    IMUSANT_segmented_part_LBDM::
    printForTesting() const
    {
        return print(false);
    }
    
    string
    IMUSANT_segmented_part_LBDM::
    print(bool include_notes, bool include_boundaries) const
    {
        IMUSANT_vector<S_IMUSANT_note> notes = fPart->notes();
        
        stringstream ret_val;
        
        ret_val << "PART NAME - " << fPart->getPartName() << endl;
        
        ret_val << "STRENGTH VECTORS" << endl;
        
        if (include_notes)
        {
            ret_val << FILL_NOTE << "NOTE1" << FILL_NOTE << "NOTE2";
        }
        
        ret_val << FILL_DATA << "PITCH" << FILL_DATA << "IOI" << FILL_DATA << "REST" << FILL_DATA << "WEIGHTED AVG" << endl;
        
        ret_val << "{" << endl ;
        
        for (int index = 0; index < pitch_interval_profile.strength_vector.size(); index++)
        {
            if (include_notes)
            {
                ret_val
                << FILL_NOTE << "{" + (index == 0 ? "-" : notes[index - 1]->pretty_print()) + ","
                << FILL_NOTE << notes[index]->pretty_print() + ",";
            }
            else
            {
                ret_val << "{";
            }
    
            ret_val
            << FILL_DATA << pitch_interval_profile.strength_vector[index] << ","
            << FILL_DATA << ioi_interval_profile.strength_vector[index] << ","
            << FILL_DATA << rest_interval_profile.strength_vector[index] << ","
            << FILL_DATA << overall_local_boundary_strength_profile[index]
            << "},"
            << FILL_DATA << "// " << index;
            
            if (include_boundaries && isThisASegmentBoundary(index))
            {
                ret_val << FILL_DATA << "BOUNDARY";
            }
            
            ret_val << endl;
        }
        
        ret_val << "}" << endl;
        
        return ret_val.str();
    }
    
    
    S_IMUSANT_segmented_part_LBDM new_IMUSANT_segmented_part_LBDM(S_IMUSANT_part the_part)
    {
        IMUSANT_segmented_part_LBDM* o = new IMUSANT_segmented_part_LBDM(the_part);
        assert (o!=0);
        return o;
    }
}