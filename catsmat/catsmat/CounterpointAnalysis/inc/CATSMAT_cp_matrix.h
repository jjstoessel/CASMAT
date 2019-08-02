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
#include "Loki/Visitor.h"
#include "IMUSANT_pitch.h"
#include "IMUSANT_interval.h"
#include "IMUSANT_note.h"
#include "IMUSANT_interval_vector.h"
#include "CATSMAT_visitable.h"
#include "CATSMAT_chord.h"
#include "IMUSANT_barline.h"
#include "CATSMAT_t_utilities.h"
#include "IMUSANT_score.h"

using namespace IMUSANT;
using namespace Loki;

namespace CATSMAT {
    
    class CATSMAT_cp_matrix : public smartable //make sure const
    {
    public:

        using Matrix = std::list<S_CATSMAT_chord>;
        using Matrix_iterator = Matrix::iterator;

        friend  IMUSANT_SMARTP<CATSMAT_cp_matrix> new_CATSMAT_object<CATSMAT_cp_matrix>();
        friend  std::ostream& operator<< (std::ostream& os, const IMUSANT_SMARTP<CATSMAT_cp_matrix>& elt );
        
        void    addpart();
        void    add(const S_IMUSANT_part& part);
        void	add(const IMUSANT_note& note);
        void    set(const IMUSANT_time& time);
        void    set(const S_IMUSANT_score& score);
        void	clear() { fCPMatrix.clear(); }
        void    reindex();
        
        const   Matrix& getCPmatrix() const { return fCPMatrix; }
        bool    isAccented(const Matrix_iterator& iter, const IMUSANT_duration& beat);
        
        void    print(std::ostream& os);
        unsigned long partCount() const { return fCurrentPart + 1; }
        
        void    setMeasureNumber(long currentMeasure);
        void    setCurrentLeftBarline(IMUSANT_barline::type barline) { fLeftBarline = barline; }
        
        S_IMUSANT_score getScore() const;
        bool    SelfTest();
        
        
    protected:
        //ctors
        CATSMAT_cp_matrix();
        virtual ~CATSMAT_cp_matrix();
        
    private:
        
        void            insert(const IMUSANT_note& note);
        void            split(const IMUSANT_note& note);
        IMUSANT_note    distribute(const IMUSANT_note& note, const S_IMUSANT_note previous_note = nullptr);


        Matrix                              fCPMatrix;            //the contrapuntal matrix; a vector of vectors, each column of which represents a chord;
        S_IMUSANT_score                     fSourceScore = nullptr;  //lookback pointer to source score; do not access if null
        
        //internal strictly private class variables
        int                                 fCurrentPart;
        Matrix::iterator                    fCurrentChord;
        IMUSANT_time                        fCurrentTime;
        long                                fCurrentMeasureNumber;
        IMUSANT_duration                    fCumulativeMeasureDuration;
        IMUSANT_duration                    fMeasureDuration;
        IMUSANT_barline::type               fLeftBarline;
    };

    class CATSMAT_cp_matrix_visitable : public CATSMAT_cp_matrix, public Loki::BaseVisitable<void, DefaultCatchAll, true>
    {
    public:
        LOKI_DEFINE_CONST_VISITABLE()
    };
    
    class CATSMAT_cp_matrix_visitor : public CATSMAT_cp_matrix, public IMUSANT_visitor
    {
    public:
        CATSMAT_cp_matrix_visitor() {}
        ~CATSMAT_cp_matrix_visitor() {}
        
        void visit ( S_IMUSANT_chord& elt );
        void visit ( S_IMUSANT_measure& elt );
        void visit ( S_IMUSANT_barline& );
        void visit ( S_IMUSANT_note& elt );
        void visit ( S_IMUSANT_part& elt );
        void visit ( S_IMUSANT_score& elt );
        
        void visit ( S_IMUSANT_attributes& ) {}
        void visit ( S_IMUSANT_comment& elt ) {}
        void visit ( S_IMUSANT_element& elt ) {}
        void visit ( S_IMUSANT_lyric& elt ) {}
        void visit ( S_IMUSANT_partlist& elt );
    };
    
    typedef IMUSANT_SMARTP<CATSMAT_cp_matrix> S_CATSMAT_cp_matrix;
    typedef IMUSANT_SMARTP<CATSMAT_cp_matrix_visitable> S_CATSMAT_cp_matrix_visitable;
    typedef IMUSANT_SMARTP<CATSMAT_cp_matrix_visitor> S_CATSMAT_cp_matrix_visitor;

    
S_CATSMAT_cp_matrix new_CATSMAT_cp_matrix();
    
} //namespace CATSMAT
#endif /* defined(__CATSMAT_cp_matrix__) */
