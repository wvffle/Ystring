/* Ystring: generic algorithms and functions
 * Copyright 2014 Jan Erik Breimo
 * All rights reserved.
 *
 * This file is distributed under the Simplified BSD License.
 * License text is included with the source distribution.
 */
#ifndef JEBBASE_ALGORITHMS_ALGORITHMSCPP14_HPP
#define JEBBASE_ALGORITHMS_ALGORITHMSCPP14_HPP

#include <algorithm>
#include <cstddef>
#include <functional>
#include <iterator>
#include <utility>
#include "Ystring/YstringDefinitions.hpp"

/** @file
  * @brief Defines various generic algorithms that are also part of the
  *     C++14 standard.
  */

namespace Ystring { namespace Algorithms {

//template <typename InpIt1, typename InpIt2>
//std::pair<InpIt1, InpIt2> mismatch(InpIt1 beg, InpIt1 end,
//                                   InpIt2 cmpBeg, InpIt2 cmpEnd)
//{
//    while (beg != end && cmpBeg != cmpEnd && *beg == *cmpBeg)
//    {
//        beg++;
//        cmpBeg++;
//    }
//    return std::make_pair(beg, cmpBeg);
//}
//
//template <typename FwdIt1, typename FwdIt2>
//bool equal(FwdIt1 beg, FwdIt1 end,
//           FwdIt2 cmpBeg, FwdIt2 cmpEnd)
//{
//    return Algorithms::mismatch(beg, end, cmpBeg, cmpEnd) ==
//            std::make_pair(end, cmpEnd);
//}
//
//template <typename FwdIt1, typename FwdIt2, typename BinaryPredicate>
//bool equal(FwdIt1 beg, FwdIt1 end,
//           FwdIt2 cmpBeg, FwdIt2 cmpEnd,
//           BinaryPredicate pred)
//{
//    return Algorithms::mismatch(beg, end, cmpBeg, cmpEnd, pred) ==
//            std::make_pair(end, cmpEnd);
//}

}}

#endif
