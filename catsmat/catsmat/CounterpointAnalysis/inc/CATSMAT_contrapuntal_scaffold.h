//
// Created by Jason Stoessel on 2019-05-07.
//

#ifndef CATSMAT_CATSMAT_CONTRAPUNTAL_SCAFFOLD_H
#define CATSMAT_CATSMAT_CONTRAPUNTAL_SCAFFOLD_H

#include <ostream>
#include "CATSMAT_dyad_sequences_base.h"

using namespace IMUSANT;

namespace CATSMAT
{
    typedef vector<S_IMUSANT_interval_vector> CATSMAT_interval_cluster;

    class CATSMAT_contrapuntal_scaffold : public CATSMAT_dyad_sequences_base<CATSMAT_interval_cluster>
    {
    public:
        enum CR_type { dynamic, regular, salami };
        
        CATSMAT_contrapuntal_scaffold(const IMUSANT_duration &cluster_duration_);
        virtual ~CATSMAT_contrapuntal_scaffold();

        const IMUSANT_duration &getCluster_duration_() const;
        void  setCluster_duration_(const IMUSANT_duration &cluster_duration_);
        const CR_type getContrapuntalRhythm() const { return cr_; }
        void  setContrapuntalRhythm(const CR_type type) { cr_=type; }
        
        friend ostream &operator<<(ostream &os, const CATSMAT_contrapuntal_scaffold &skeleton);
        void Visit(const CATSMAT_cp_matrix &matrix) override;
        void Print(ostream &os) const override;
        
    private:

        void process(const list<S_CATSMAT_chord>& matrix);

        CR_type          cr_;
        IMUSANT_duration cluster_duration_;
        unsigned long    part_count_;
    };
}



#endif //CATSMAT_CATSMAT_CONTRAPUNTAL_SCAFFOLD_H
