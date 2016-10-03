/*
 *  IMUSANT_score.cpp
 *  imusant
 *
 *  Created by Jason Stoessel on 23/05/06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#include "IMUSANT_score.h"

namespace IMUSANT
{

    S_IMUSANT_score new_IMUSANT_score(const string& movtTitle)
            { IMUSANT_score* o = new IMUSANT_score(movtTitle); assert (o!=0); return o; }

    ostream& operator<<(ostream& os, S_IMUSANT_score& score)
    {
        score->print(os);
        
        return os;
    }

    IMUSANT_score::IMUSANT_score( const string& movtTitle) 
        : fMovementTitle(movtTitle)
    {
        fPartList = new_IMUSANT_partlist();
    }

    void IMUSANT_score::accept(IMUSANT_visitor& visitor)
    {
        S_IMUSANT_score sptr(this);
        visitor.visit(sptr);
    }
    
    bool
    IMUSANT_score::
    getPartById(string partId, S_IMUSANT_part& output_part)
    {
        IMUSANT_vector<S_IMUSANT_part> part_vector = partlist()->parts();
        bool found = false;
        for (unsigned index = 0 ; index < part_vector.size() && !found;  index++ )
        {
            if (part_vector[index]->getID() == partId)
            {
                found = true;
                output_part = part_vector[index];
            }
        }
        return found;
    }

    void	IMUSANT_score::print(ostream& os)
    {
        os << "<IMUSANT 1.0>" << endl;
        os << "Work title: " << fWorkTitle << endl;
        os << "Work No.: " << fWorkNum << endl;
        os << "Movement Title: " << fMovementTitle << endl;
        os << "Movement Number: " << fMovementNum << endl;
        //os << "Composer: " << fCreator << endl;
        //os << "Rights: " << fRights << endl;
        os << "Comments: " << fScoreComments << endl;
        os << "Source: " << fSource << endl;
        os << "Editor: " << fEditor << endl;
        os << "Date: " << fDate << endl;
        
        if (fPartList)
            fPartList->print(os);
        else
            os << "Without parts" << endl;
        
        os << "<\\IMUSANT 1.0>" << endl;
        
    }

} //namespace IMUSANT