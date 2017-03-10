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

namespace CATSMAT
{
    //IMUSANT_SMARTP<CATSMAT_CanonicTools> new_CATSMAT_object();
    
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
    
        bool canon_found = false;
        
        for (vector<IMUSANT_PartEntry>::iterator first_part_index = parts_in_entry_order.begin(); first_part_index!=parts_in_entry_order.end() ; first_part_index++ )
        {
            for (auto second_part_index = first_part_index; second_part_index != parts_in_entry_order.end() ; second_part_index++)
            {
                canon_found = Detect_Canon_Type(*first_part_index, *second_part_index, error_threshold);
            }
        }
        
        return true;
    }
    
    bool
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
        if (!(canon_type.imitative_ | canon_type.retrograde_ | canon_type.contrary_motion_)) return false;
        
        //part name is unreliable as an unique identifier
        canon_type.part_names_.push_back(first_part.Part->getPartName());
        canon_type.part_names_.push_back(second_part.Part->getPartName());
        
        canon_type.strict_ = canon_type.imitative_ && IsRhythmicallyExact(first_part, second_part, error_threshold);
        
        if (canon_type.imitative_)
        {
            //find the interval of imitation and IOI
            IMUSANT_interval interval = GetIntervalBetweenParts(first_part, second_part);
            canon_type.interval_.push_back(interval);
            
            if (!IMUSANT_segmented_part_fixed_period::partsEnterTogether(first_part, second_part))
            {
                IMUSANT_duration ioi = *IMUSANT_segmented_part_fixed_period::calculateEntryOffsetBetweenParts(first_part, second_part);
                canon_type.ioi_.push_back(ioi);
            }
            
            if (!canon_type.strict_)
            {
                if (IsProportionalCanon(first_part, second_part, error_threshold))
                {
                    //Can be either a simultaneous mensuration, proportion, inversion, retrograde or retrograde inversion canon OR not a canon at all
                    //canon_type.ioi_ defaults to zero
                    canon_type.proportional_ = true;
                    canon_type.proportion_ = TRational(); //needs to get relation between notes.
                }
                else if (IsMensurationCanon(first_part, second_part, error_threshold))
                {
                    //store result
                    //currently not detected - revisit
                }
            }
            
            Insert(canon_type);
            return true;
        }
        
        if (canon_type.retrograde_)
        {
        }
        
        if (canon_type.contrary_motion_)
        {
            
        }
        Insert(canon_type);
        return true;
    }

    void
    CATSMAT_CanonicTools::
    Insert(CATSMAT_Canon_Type insert_canon_type)
    {
        bool insert = true;
        
        for ( vector<CATSMAT_Canon_Type>::iterator known_canon_type = canon_types_.begin();
                                                   known_canon_type!= canon_types_.end();
                                                   known_canon_type++)
        {
            
            for ( vector<string>::iterator insert_part_name = insert_canon_type.part_names_.begin();
                 insert_part_name!= insert_canon_type.part_names_.end();
                 insert_part_name++)
            
            {
                for ( vector<string>::iterator known_part_name = known_canon_type->part_names_.begin();
                     known_part_name!= known_canon_type->part_names_.end();
                     known_part_name++)
                {
                    if (*insert_part_name == *known_part_name)
                    {
                        //then the other insert_part_name is also in canon with known_part_names
                        insert = false;
                        std::sort(known_canon_type->part_names_.begin(), known_canon_type->part_names_.end());
                        std::sort(insert_canon_type.part_names_.begin(), insert_canon_type.part_names_.end());
                        vector<string> result;
                        result.resize(known_canon_type->part_names_.size()+insert_canon_type.part_names_.size()-1);
                        std::merge(known_canon_type->part_names_.begin(),
                                   known_canon_type->part_names_.end(),
                                   insert_part_name, //insert_canon_type.part_names_.begin(),
                                   insert_canon_type.part_names_.end(),
                                   result.begin());
                        known_canon_type->number_of_voices_++;
                        vector<IMUSANT_interval>::iterator first, second, val, it;
                        first = known_canon_type->interval_.begin();
                        second = known_canon_type->interval_.end();
                        val = insert_canon_type.interval_.begin();
                        it = std::find(first, second, *val);
                        if ( it==known_canon_type->interval_.end())
                        {
                            IMUSANT_interval in = *insert_canon_type.interval_.begin();
                            insert_canon_type.interval_.push_back(*val);
                        }
                    }
                }
            }
        }
        if (insert == true)
            canon_types_.push_back(insert_canon_type);
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
        
        IMUSANT_interval_vector* first_part_intervals = new_IMUSANT_interval_vector();
        IMUSANT_interval_vector* second_part_intervals = new_IMUSANT_interval_vector();
        
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
    IsProportionalCanon(IMUSANT_PartEntry& first_part, IMUSANT_PartEntry& second_part, double error_threshold)
    {
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

}
