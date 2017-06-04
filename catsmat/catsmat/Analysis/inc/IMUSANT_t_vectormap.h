//
//  IMUSANT_T_VectorMap.hpp
//  catsmat
//
//  Created by Jason Stoessel on 7/03/2017.
//
//

#ifndef IMUSANT_vectormap_hpp
#define IMUSANT_vectormap_hpp

#include <stdio.h>
#include "Visitor.h"
#include "IMUSANT_t_repeated_substring.h"

using namespace Loki;

namespace CATSMAT
{
    template <typename T, class C> //T is type for tree; C is the visited class that provides vectors of T
    class IMUSANT_T_VectorMap :
    public Loki::BaseVisitor,
    public Loki::Visitor<C, void, true>
    {
    public:
        typedef typename IMUSANT_T_RepeatedSubstring<T>::SUBSTR_VECTOR SUBSTR_VECTOR;
        typedef map<int, vector<T> >        id_vec_map;
        
        IMUSANT_T_VectorMap() {}
        ~IMUSANT_T_VectorMap() {}
        
        void Visit(C&);
        id_vec_map&     get_id_vec_map() const { return id_vec_map_; }
        void            set_id_vec_map(const id_vec_map& ivm) { id_vec_map_ = ivm; };
        
    protected:
        
        id_vec_map      id_vec_map_;
    };

}

#endif /* IMUSANT_vectormap_hpp */
