//
//  CATSMAT_t_utilities.h
//  imusant
//
//  Created by Jason Stoessel on 10/06/2016.
//
//

#ifndef imusant_CATSMAT_t_utilities_h
#define imusant_CATSMAT_t_utilities_h

#include <map>
#include "CATSMAT_exception.h"
#include "smartpointer.h"

using namespace IMUSANT;

namespace CATSMAT
{

    template<typename A, typename B>
    std::pair<B,A> flip_pair(const std::pair<A,B> &p)
    {
        return std::pair<B,A>(p.second, p.first);
    }

    template<typename A, typename B>
    std::multimap<B,A> flip_map(const std::map<A,B> &src)
    {
        std::multimap<B,A> dst;
        std::transform(src.begin(), src.end(), std::inserter(dst, dst.begin()),
                       flip_pair<A,B>);
        return dst;
    }
    
    template<typename A>
    VEXP IMUSANT_SMARTP<A> new_CATSMAT_object()
    {
        A* o = new A();
        if (o==0) throw catsmat_runtime_error("Unable to allocate CATSMAT object");
        return o;
    }
    
    template <class _InputIterator1, class _InputIterator2, class _BinaryPredicate>
    int
    compare(_InputIterator1 __first1, _InputIterator1 __last1, _InputIterator2 __first2)
    {
        int count = 0;
        for (; __first1 != __last1; ++__first1, (void) ++__first2)
            if (*__first1!=*__first2)
                count++;
        return count;
    }
    
    template <class _InputIterator1, class _InputIterator2, class _BinaryPredicate>
    int
    compare(_InputIterator1 __first1, _InputIterator1 __last1, _InputIterator2 __first2, _BinaryPredicate __pred)
    {
        int count = 0;
        for (; __first1 != __last1; ++__first1, (void) ++__first2)
            if (!__pred(*__first1, *__first2))
                count++;
        return count;
    }

}
#endif
