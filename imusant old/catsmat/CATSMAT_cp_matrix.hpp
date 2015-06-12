/*
 *  CATSMAT_cp_matrix.h
 *  imusant
 *
 *  Created by Jason Stoessel on 29/01/2015.
 *
 *  Vector class for handling contrapuntal units: dyads, triads, etc.
 *
 *
 */

#ifndef __CATSMAT_cp_matrix__
#define __CATSMAT_cp_matrix__

#include <stdio.h>

#include "smartpointer.h"
#include "Visitor.h"
#include "IMUSANT_pitch.h"
#include "IMUSANT_interval.h"
#include "IMUSANT_note.h"
#include "IMUSANT_chord.h"
#include "IMUSANT_interval_vector.h"
#include "CATSMAT_visitable.hpp"

using namespace std;
using namespace IMUSANT;
using namespace Loki;

namespace CATSMAT {
    
class CATSMAT_cp_matrix : public smartable, public BaseVisitable<void, DefaultCatchAll, true> //make sure const
{
public:
    
    LOKI_DEFINE_CONST_VISITABLE()
    
    friend  SMARTP<CATSMAT_cp_matrix> new_CATSMAT_cp_matrix();
    friend  ostream& operator<< (ostream& os, const SMARTP<CATSMAT_cp_matrix>& elt );
    
    bool    addpart();
    bool	add(const IMUSANT_note& note);
    void    set(const IMUSANT_time& time) { fCurrentTime = time; }
    void	clear() { fCPMatrix.clear(); }
    
    const   list< S_IMUSANT_chord >& getCPmatrix() const { return fCPMatrix; }
    const   vector<S_IMUSANT_interval_vector> getVerticalIntervals() const { return fVIntervalVector; }
    
    void    print(ostream& os);
    unsigned long partCount() const { return fCurrentPart; }
    
protected:
    //ctors
            CATSMAT_cp_matrix();
    virtual ~CATSMAT_cp_matrix();
    
private:
    
    bool            insert(const IMUSANT_note& note);
    void            split(const IMUSANT_note& note);
    IMUSANT_note    distribute(const IMUSANT_note& note);

    
    list< S_IMUSANT_chord >             fCPMatrix; //a vector of vectors, each of which represent a chord
    vector<S_IMUSANT_interval_vector>   fVIntervalVector;
    
    unsigned long                       fCurrentPart;
    list<S_IMUSANT_chord>::iterator     fCurrentChord;
    IMUSANT_time                        fCurrentTime;
    
};

typedef SMARTP<CATSMAT_cp_matrix> S_CATSMAT_cp_matrix;
    
S_CATSMAT_cp_matrix new_CATSMAT_cp_matrix();
    
} //namespace CATSMAT
#endif /* defined(__CATSMAT_cp_matrix__) */
