//
//  CATSMAT_score_profile_special.cpp
//  catsmat
//
//  Created by Jason Stoessel on 16/3/17.
//
//

#include <stdio.h>
#include "CATSMAT_score_profile.hpp"
#include "CATSMAT_score_profile.tpp"
#include "IMUSANT_generalised_interval.h"
#include "CATSMAT_TrigramSequences.hpp"
#include "IMUSANT_contour_symbol.h"

namespace CATSMAT {
    
    //explicit instantiations of templated classes
    template class CATSMAT_score_profile<IMUSANT_pitch>;
    template class CATSMAT_score_profile<IMUSANT_interval>;
    template class CATSMAT_score_profile<IMUSANT_duration>;
    template class CATSMAT_score_profile<IMUSANT_generalised_interval>;
    template class CATSMAT_score_profile<IMUSANT_contour_symbol>;
    
    //Specialisation of CATSMAT_score_profile::print for CATSMAT_TrigramSequences::Token
    //required to ensure that trigram is printed (operator<<) rather than token

    template<>
    void
    CATSMAT_score_profile<typename CATSMAT_TrigramSequences::Token>::
    print(ostream& os) const
    {
        ostringstream header,lines,total;
        header << fType << fDelimiter;
        total << "Total" << fDelimiter;
        
        for (std::pair<CATSMAT_TrigramSequences::Token, int> data : fProfile)
        {
            CATSMAT_TrigramSequences::Trigram trigram = CATSMAT_TrigramSequences::Token2Triple(data.first);
            //add pitch name to header
            header << trigram << fDelimiter;
            total << data.second << fDelimiter;
        }
        
        for (auto s : fPartNames)
        {
            ostringstream line;
            line << s.c_str() << fDelimiter;
            
            for (auto data : fProfile)
            {
                CATSMAT_TrigramSequences::Token t = data.first; //pitch type
                //search table for occurrences of pitch in part
                auto it = std::find_if(fTable.begin(), fTable.end(), [&s,&t](const TABLE_TUPLE& item)
                                       {
                                           return s == get<0>(item) && t == get<1>(item);
                                       }); //returns iterator
                if (it!=fTable.end())
                    line << get<2>(*it) << fDelimiter;
                else //not found
                    line << "0" << fDelimiter;
                
            }
            
            lines << line.str() << endl;
        }
        
        header << endl;
        
        os << header.str();
        os << lines.str();
        os << total.str() << endl;
    }
    
    /*n3376 14.7.3/6
    
    If a template, a member template or a member of a class template is explicitly specialized then that specialization shall be declared before the first use of that specialization that would cause an implicit instantiation to take place, in every translation unit in which such a use occurs; no diagnostic is required.*/
    
    template class CATSMAT_score_profile<CATSMAT_TrigramSequences::Token>;
    
    template<>
    void
    CATSMAT_score_profile<typename std::pair<IMUSANT_contour_symbol, IMUSANT_contour_symbol> >::
    print(ostream& os) const
    {
        ostringstream header,lines,total;
        header << fType << fDelimiter;
        total << "Total" << fDelimiter;
        
        for (std::pair<std::pair<IMUSANT_contour_symbol, IMUSANT_contour_symbol>, int> data : fProfile)
        {
            //CATSMAT_TrigramSequences::Trigram trigram = CATSMAT_TrigramSequences::Token2Triple(data.first);
            //add pitch name to header
            //header << trigram << fDelimiter;
            total << data.second << fDelimiter;
        }
        
        for (auto s : fPartNames)
        {
            ostringstream line;
            line << s.c_str() << fDelimiter;
            
            for (auto data : fProfile)
            {
                std::pair<IMUSANT_contour_symbol, IMUSANT_contour_symbol> t = data.first; //pitch type
                //search table for occurrences of pitch in part
                auto it = std::find_if(fTable.begin(), fTable.end(), [&s,&t](const TABLE_TUPLE& item)
                                       {
                                           return s == get<0>(item) && t == get<1>(item);
                                       }); //returns iterator
                if (it!=fTable.end())
                    line << get<2>(*it) << fDelimiter;
                else //not found
                    line << "0" << fDelimiter;
                
            }
            
            lines << line.str() << endl;
        }
        
        header << endl;
        
        os << header.str();
        os << lines.str();
        os << total.str() << endl;
    }
    
    template class CATSMAT_score_profile<std::pair<IMUSANT_contour_symbol, IMUSANT_contour_symbol> >;


}
