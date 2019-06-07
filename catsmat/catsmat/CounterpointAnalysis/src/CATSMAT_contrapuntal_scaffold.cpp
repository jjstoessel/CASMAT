//
// Created by Jason Stoessel on 2019-05-07.
//

#include "CATSMAT_contrapuntal_scaffold.h"
#include "CATSMAT_cp_matrix.h"

namespace CATSMAT
{

CATSMAT_contrapuntal_scaffold::CATSMAT_contrapuntal_scaffold(const IMUSANT_duration &cluster_duration_)
    : cluster_duration_(cluster_duration_)
{

}

CATSMAT_contrapuntal_scaffold::~CATSMAT_contrapuntal_scaffold()
{

}

const IMUSANT_duration &CATSMAT_contrapuntal_scaffold::getCluster_duration_() const
{
    return cluster_duration_;
}

void CATSMAT_contrapuntal_scaffold::setCluster_duration_(const IMUSANT_duration &cluster_duration_)
{
    CATSMAT_contrapuntal_scaffold::cluster_duration_ = cluster_duration_;
}

ostream &operator<<(ostream &os, const CATSMAT_contrapuntal_scaffold &skeleton)
{
    skeleton.Print(os);
    return os;
}

void CATSMAT_contrapuntal_scaffold::Visit(const CATSMAT_cp_matrix &matrix)
{
    part_count_ = matrix.partCount();

    process(matrix.getCPmatrix());
}

void CATSMAT_contrapuntal_scaffold::process(const list<CATSMAT::S_CATSMAT_chord> &matrix)
{
    if (!matrix.empty())
    {
        //allocate temporary storage for each voice pair.
//        vector<S_IMUSANT_interval_vector> interval_vectors[part_count_];
//        while (interval_vectors.size() < ( (part_count_)*(part_count_-1)/2 ) )
//        {
//            interval_vectors->push_back(new_IMUSANT_interval_vector());
//        } //pointers in interval_vectors self-destruct with destructor


        for (auto chord = matrix.begin(); chord!=matrix.end(); chord++)
        {
            map<int, S_IMUSANT_note>::size_type chord_size = (*(*chord)).size();

            int dyad_pair = 0;

            S_IMUSANT_interval_vector chord_intervals = new_IMUSANT_interval_vector();

            vector<S_IMUSANT_interval_vector> interval_vectors;

            for (int i = 0; i<chord_size; i++)
            {
                for (int j=i; ++j<chord_size; /*nothing here*/)
                {
                    map<int, S_IMUSANT_note> chord_notes = *(*chord);

                    IMUSANT_interval interval;

                    interval.setLocation(i,
                                         chord_notes[i]->getMeasureNum(),
                                         chord_notes[i]->getNoteIndex(),
                                         j,
                                         chord_notes[j]->getMeasureNum(),
                                         chord_notes[j]->getNoteIndex());

                    if (chord_notes[i]->getType()!=IMUSANT_NoteType::rest && chord_notes[j]->getType()!=IMUSANT_NoteType::rest)
                    {
                        interval = IMUSANT_interval(chord_notes[j]->pitch(), chord_notes[i]->pitch());
                    }

                    //only insert interval if not a repeated interval
                    if ( (chord_notes[i]->isTiedPrevious() && chord_notes[j]->isTiedPrevious()))
                    {

                    }
                    else
                        interval_vectors[dyad_pair]->add(interval);

                    //
                    //                            !((interval.getQuality()==IMUSANT_interval::dissonant) && (ignore_dissonances_==true))

                    dyad_pair++; //complete iteration through one pair of voices
                }

            }


        }
    }
}

void CATSMAT_contrapuntal_scaffold::Print(ostream &os) const
{

}

} //namespace CATSMAT
