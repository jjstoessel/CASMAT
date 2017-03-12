//
//  CATSMAT_CanonicTools.cpp
//  catsmat
//
//  Created by Jason James Stoessel on 10/03/2017.
//
//
#include <algorithm>
#include "CATSMAT_canonic_tools.hpp"
#include "IMUSANT_segmented_part_fixed_period.h"
#include "IMUSANT_interval_vector.h"
// #define OUTPUT(s) cout << s;
#define OUTPUT(s)
#define YES_NO(s) ( s ? "yes" : "no" )

namespace CATSMAT
{

    bool
    CATSMAT_CanonicTools::
    Initialise(S_IMUSANT_score the_score, double error_threshold)
    {
        score_ = the_score;
        error_threshold_ = error_threshold;
        IMUSANT_vector<S_IMUSANT_part>& parts = the_score->partlist()->parts();
        
        if (parts.size() <= 1)
        {
            return false;
        }
        
        // adapted from IMUSANT_segmented_part_fixed_period
        // Sort the parts in the order in which they enter...
        IMUSANT_partlist_ordered_by_part_entry part_sorter;
        vector<IMUSANT_PartEntry> parts_in_entry_order = part_sorter.getPartsInOrder(the_score);
        
        for (vector<IMUSANT_PartEntry>::iterator first_part_index = parts_in_entry_order.begin(); first_part_index!=parts_in_entry_order.end() ; first_part_index++ )
        {
            for (auto second_part_index = first_part_index + 1; second_part_index != parts_in_entry_order.end() ; second_part_index++)
            {
                Detect_Canon_Type(*first_part_index, *second_part_index, error_threshold);
            }
        }
        
        return true;
    }
    
    void
    CATSMAT_CanonicTools::
    Detect_Canon_Type(IMUSANT_PartEntry& first_part, IMUSANT_PartEntry& second_part, double error_threshold)
    {
        OUTPUT("+++++  Detecting canon between Part " +
               first_part.Part->getPartName() +
               " and Part " +
               second_part.Part->getPartName() +
               " +++++\n" +
               "Error Threshold = " +
               std::to_string(error_threshold) +
               "\n") ;
        CATSMAT_Canon_Type canon_type;
        
        canon_type.imitative_ = IsIntervallicallyExact(first_part, second_part, error_threshold);
        canon_type.retrograde_ = IsRetrograde(first_part, second_part, error_threshold);
        canon_type.contrary_motion_ = IsInversion(first_part, second_part, error_threshold);
        
        //exit if there is/are no melodic transformation(s) present so if cannot be canonic
        if (!(canon_type.imitative_ | canon_type.retrograde_ | canon_type.contrary_motion_)) return;
        
        //add pointers to parts in score - potentially dangerous if score removed from memory
        canon_type.parts_.push_back(first_part.Part);
        canon_type.parts_.push_back(second_part.Part);
        
        //NB. IMUSANT_PartEntry::Part->getPartName() is unreliable for obtaining a unique identifier
        
        canon_type.strict_ = canon_type.imitative_ && IsRhythmicallyExact(first_part, second_part, error_threshold);
        
        if (canon_type.imitative_)
        {
            //find the interval of imitation and IOI
            IMUSANT_interval interval = GetIntervalBetweenParts(first_part, second_part);
            canon_type.intervals_.push_back(interval);
            
            if (!IMUSANT_segmented_part_fixed_period::partsEnterTogether(first_part, second_part))
            {
                //calculate ioi_unit and ioi_unit_count
                IMUSANT_duration ioi = *IMUSANT_segmented_part_fixed_period::calculateEntryOffsetBetweenParts(first_part, second_part);
                IMUSANT_duration ioi_unit;
                
                ioi_unit = CalculateIOIUnit(first_part, second_part);
                
                if(ioi_unit!= IMUSANT_duration()) //only insert if ioi_unit was calculated
                {
                    int ioi_unit_count = ioi.asAbsoluteNumeric()/ioi_unit.asAbsoluteNumeric();
                
                    CATSMAT_Canon_Type::CATSMAT_IOI_pair ioi_pair = std::make_pair(ioi_unit, ioi_unit_count);
                    canon_type.ioi_pairs_.push_back(ioi_pair);
                }
            }
            
            if (!canon_type.strict_)
            {
                TRational proportion;
                
                if (IsProportionalCanon(first_part, second_part, proportion, error_threshold))
                {
                    //Can be either a simultaneous mensuration, proportion, inversion, retrograde or retrograde inversion canon OR not a canon at all
                    //canon_type.ioi_ defaults to zero
                    canon_type.proportional_ = true;
                    canon_type.proportions_.push_back(proportion); //needs to get relation between notes.
                }
                else if (IsMensurationCanon(first_part, second_part, error_threshold))
                {
                    //store result
                    //currently not detected - revisit
                }
            }
            
            Insert(canon_type);
            return;
        }
        
        if (canon_type.retrograde_)
        {
        }
        
        if (canon_type.contrary_motion_)
        {
            
        }
        Insert(canon_type);
    }

    void
    CATSMAT_CanonicTools::
    Insert(CATSMAT_Canon_Type insert_canon_type)
    {
        bool complementary_found = false;
        
        for ( vector<CATSMAT_Canon_Type>::iterator known_canon_type = canon_types_.begin();
                                                   known_canon_type!= canon_types_.end();
                                                   known_canon_type++)
        {
            std::sort(known_canon_type->parts_.begin(), known_canon_type->parts_.end());
            std::sort(insert_canon_type.parts_.begin(), insert_canon_type.parts_.end());
            if (std::includes(known_canon_type->parts_.begin(), known_canon_type->parts_.end(), insert_canon_type.parts_.begin(),insert_canon_type.parts_.end())) return; //all canonic relations already known between part
            
            vector<S_IMUSANT_part> different_parts;
            std::set_difference(known_canon_type->parts_.begin(), known_canon_type->parts_.end(), insert_canon_type.parts_.begin(), insert_canon_type.parts_.end(), std::inserter(different_parts,different_parts.begin()));
            
            if (!different_parts.empty())
            {
                complementary_found = true; //the insert canon type has something in common with a known canon type
                //at least one part of the insertable canonic pair is already canonic with another part in a known pair
                for (vector<S_IMUSANT_part>::const_iterator insert_part = different_parts.begin();
                     insert_part != different_parts.end();
                     insert_part++)
                {
                    
                    //pointer to part already stored
                    //add another part pointer - use merge, unique method. NB. source vectors must be sorted
                    vector<S_IMUSANT_part> results;
                    results.resize(known_canon_type->parts_.size()+insert_canon_type.parts_.size());
                    std::merge(known_canon_type->parts_.begin(), known_canon_type->parts_.end(),
                               insert_canon_type.parts_.begin(), insert_canon_type.parts_.end(),
                               results.begin());
                    auto it = std::unique(results.begin(), results.end(), [](S_IMUSANT_part l, S_IMUSANT_part r) { return l==r; });
                    results.resize(std::distance(results.begin(),it));
                    known_canon_type->parts_.clear();
                    known_canon_type->parts_.assign(results.begin(),results.end());
                    known_canon_type->number_of_voices_ = results.size();
                    
                    //add a different interval to canon_type if required
                    for (IMUSANT_interval val : insert_canon_type.intervals_)
                    {
                        auto it = std::find(known_canon_type->intervals_.begin(), known_canon_type->intervals_.end(), val);
                        
                        //is it a stacked canon - assume ordered ascend/descending entry
                        for (IMUSANT_interval known_int : known_canon_type->intervals_)
                        {
                            if (known_int == IMUSANT_interval(IMUSANT::IMUSANT_interval::unison)) break; // unison canons x>2 in 1 are technically stacked!
                            
                            for (int i = 1; i < known_canon_type->number_of_voices_-1; i++)
                            {
                                known_int += known_int; //effectively multiply interval by i
                                auto insert_result = std::find(insert_canon_type.intervals_.begin(), insert_canon_type.intervals_.end(), known_int);
                                if (insert_result!=insert_canon_type.intervals_.end()) {
                                    known_canon_type->stacked_ = true;
                                    break;
                                }
                            }
                        }
                        
                        //insert interval if not already known
                        if ( it==known_canon_type->intervals_.end() && !known_canon_type->stacked_)
                        {
                            IMUSANT_interval in = *insert_canon_type.intervals_.begin();
                            known_canon_type->intervals_.push_back(val);
                        }
                    }
                    
                    //add a different ioi if required - but only if different to no of vv. * ioi_
                    for (CATSMAT_Canon_Type::CATSMAT_IOI_pair insert_ioi_pair : insert_canon_type.ioi_pairs_)
                    {
                        int expected_ioi_count = insert_ioi_pair.second/(known_canon_type->number_of_voices_-1);
                        CATSMAT_Canon_Type::CATSMAT_IOI_pair expected_ioi_pair = std::make_pair(insert_ioi_pair.first, expected_ioi_count);
                        auto found_ioi_pair = std::find(known_canon_type->ioi_pairs_.begin(), known_canon_type->ioi_pairs_.end(), expected_ioi_pair);
                        if (found_ioi_pair==known_canon_type->ioi_pairs_.end())
                            known_canon_type->ioi_pairs_.push_back(insert_ioi_pair);
                    }
                }
            }
        }
        
        if (!complementary_found) canon_types_.push_back(insert_canon_type);//if we get to here insert needed
    }

    bool
    CATSMAT_CanonicTools::
    IsMelodicallyExact(IMUSANT_PartEntry& first_part, IMUSANT_PartEntry& second_part, double error_threshold)
    {
        IMUSANT_vector<S_IMUSANT_note> part_one_notes = first_part.Part->notes();
        IMUSANT_vector<S_IMUSANT_note> part_two_notes = second_part.Part->notes();
        
        int first_part_index = first_part.EntryVectorIndexPosition;
        int second_part_index = second_part.EntryVectorIndexPosition;
        
        S_IMUSANT_note n1;
        S_IMUSANT_note n2;
        
        int num_non_matching_notes = 0;
        
        while (first_part_index < part_one_notes.size() - second_part_index
               &&
               second_part_index < part_two_notes.size() )
        {
            n1 = part_one_notes[first_part_index++];
            n2 = part_two_notes[second_part_index++];
            
            
            OUTPUT("Comparing " + n1->pretty_print() + " to " + n2->pretty_print());
            
            if (! (*n1 == *n2))
            {
                num_non_matching_notes++;
                OUTPUT(" ---  DIFFERENT --- ");
            }
            
            OUTPUT(endl);
            
        }
        
        return IMUSANT_segmented_part_fixed_period::errorRateIsAcceptable(error_threshold,num_non_matching_notes, part_one_notes.size());
    }
    
    bool
    CATSMAT_CanonicTools::
    IsRhythmicallyExact(IMUSANT_PartEntry& first_part, IMUSANT_PartEntry& second_part, double error_threshold)
    {
        IMUSANT_vector<S_IMUSANT_note> part_one_notes = first_part.Part->notes();
        IMUSANT_vector<S_IMUSANT_note> part_two_notes = second_part.Part->notes();
        
        int first_part_index = first_part.EntryVectorIndexPosition;
        int second_part_index = second_part.EntryVectorIndexPosition;
        
        S_IMUSANT_note n1;
        S_IMUSANT_note n2;
        
        int num_non_matching_notes = 0;
        
        while (first_part_index < part_one_notes.size() - second_part_index
               &&
               second_part_index < part_two_notes.size() )
        {
            n1 = part_one_notes[first_part_index++];
            n2 = part_two_notes[second_part_index++];
            
            
            OUTPUT("Comparing " + n1->pretty_print() + " to " + n2->pretty_print());
            
            if (! (*n1->duration() == *n2->duration()))
            {
                num_non_matching_notes++;
                OUTPUT(" ---  DIFFERENT --- ");
            }
            
            OUTPUT(endl);
            
        }
        
        return IMUSANT_segmented_part_fixed_period::errorRateIsAcceptable(error_threshold,num_non_matching_notes, part_one_notes.size());
    }

    
    bool
    CATSMAT_CanonicTools::
    IsIntervallicallyExact(IMUSANT_PartEntry& first_part, IMUSANT_PartEntry& second_part, double error_threshold)
    {
        IMUSANT_vector<S_IMUSANT_note> part_one_notes = first_part.Part->notes();
        IMUSANT_vector<S_IMUSANT_note> part_two_notes = second_part.Part->notes();
        
        S_IMUSANT_interval_vector first_part_intervals = new_IMUSANT_interval_vector();
        S_IMUSANT_interval_vector second_part_intervals = new_IMUSANT_interval_vector();
        
        //this conversion does not enter rests, so compare directly
        first_part_intervals->add(part_one_notes);
        second_part_intervals->add(part_two_notes);
    
        int num_non_matching_intervals = 0;
        auto part_one_interval = first_part_intervals->getIntervals().begin();
        auto part_two_interval = second_part_intervals->getIntervals().begin();
        
        while( part_one_interval != first_part_intervals->getIntervals().end())
        {
            
            OUTPUT("Comparing " + part_one_interval->pretty_print() + " to " + part_two_interval->pretty_print());
            
            if (! (*part_one_interval == *part_two_interval))
            {
                num_non_matching_intervals++;
                OUTPUT(" ---  DIFFERENT --- ");
            }
            
            part_one_interval++;
            part_two_interval++;
            
            OUTPUT(endl);
            
        }
        
        return IMUSANT_segmented_part_fixed_period::errorRateIsAcceptable(error_threshold,num_non_matching_intervals, first_part_intervals->getIntervals().size());
    }


    IMUSANT_interval
    CATSMAT_CanonicTools::
    GetIntervalBetweenParts(IMUSANT_PartEntry& first_part, IMUSANT_PartEntry& second_part)
    {
        
        IMUSANT_vector<S_IMUSANT_note> part_one_notes = first_part.Part->notes();
        IMUSANT_vector<S_IMUSANT_note> part_two_notes = second_part.Part->notes();
        
        int first_part_index = first_part.EntryVectorIndexPosition;
        int second_part_index = second_part.EntryVectorIndexPosition;
        
        S_IMUSANT_note n1;
        S_IMUSANT_note n2;
        
        n1 = part_one_notes[first_part_index];
        n2 = part_two_notes[second_part_index];
        
        IMUSANT_interval interval(n1->pitch(),n2->pitch());
        
        return interval;
    }
    
    bool
    CATSMAT_CanonicTools::
    IsRetrograde(IMUSANT_PartEntry& first_part, IMUSANT_PartEntry& second_part, double error_threshold)
    {
        return false; // does nothing for now
    }
    
    bool
    CATSMAT_CanonicTools::
    IsProportionalCanon(IMUSANT_PartEntry& first_part, IMUSANT_PartEntry& second_part, TRational& result, double error_threshold)
    {
        result.set(1,1);
        
        return false; // does nothing for now
    }
    
    bool
    CATSMAT_CanonicTools::
    IsMensurationCanon(IMUSANT_PartEntry& first_part, IMUSANT_PartEntry& second_part, double error_threshold)
    {
        return false; // does nothing for now
    }
    
    bool
    CATSMAT_CanonicTools::
    IsInversion(IMUSANT_PartEntry& first_part, IMUSANT_PartEntry& second_part, double error_threshold)
    {
        return false; // does nothing for now
    }
    
    IMUSANT_duration
    CATSMAT_CanonicTools::
    CalculateIOIUnit(IMUSANT_PartEntry& first_part, IMUSANT_PartEntry& second_part)
    {
        IMUSANT_duration ioi_unit;
        IMUSANT_duration p1_measure_duration, p2_measure_duration;
        IMUSANT_time     time;
        //test first for ioi at measure length
        for (unsigned long i = first_part.EntryMeasureNum-1; i<second_part.EntryMeasureNum; i++)
        {
            IMUSANT_duration measure_dur;
            
            time = first_part.Part->measures()[i]->getTime(); //get time if there
            
            for (S_IMUSANT_note note_ptr : first_part.Part->measures()[i]->notes())
            {
                measure_dur += *note_ptr->duration();
            }
            if (p1_measure_duration!= measure_dur)
                p1_measure_duration = measure_dur;
        }
        
        IMUSANT_duration ioi = *IMUSANT_segmented_part_fixed_period::calculateEntryOffsetBetweenParts(first_part, second_part);
        float ioi_units_float = ioi.asAbsoluteNumeric()/p1_measure_duration.asAbsoluteNumeric();
        int ioi_units = ioi_units_float;
        if ( ioi_units_float > (float)ioi_units || ioi_units_float < (float)ioi_units )
        {
            //ioi unit is smaller than a measure
            IMUSANT_duration submeasure_dur;
            for (unsigned long j = 0; j < second_part.EntryNoteIndex; j++)
            {
                submeasure_dur += *second_part.Part->measures()[second_part.EntryNoteIndex]->notes()[j]->duration();
            }
            ioi_unit = submeasure_dur; //REVISIT
        }
        else
            ioi_unit = p1_measure_duration;
        
        return ioi_unit;
    }
    
    //output stream operator for CATSMAT_Canon_Type
    ostream& operator<< (ostream& os, const CATSMAT_Canon_Type& type )
    {
        os
        << "=== Canonic type ===" << endl
        << "Number of voices: " << type.number_of_voices_ << endl;
        for (CATSMAT_Canon_Type::CATSMAT_IOI_pair unit_count : type.ioi_pairs_)
        {
            os << "IOI count: " << unit_count.second  << " (unit: " << unit_count.first << ")" << endl;
        }
        //os
        //<< "IOI unit: " << type.ioi_unit_ << endl;
        for (IMUSANT_interval interval : type.intervals_)
        {
            os << "Interval: " << interval << endl;
        }
        os
        << "Melodically imitative: " << ( type.imitative_ ? "yes" : "no" ) << endl
        << "Strict: " << YES_NO(type.strict_) << endl
        << "Retrograde: " << YES_NO(type.retrograde_) << endl
        << "Contrary motion: " << YES_NO(type.contrary_motion_) << endl
        << "Proportional: " << YES_NO(type.proportional_) << endl;
        for (TRational proportion : type.proportions_)
        {
            os << "Proportion: " << proportion.toString().c_str() << endl;
        }
        os
        << "Stacked: " << YES_NO(type.stacked_) << endl;
        for (S_IMUSANT_part part : type.parts_ )
        {
            os << "Part: " << part->getPartName() << ", Part ID: " << part->getID() << endl;
        }
        return os;
    }


}