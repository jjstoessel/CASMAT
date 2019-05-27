//
// Created by Jason Stoessel on 2019-05-07.
//

#ifndef CATSMAT_CATSMAT_DYAD_SKELETON_H
#define CATSMAT_CATSMAT_DYAD_SKELETON_H

#include <ostream>
#include "CATSMAT_dyad_sequences_base.h"
using namespace IMUSANT;

namespace CATSMAT
{
    typedef vector<S_IMUSANT_interval_vector> CATSMAT_interval_cluster;

    class CATSMAT_dyad_skeleton : public CATSMAT_dyad_sequences_base<CATSMAT_interval_cluster>
    {
    public:
        CATSMAT_dyad_skeleton(const IMUSANT_duration &cluster_duration_);
        virtual ~CATSMAT_dyad_skeleton();

        const IMUSANT_duration &getCluster_duration_() const;
        void  setCluster_duration_(const IMUSANT_duration &cluster_duration_);

        friend ostream &operator<<(ostream &os, const CATSMAT_dyad_skeleton &skeleton);
        void Visit(const CATSMAT_cp_matrix &matrix) override;
        void Print(ostream &os) const override;
    private:

        void process(const list<S_CATSMAT_chord>& matrix);

        IMUSANT_duration cluster_duration_;
        unsigned long    part_count_;
    };
}



#endif //CATSMAT_CATSMAT_DYAD_SKELETON_H
