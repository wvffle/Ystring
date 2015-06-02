//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 02.06.15
//
// This file is distributed under the BSD License.
// License text is included with the source distribution.
//****************************************************************************
#pragma once

#include "../FindFlags.hpp"
#include "../Utilities/RangeAlgorithms.hpp"
#include "EncodedRange.hpp"

namespace Ystring { namespace Generic {

template <typename It1, typename Enc1,
          typename It2, typename Enc2>
EncodedRange<It1, Enc1> findImpl(
        EncodedRange<It1, Enc1> str,
        EncodedRange<It2, Enc2> cmp,
        std::true_type)
{
    return makeEncodedRange(search(str.getRange(), cmp.getRange()), Enc1());
}

template <typename It1, typename Enc1,
          typename It2, typename Enc2>
EncodedRange<It1, It1> findImpl(
        EncodedRange<It1, Enc1> str,
        EncodedRange<It2, Enc2> cmp,
        std::false_type)
{
    auto dec1 = str.getForwardDecoder();
    auto dec2 = cmp.getForwardDecoder();
    return find(dec1, dec2).getRange();
}

template <typename It1, typename Enc1,
          typename It2, typename Enc2>
EncodedRange<It1, It1> find(
        EncodedRange<It1, Enc1> str,
        EncodedRange<It2, Enc2> sub,
        FindFlags_t flags = FindFlags::DEFAULTS)
{
    if (flags == FindFlags::CASE_INSENSITIVE)
        return findCaseInsensitive(str, sub);
    else
        return findImpl(str, sub,
                        CanCompareRawValues<It1, Enc1, It2, Enc2>::type());
}

}}
