//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 02.06.15
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#pragma once

#include "../FindFlags.hpp"
#include "../Encoded/DecoderStringFunctions.hpp"
#include "../Utilities/RangeAlgorithms.hpp"
#include "EncodedRange.hpp"
#include "StringTraits.hpp"

#include <JEBDebug/Debug.hpp>

namespace Ystring { namespace Generic {

template <typename It1, typename Enc1, typename It2, typename Enc2>
bool endsWithImpl(EncodedRange<It1, Enc1> str,
                    EncodedRange<It2, Enc2> cmp,
                    std::true_type)
{
    JEB_CHECKPOINT();
    auto strRange = makeReverseRange(str.getRange());
    auto cmpRange = makeReverseRange(cmp.getRange());
    return mismatch(strRange, cmpRange).second == cmpRange.end();
}

template <typename It1, typename Enc1, typename It2, typename Enc2>
bool endsWithImpl(EncodedRange<It1, Enc1> str,
                    EncodedRange<It2, Enc2> cmp,
                    std::false_type)
{
    JEB_CHECKPOINT();
    return Encoded::startsWith(str.getReverseDecoder(),
                               cmp.getReverseDecoder());
}

template <typename It1, typename Enc1, typename It2, typename Enc2>
bool endsWith(EncodedRange<It1, Enc1> str,
                EncodedRange<It2, Enc2> cmp,
                FindFlags_t flags = FindFlags::DEFAULTS)
{
    JEB_CHECKPOINT();
    if (flags == FindFlags::CASE_INSENSITIVE)
        return Encoded::startsWith(str.getReverseDecoder(),
                                   cmp.getReverseDecoder(),
                                   flags);
    else
        return endsWithImpl(
                str, cmp,
                typename CanCompareRawValues<It1, Enc1, It2, Enc2>::type());
}

template <typename It1, typename Enc1, typename It2, typename Enc2>
EncodedRange<It1, Enc1> findImpl(EncodedRange<It1, Enc1> str,
                                 EncodedRange<It2, Enc2> cmp,
                                 std::true_type)
{
    JEB_CHECKPOINT();
    return makeEncodedRange(search(str.getRange(), cmp.getRange()), Enc1());
}

template <typename It1, typename Enc1, typename It2, typename Enc2>
EncodedRange<It1, Enc1> findImpl(EncodedRange<It1, Enc1> str,
                                 EncodedRange<It2, Enc2> cmp,
                                 std::false_type)
{
    JEB_CHECKPOINT();
    auto dec1 = str.getForwardDecoder();
    auto dec2 = cmp.getForwardDecoder();
    return makeEncodedRange(find(dec1, dec2));
}

template <typename It1, typename Enc1, typename It2, typename Enc2>
EncodedRange<It1, Enc1> find(EncodedRange<It1, Enc1> str,
                             EncodedRange<It2, Enc2> cmp,
                             FindFlags_t flags = FindFlags::DEFAULTS)
{
    JEB_CHECKPOINT();
    if (flags == FindFlags::CASE_INSENSITIVE)
        return makeEncodedRange(Encoded::find(str.getForwardDecoder(),
                                              cmp.getForwardDecoder(),
                                              flags));
    else
        return findImpl(
                str, cmp,
                typename CanCompareRawValues<It1, Enc1, It2, Enc2>::type());
}

template <typename It1, typename Enc1, typename It2, typename Enc2>
bool startsWithImpl(EncodedRange<It1, Enc1> str,
                    EncodedRange<It2, Enc2> cmp,
                    std::true_type)
{
    JEB_CHECKPOINT();
    return mismatch(str.getRange(), cmp.getRange()).second == cmp.end();
}

template <typename It1, typename Enc1, typename It2, typename Enc2>
bool startsWithImpl(EncodedRange<It1, Enc1> str,
                    EncodedRange<It2, Enc2> cmp,
                    std::false_type)
{
    JEB_CHECKPOINT();
    return Encoded::startsWith(str.getForwardDecoder(),
                               cmp.getForwardDecoder());
}

template <typename It1, typename Enc1, typename It2, typename Enc2>
bool startsWith(EncodedRange<It1, Enc1> str,
                EncodedRange<It2, Enc2> cmp,
                FindFlags_t flags = FindFlags::DEFAULTS)
{
    JEB_CHECKPOINT();
    if (flags == FindFlags::CASE_INSENSITIVE)
        return Encoded::startsWith(str.getForwardDecoder(),
                                   cmp.getForwardDecoder(),
                                   flags);
    else
        return startsWithImpl(
                str, cmp,
                typename CanCompareRawValues<It1, Enc1, It2, Enc2>::type());
}

}}
