//
//  IMUSANT_processor.h
//  Base class for processors of IMUSANT collections
//
//  Created by Jason Stoessel on 12/06/2016.
//
//

#ifndef ____IMUSANT_processor__
#define ____IMUSANT_processor__

#include <stdio.h>
#include "boost/multi_array.hpp"
#include "Loki/Visitor.h"
#include "suffixtree.h"
#include "IMUSANT_processing.h"

using namespace std;
using namespace ns_suffixtree;

#define MAX(X,Y) ( (X>Y)? (X) : (Y) ) //move to general macros header

namespace IMUSANT
{
    template <typename T>
    class IMUSANT_processor :
        public Loki::BaseVisitor,
        public Loki::Visitor<IMUSANT_processing, void, true>
    {
    public:
        
        IMUSANT_processor() {}
        ~IMUSANT_processor() { if (mTreePtr!=NULL) delete mTreePtr; }
    
        virtual void    Visit(const IMUSANT_processing&) = 0;
        
        typedef suffixtree< vector<T> >  _tree;
        typedef map<int, vector<T> > ID_vec_map;
        
    protected:
        suffixtree< vector<T> >* buildSuffixTree(const map<int, vector<T> >& id_vec_map);
        
        _tree*       mTreePtr;
        ID_vec_map   mID_vec_map;
    };
    
    typedef boost::multi_array<int, 2> int_2d_array_t;
    
    template<typename T> suffixtree< vector<T> >*
    IMUSANT_processor<T>::
    buildSuffixTree(const map<int, vector<T> >& id_vec_map)
    {
        //get first part from first file
        suffixtree< vector<T> >* tree = NULL;
        
        for (auto i = id_vec_map.begin(); i!=id_vec_map.end(); i++)
        {
            
            if (tree==NULL) {
                tree=new suffixtree< vector<T> >(i->second, i->first);
            }
            else
                tree->add_sentence(i->second, i->first);
        }
        
        return tree;
    }
}
#endif /* defined(____IMUSANT_processor__) */
