//
//  CATSMAT_sonority.cpp
//  imusant
//
//  Created by Jason Stoessel on 30/05/2016.
//
//

#include "CATSMAT_chord.h"


namespace CATSMAT
{
    
    S_CATSMAT_chord new_CATSMAT_chord()
    {
        CATSMAT_chord* o = new CATSMAT_chord(); assert(o!=0); return o;
    }
    
    void	CATSMAT_chord::print(ostream& os) const
    {
        os << "<CHRD>" << endl;
        
        for (auto note=this->begin(); note!=this->end(); note++)
        {
            os << " ";
            note->second->print(os);
        }
        
        os << "<\\CHRD>" << endl;
        
    }
    
    void    CATSMAT_chord::print_short(ostream& os) const
    {
        os << "<CHORD/>" << endl;
    }
    
    CATSMAT_chord&
    CATSMAT_chord::operator=(const CATSMAT_chord& rhs)
    {
        for (auto note : rhs)
        {
            S_IMUSANT_note copy = new_IMUSANT_note();
            *copy = *note.second;
            this->insert(std::pair<int, S_IMUSANT_note>(note.first, copy));
        }
        return *this;
    }
}
