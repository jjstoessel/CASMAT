//
//  TSuffixTreeBuilder.hpp
//  catsmat
//
//  Created by Jason Stoessel on 7/03/2017.
//
//

#ifndef TSuffixTreeBuilder_hpp
#define TSuffixTreeBuilder_hpp

#include <stdio.h>
#include "Loki/Visitor.h"
#include "TRepeatedSubstring.h"

using namespace Loki;

namespace CATSMAT
{
    template <typename T, class C> //T is type for tree; C is the visited class that provides vectors of T
    class TVectorMap :
    public Loki::BaseVisitor,
    public Loki::Visitor<C, void, true>
    {
    public:
        typedef typename TRepeatedSubstring<T>::SUBSTR_VECTOR SUBSTR_VECTOR;
        typedef map<int, vector<T> >        id_vec_map;
        
        TVectorMap() {}
        ~TVectorMap() {}
        
        void Visit(C&);
        id_vec_map&     get_id_vec_map() const { return id_vec_map_; }
        void            set_id_vec_map(const id_vec_map& ivm) { id_vec_map_ = ivm; };
        
    protected:
        
        id_vec_map      id_vec_map_;
    };

}

#endif /* TSuffixTreeBuilder_hpp */
