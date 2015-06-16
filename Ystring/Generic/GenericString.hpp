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
            Encoded::makeForwardDecoder(src, encoding));
    dst.terminate();
}

template <typename Str, typename It, typename Enc>
void appendUpper(StringReference<Str>& dst,
                 Utilities::Range<It> src,
                 Enc encoding)
{
    Encoded::appendUpper(
            dst.getEncoder(encoding),
            Encoded::makeForwardDecoder(src, encoding));
    dst.terminate();
}

template <typename Str, typename It, typename Enc>
Str lower(Utilities::Range<It> src, Enc encoding)
{
    auto str = Str();
    auto ref = makeStringReference(str);
    appendLower(ref, src, encoding);
    return str;
}

template <typename Str, typename It, typename Enc>
Str upper(Utilities::Range<It> src, Enc encoding)
{
    auto str = Str();
    auto ref = makeStringReference(str);
    appendUpper(ref, src, encoding);
    return str;
}

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

template <typename It, typename Enc>
size_t sizeOfUpper(Utilities::Range<It> src, Enc encoding)
{
    size_t n = 0;
    Utilities::CountingOutputIterator<typename Enc::CanonicalType> it(&n);
    Encoded::appendUpper(
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
Utilities::Range<It1> findImpl(Utilities::Range<It1> str,
                               Utilities::Range<It2> cmp,
                               Enc encoding,
                               std::true_type)
{
    JEB_CHECKPOINT();
    return search(str, cmp);
}

template <typename It1, typename It2, typename Enc>
Utilities::Range<It1> findImpl(Utilities::Range<It1> str,
                               Utilities::Range<It2> cmp,
                               Enc encoding,
                               std::false_type)
{
    JEB_CHECKPOINT();
    return Encoded::find(
            Encoded::makeForwardDecoder(str, encoding),
            Encoded::makeForwardDecoder(cmp, encoding)).getRange();
}

template <typename It1, typename It2, typename Enc>
Utilities::Range<It1> find(Utilities::Range<It1> str,
                           Utilities::Range<It2> cmp,
                           Enc encoding,
                           FindFlags_t flags = FindFlags::DEFAULTS)
{
    JEB_CHECKPOINT();
    if (flags == FindFlags::CASE_INSENSITIVE)
        return Encoded::find(Encoded::makeForwardDecoder(str, encoding),
                             Encoded::makeForwardDecoder(cmp, encoding),
                             flags).getRange();
    else
        return findImpl(
                str, cmp, encoding,
                typename CanCompareRawValues<It1, Enc, It2, Enc>::type());
}


template <typename It1, typename It2, typename Enc>
bool startsWithImpl(Utilities::Range<It1> str,
                    Utilities::Range<It2> cmp,
                    Enc /*encoding*/,
                    std::true_type)
{
    JEB_CHECKPOINT();
    return mismatch(str, cmp).second == cmp.end();
}

template <typename It1, typename It2, typename Enc>
bool startsWithImpl(Utilities::Range<It1> str,
                    Utilities::Range<It2> cmp,
                    Enc encoding,
                    std::false_type)
{
    JEB_CHECKPOINT();
    return Encoded::startsWith(Encoded::makeForwardDecoder(str, encoding),
                               Encoded::makeForwardDecoder(cmp, encoding));
}

template <typename It1, typename It2, typename Enc>
bool startsWith(Utilities::Range<It1> str,
                Utilities::Range<It2> cmp,
                Enc encoding,
                FindFlags_t flags = FindFlags::DEFAULTS)
{
    JEB_CHECKPOINT();
    if (flags == FindFlags::CASE_INSENSITIVE)
        return Encoded::startsWith(Encoded::makeForwardDecoder(str, encoding),
                                   Encoded::makeForwardDecoder(cmp, encoding),
                                   flags);
    else
        return startsWithImpl(
                str, cmp, encoding,
                typename SameIteratorValueType<It1, It2>::type());
}

}}
