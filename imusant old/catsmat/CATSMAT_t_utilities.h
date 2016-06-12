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

}
#endif