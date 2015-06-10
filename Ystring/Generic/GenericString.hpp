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
#include "../Encoded/Encoder.hpp"
#include "../Utilities/RangeAlgorithms.hpp"
#include "../Utilities/CountingOutputIterator.hpp"
#include "EncodedRange.hpp"
#include "StringTraits.hpp"
#include "StringReference.hpp"

#include <JEBDebug/Debug.hpp>

namespace Ystring { namespace Generic {

template <typename Str, typename It, typename Enc>
void appendLower(StringReference<Str>& dst,
                 Utilities::Range<It> src,
                 Enc encoding)
{
    Encoded::appendLower(
            dst.getEncoder(encoding),
            Encoded::makeReverseDecoder(src, encoding));
}

//template <typename Str, typename It, typename Enc>
//Str lower(Utilities::Range<It> src, Enc encoding)
//{
//    Encoded::appendLower(
//            dst.getEncoder(encoding),
//            Encoded::makeReverseDecoder(src, encoding));
//}

template <typename It, typename Enc>
size_t sizeOfLower(Utilities::Range<It> src, Enc encoding)
{
    size_t n = 0;
    Utilities::CountingOutputIterator<typename Enc::CanonicalType> it(&n);
    Encoded::appendLower(
            Encoded::makeEncoder(it, encoding),
            Encoded::makeForwardDecoder(src, encoding));
    return n;
}


//template <typename Str, typename It2, typename Enc>
//void replace(EncodedString<Str, Enc> dst,
//             EncodedRange<It2, Enc> cmp,)
//{
//    Encoded::appendLower(dst.getEncoder(), src.getForwardDecoder());
//}

template <typename It1, typename It2, typename Enc>
bool endsWithImpl(Utilities::Range<It1> str,
                  Utilities::Range<It2> cmp,
                  Enc encoding,
                  std::true_type)
{
    JEB_CHECKPOINT();
    auto strRange = makeReverseRange(str);
    auto cmpRange = makeReverseRange(cmp);
    return mismatch(strRange, cmpRange).second == cmpRange.end();
}

template <typename It1, typename It2, typename Enc>
bool endsWithImpl(Utilities::Range<It1> str,
                  Utilities::Range<It2> cmp,
                  Enc encoding,
                  std::false_type)
{
    JEB_CHECKPOINT();
    return Encoded::startsWith(Encoded::makeReverseDecoder(str, encoding),
                               Encoded::makeReverseDecoder(cmp, encoding));
}

template <typename It1, typename It2, typename Enc>
bool endsWith(Utilities::Range<It1> str,
              Utilities::Range<It2> cmp,
              Enc encoding,
              FindFlags_t flags = FindFlags::DEFAULTS)
{
    JEB_CHECKPOINT();
    if (flags == FindFlags::CASE_INSENSITIVE)
        return Encoded::startsWith(Encoded::makeReverseDecoder(str, encoding),
                                   Encoded::makeReverseDecoder(cmp, encoding),
                                   flags);
    else
        return endsWithImpl(
                str, cmp, encoding,
                typename SameIteratorValueType<It1, It2>::type());
}

template <typename It1, typename It2, typename Enc>
EncodedRange<It1, Enc> findImpl(EncodedRange<It1, Enc> str,
                                EncodedRange<It2, Enc> cmp,
                                std::true_type)
{
    JEB_CHECKPOINT();
    return makeEncodedRange(search(str.getRange(), cmp.getRange()), Enc());
}

template <typename It1, typename It2, typename Enc>
EncodedRange<It1, Enc> findImpl(EncodedRange<It1, Enc> str,
                                EncodedRange<It2, Enc> cmp,
                                std::false_type)
{
    JEB_CHECKPOINT();
    auto dec1 = str.getForwardDecoder();
    auto dec2 = cmp.getForwardDecoder();
    return makeEncodedRange(find(dec1, dec2));
}

template <typename It1, typename It2, typename Enc>
EncodedRange<It1, Enc> find(EncodedRange<It1, Enc> str,
                            EncodedRange<It2, Enc> cmp,
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
                typename CanCompareRawValues<It1, Enc, It2, Enc>::type());
}


template <typename It1, typename It2, typename Enc>
bool startsWithImpl(EncodedRange<It1, Enc> str,
                    EncodedRange<It2, Enc> cmp,
                    std::true_type)
{
    JEB_CHECKPOINT();
    return mismatch(str.getRange(), cmp.getRange()).second == cmp.end();
}

template <typename It1, typename It2, typename Enc>
bool startsWithImpl(EncodedRange<It1, Enc> str,
                    EncodedRange<It2, Enc> cmp,
                    std::false_type)
{
    JEB_CHECKPOINT();
    return Encoded::startsWith(str.getForwardDecoder(),
                               cmp.getForwardDecoder());
}

template <typename It1, typename It2, typename Enc>
bool startsWith(EncodedRange<It1, Enc> str,
                EncodedRange<It2, Enc> cmp,
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
                typename SameIteratorValueType<It1, It2>::type());
}

}}
