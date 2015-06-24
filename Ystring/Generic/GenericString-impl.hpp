//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 02.06.15
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#pragma once

#include "../Encoded/DecoderStringFunctions.hpp"
#include "../Encoded/Encoder.hpp"
#include "../Encoded/ForwardDecoder.hpp"
#include "../Encoded/ReverseDecoder.hpp"
#include "../Utilities/CountingOutputIterator.hpp"
#include "StringTraits.hpp"

#include <JEBDebug/Debug.hpp>

namespace Ystring { namespace Generic {

template <typename Str, typename Enc>
void append(StringReference<Str>& dst, uint32_t chr, Enc encoding)
{
    auto encoder = dst.getEncoder(encoding);
    encoder.encode(chr);
}

template <typename Str, typename Enc>
void append(StringReference<Str>&& dst, uint32_t chr, Enc encoding)
{
    append(dst, chr, encoding);
}

template <typename Str, typename It1, typename It2>
void appendJoin(StringReference<Str>& dst, It1 first, It1 last,
                Utilities::Range<It2> delimiter)
{
    if (first == last)
        return;

    auto appender = dst.getAppender();
    appender.append(Utilities::makeRange(*first));
    while (++first != last)
    {
        appender.append(delimiter);
        appender.append(Utilities::makeRange(*first));
    }
    dst.terminate();
}

template <typename Str, typename It>
void appendJoin(StringReference<Str>& dst, It first, It last)
{
    auto appender = dst.getAppender();
    for (; first != last; ++first)
        appender.append(Utilities::makeRange(*first));
    dst.terminate();
}

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
void appendTitle(StringReference<Str>& dst,
                 Utilities::Range<It> src,
                 Enc encoding)
{
    Encoded::appendTitle(
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

template <typename It1, typename It2, typename Enc>
int32_t caseInsensitiveCompare(Utilities::Range<It1> str,
                               Utilities::Range<It2> cmp,
                               Enc encoding)
{
    return caseInsensitiveCompare(
            Encoded::makeForwardDecoder(str, encoding),
            Encoded::makeForwardDecoder(cmp, encoding));
}

template <typename It1, typename It2, typename Enc>
bool caseInsensitiveEqual(Utilities::Range<It1> str,
                          Utilities::Range<It2> cmp,
                          Enc encoding)
{
    return caseInsensitiveEqual(Encoded::makeForwardDecoder(str, encoding),
                                Encoded::makeForwardDecoder(cmp, encoding));
}

template <typename It1, typename It2, typename Enc>
bool caseInsensitiveLess(Utilities::Range<It1> str,
                         Utilities::Range<It2> cmp,
                         Enc encoding)
{
    return caseInsensitiveLess(Encoded::makeForwardDecoder(str, encoding),
                               Encoded::makeForwardDecoder(cmp, encoding));
}

template <typename It, typename Enc>
bool contains(Utilities::Range<It> str, uint32_t chr, Enc encoding)
{
    auto dec = Encoded::makeForwardDecoder(str, encoding);
    return Encoded::advanceUntil(dec, [=](uint32_t c){return c == chr;});
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
              FindFlags_t flags)
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
    return Encoded::find(Encoded::makeForwardDecoder(str, encoding),
                         Encoded::makeForwardDecoder(cmp, encoding)
                        ).getRange();
}

template <typename It1, typename It2, typename Enc>
Utilities::Range<It1> find(Utilities::Range<It1> str,
                           Utilities::Range<It2> cmp,
                           Enc encoding,
                           FindFlags_t flags)
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

template <typename Str, typename It1, typename It2>
Str join(It1 first, It1 last, Utilities::Range<It2> delimiter)
{
    auto result = Str();
    auto ref = makeStringReference(result);
    appendJoin(ref, first, last, delimiter);
    return result;
}

template <typename Str, typename It>
Str join(It first, It last)
{
    auto result = Str();
    auto ref = makeStringReference(result);
    appendJoin(ref, first, last);
    return result;
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
Str reverse(Utilities::Range<It> src, Enc encoding)
{
    Str result(getSize(src), 0);
    auto dst = begin(result);
    auto dec = Encoded::makeReverseDecoder(src, encoding);
    while (advanceCharacter(dec))
    {
        src.begin() = dec.end();
        dst = copy(src, dst);
        src.end() = src.begin();
    }
    return result;
}

template <typename It1, typename It2>
size_t sizeOfJoin(It1 first, It1 last, Utilities::Range<It2> delimiter)
{
    size_t n = 0, len = 0;
    for (; first != last; ++first)
    {
        len += getSize(Utilities::makeRange(*first));
        ++n;
    }
    return len + (n - 1) * getSize(delimiter);
}

template <typename It>
size_t sizeOfJoin(It first, It last)
{
    size_t size = 0;
    for (; first != last; ++first)
        size += getSize(Utilities::makeRange(first));
    return size;
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

template <typename Str, typename It, typename Enc>
std::vector<Str> split(
        Utilities::Range<It> str,
        Enc encoding,
        size_t maxParts = 0,
        SplitFlags_t flags = SplitFlags::IGNORE_EMPTY)
{
    std::vector<Str> result;
    auto dec = Encoded::makeForwardDecoder(str, encoding);
    while (maxParts != 1 && str.begin() != str.end())
    {
        auto token = nextToken(dec, Unicode::isWhitespace);
        if (!SplitFlags::ignoreEmpty(flags) || token.begin() != token.end())
        {
            result.emplace_back(token.begin(), token.end());
            --maxParts;
        }
        if (token.end() == str.end())
            return result;
    }
    if ((!SplitFlags::ignoreRemainder(flags)) &&
        (!SplitFlags::ignoreEmpty(flags) || str.begin() != str.end()))
    {
        result.emplace_back(str.begin(), str.end());
    }
    return result;
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
                FindFlags_t flags)
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

template <typename Str, typename It, typename Enc>
Str title(Utilities::Range<It> src, Enc encoding)
{
    auto str = Str();
    auto ref = makeStringReference(str);
    appendTitle(ref, src, encoding);
    return str;
}

template <typename It, typename Enc, typename UnaryPred>
Utilities::Range<It> trim(Utilities::Range<It> str,
                          Enc encoding,
                          UnaryPred trimChar)
{
    return trimEnd(trimStart(str, encoding, trimChar), encoding, trimChar);
}

template <typename It, typename Enc, typename UnaryPred>
Utilities::Range<It> trimEnd(Utilities::Range<It> str,
                             Enc encoding,
                             UnaryPred trimChar)
{
    auto dec = Encoded::makeReverseDecoder(str, encoding);
    advanceWhile(dec, trimChar);
    return dec.getRange();
}

template <typename It, typename Enc, typename UnaryPred>
Utilities::Range<It> trimStart(Utilities::Range<It> str,
                               Enc encoding,
                               UnaryPred trimChar)
{
    auto dec = Encoded::makeForwardDecoder(str, encoding);
    advanceWhile(dec, trimChar);
    return dec.getRange();
}

template <typename Str, typename It, typename Enc>
Str upper(Utilities::Range<It> src, Enc encoding)
{
    auto str = Str();
    auto ref = makeStringReference(str);
    appendUpper(ref, src, encoding);
    return str;
}

}}
