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

namespace Ystring { namespace Generic {

namespace Details
{
    template <typename It1, typename It2, typename Enc>
    bool endsWithImpl(Utilities::Range<It1> str,
                      Utilities::Range<It2> cmp,
                      Enc /*encoding*/,
                      FindFlags_t /*flags*/,
                      std::true_type);

    template <typename It1, typename It2, typename Enc>
    bool endsWithImpl(Utilities::Range<It1> str,
                      Utilities::Range<It2> cmp,
                      Enc encoding,
                      FindFlags_t flags,
                      std::false_type);

    template <typename It1, typename It2, typename Enc>
    Utilities::Range<It1> findImpl(Utilities::Range<It1> str,
                                   Utilities::Range<It2> cmp,
                                   Enc /*encoding*/,
                                   FindFlags_t /*flags*/,
                                   std::true_type);

    template <typename It1, typename It2, typename Enc>
    Utilities::Range<It1> findImpl(Utilities::Range<It1> str,
                                   Utilities::Range<It2> cmp,
                                   Enc encoding,
                                   FindFlags_t flags,
                                   std::false_type);

    template <typename Str, typename Decoder, typename NextTokenFunc>
    std::vector<Str> splitImpl(
            Decoder str,
            NextTokenFunc nextTokenFunc,
            size_t maxParts,
            SplitFlags_t flags);

    template <typename Str, typename It1, typename It2, typename Enc>
    std::vector<Str> splitImpl(
            Utilities::Range<It1> str,
            Utilities::Range<It2> cmp,
            Enc encoding,
            int maxParts,
            SplitFlags_t flags,
            std::true_type);

    template <typename Str, typename It1, typename It2, typename Enc>
    std::vector<Str> splitImpl(
            Utilities::Range<It1> str,
            Utilities::Range<It2> cmp,
            Enc encoding,
            int maxParts,
            SplitFlags_t flags,
            std::false_type);

    template <typename It1, typename It2, typename Enc>
    bool startsWithImpl(Utilities::Range<It1> str,
                        Utilities::Range<It2> cmp,
                        Enc /*encoding*/,
                        FindFlags_t /*flags*/,
                        std::true_type);

    template <typename It1, typename It2, typename Enc>
    bool startsWithImpl(Utilities::Range<It1> str,
                        Utilities::Range<It2> cmp,
                        Enc encoding,
                        FindFlags_t flags,
                        std::false_type);
}

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

template <typename It, typename Enc>
size_t countCharacters(Utilities::Range<It> str, Enc encoding)
{
    auto dec = Encoded::makeForwardDecoder(str, encoding);
    return advanceCharacters(dec, SIZE_MAX);
}

template <typename It, typename Enc>
size_t countCodePoints(Utilities::Range<It> str, Enc encoding)
{
    auto dec = Encoded::makeForwardDecoder(str, encoding);
    size_t n = 0;
    uint32_t ch;
    while (dec.next(ch))
        ++n;
    return n;
}

//template <typename Str, typename It2, typename Enc>
//void replace(EncodedString<Str, Enc> dst,
//             EncodedRange<It2, Enc> cmp,)
//{
//    Encoded::appendLower(dst.getEncoder(), src.getForwardDecoder());
//}

template <typename It1, typename It2, typename Enc>
bool endsWith(Utilities::Range<It1> str,
              Utilities::Range<It2> cmp,
              Enc encoding,
              FindFlags_t flags)
{
    if (flags == FindFlags::CASE_INSENSITIVE)
        return Details::endsWithImpl(str, cmp, encoding, flags,
                                     std::false_type());
    else
        return Details::endsWithImpl(
                str, cmp, encoding, flags,
                typename SameIteratorValueType<It1, It2>::type());
}

template <typename It1, typename It2, typename Enc>
Utilities::Range<It1> findNext(Utilities::Range<It1> str,
                               Utilities::Range<It2> cmp,
                               Enc encoding,
                               FindFlags_t flags)
{
    if (flags == FindFlags::CASE_INSENSITIVE)
        return Details::findImpl(str, cmp, encoding, flags,
                                 std::false_type());
    else
        return Details::findImpl(
                str, cmp, encoding, flags,
                typename CanCompareRawValues<It1, Enc, It2, Enc>::type());
}

template <typename It, typename Enc>
Utilities::Range<It> findNextNewline(Utilities::Range<It> str,
                                      Enc encoding)
{
    auto dec = Encoded::makeForwardDecoder(str, encoding);
    return Encoded::nextNewline(dec).getRange();
}

template <typename Str, typename It1, typename It2, typename Enc>
Str insert(Utilities::Range<It1> str, int pos, Utilities::Range<It2> sub,
           Enc encoding)
{
    Utilities::Range<It1> range1 = str;
    Utilities::Range<It1> range2 = str;
    It1 insertPos;
    if (pos >= 0)
    {
        auto dec = Encoded::makeForwardDecoder(str, encoding);
        advanceCharacters(dec, (size_t)pos);
        range1.end() = range2.begin() = dec.begin();
    }
    else
    {
        auto dec = Encoded::makeReverseDecoder(str, encoding);
        advanceCharacters(dec, (size_t)-pos);
        range1.end() = range2.begin() = dec.end();
    }
    auto result = Str();
    auto ref = makeStringReference(result);
    auto appender = ref.getAppender();
    appender.append(range1);
    appender.append(sub);
    appender.append(range2);
    return result;
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
        int maxParts,
        SplitFlags_t flags)
{
    return splitIf<Str>(str, encoding, Unicode::isWhitespace,
                        maxParts, flags);
}

template <typename Str, typename It1, typename It2, typename Enc>
std::vector<Str> split(
        Utilities::Range<It1> str,
        Utilities::Range<It2> cmp,
        Enc encoding,
        int maxParts,
        SplitFlags_t flags)
{
    if (SplitFlags::isCaseInsensitive(flags) || maxParts < 0)
        return Details::splitImpl<Str>(str, cmp, encoding, maxParts, flags,
                                       std::false_type());
    else
        return Details::splitImpl<Str>(
                str, cmp, encoding, maxParts, flags,
                typename SameIteratorValueType<It1, It2>::type());
}

template <typename Str, typename It, typename Enc, typename Predicate>
std::vector<Str> splitIf(
        Utilities::Range<It> str,
        Enc encoding,
        Predicate predicate,
        int maxParts,
        SplitFlags_t flags)
{
    if (maxParts >= 0)
        return Details::splitImpl<Str>(
                Encoded::makeForwardDecoder(str, encoding),
                [&](Encoded::ForwardDecoder<It, Enc>& d)
                   {return nextToken(d, predicate);},
                maxParts, flags);
    else
        return Details::splitImpl<Str>(
                Encoded::makeReverseDecoder(str, encoding),
                [&](Encoded::ReverseDecoder<It, Enc>& d)
                   {return nextToken(d, predicate);},
                -maxParts, flags);
}

template <typename Str, typename It, typename Enc>
std::vector<Str> splitLines(
        Utilities::Range<It> str,
        Enc encoding,
        int maxParts,
        SplitFlags_t flags)
{
    if (maxParts >= 0)
        return Details::splitImpl<Str>(
                Encoded::makeForwardDecoder(str, encoding),
                [&](Encoded::ForwardDecoder<It, Enc>& d)
                   {return nextLine(d);},
                maxParts, flags);
    else
        return Details::splitImpl<Str>(
                Encoded::makeReverseDecoder(str, encoding),
                [&](Encoded::ReverseDecoder<It, Enc>& d)
                   {return nextLine(d);},
                -maxParts, flags);
}

template <typename It1, typename It2, typename Enc>
bool startsWith(Utilities::Range<It1> str,
                Utilities::Range<It2> cmp,
                Enc encoding,
                FindFlags_t flags)
{
    if (flags == FindFlags::CASE_INSENSITIVE)
        return Details::startsWithImpl(str, cmp, encoding, flags,
                                       std::false_type());
    else
        return Details::startsWithImpl(
                str, cmp, encoding, flags,
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

namespace Details
{
    template <typename It1, typename It2, typename Enc>
    bool endsWithImpl(Utilities::Range<It1> str,
                      Utilities::Range<It2> cmp,
                      Enc /*encoding*/,
                      FindFlags_t /*flags*/,
                      std::true_type)
    {
        auto strRange = makeReverseRange(str);
        auto cmpRange = makeReverseRange(cmp);
        return mismatch(strRange, cmpRange).second == cmpRange.end();
    }

    template <typename It1, typename It2, typename Enc>
    bool endsWithImpl(Utilities::Range<It1> str,
                      Utilities::Range<It2> cmp,
                      Enc encoding,
                      FindFlags_t flags,
                      std::false_type)
    {
        return Encoded::startsWith(Encoded::makeReverseDecoder(str, encoding),
                                   Encoded::makeReverseDecoder(cmp, encoding),
                                   flags);
    }

    template <typename It1, typename It2, typename Enc>
    Utilities::Range<It1> findImpl(Utilities::Range<It1> str,
                                   Utilities::Range<It2> cmp,
                                   Enc /*encoding*/,
                                   FindFlags_t /*flags*/,
                                   std::true_type)
    {
        return search(str, cmp);
    }

    template <typename It1, typename It2, typename Enc>
    Utilities::Range<It1> findImpl(Utilities::Range<It1> str,
                                   Utilities::Range<It2> cmp,
                                   Enc encoding,
                                   FindFlags_t flags,
                                   std::false_type)
    {
        auto strDec = Encoded::makeForwardDecoder(str, encoding);
        return Encoded::find(strDec,
                             Encoded::makeForwardDecoder(cmp, encoding),
                             flags).getRange();
    }

    template <typename Str, typename Decoder, typename NextTokenFunc>
    std::vector<Str> splitImpl(
            Decoder str,
            NextTokenFunc nextTokenFunc,
            size_t maxParts,
            SplitFlags_t flags)
    {
        std::vector<Str> result;
        while (maxParts != 1 && str.begin() != str.end())
        {
            auto token = nextTokenFunc(str);
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

    template <typename Str, typename It1, typename It2, typename Enc>
    std::vector<Str> splitImpl(
            Utilities::Range<It1> str,
            Utilities::Range<It2> cmp,
            Enc encoding,
            int maxParts,
            SplitFlags_t flags,
            std::true_type)
    {
        std::vector<Str> result;
        while (maxParts != 1 && str.begin() != str.end())
        {
            auto token = search(str, cmp);
            if (!SplitFlags::ignoreEmpty(flags) || str.begin() != token.begin())
            {
                result.emplace_back(str.begin(), token.begin());
                --maxParts;
            }
            str.begin() = token.end();
        }
        if ((!SplitFlags::ignoreRemainder(flags)) &&
            (!SplitFlags::ignoreEmpty(flags) || str.begin() != str.end()))
        {
            result.emplace_back(str.begin(), str.end());
        }
        return result;
    }

    template <typename Str, typename It1, typename It2, typename Enc>
    std::vector<Str> splitImpl(
            Utilities::Range<It1> str,
            Utilities::Range<It2> cmp,
            Enc encoding,
            int maxParts,
            SplitFlags_t flags,
            std::false_type)
    {
        auto findFlags = SplitFlags::toFindFlags(flags);
        if (maxParts >= 0)
        {
            auto cmpDec = Encoded::makeForwardDecoder(cmp, encoding);
            return splitImpl<Str>(
                    Encoded::makeForwardDecoder(str, encoding),
                    [=](Encoded::ForwardDecoder<It1, Enc>& d)
                       {return nextToken(d, cmpDec, findFlags);},
                    maxParts, flags);
        }
        else
        {
            auto cmpDec = Encoded::makeReverseDecoder(cmp, encoding);
            return splitImpl<Str>(
                    Encoded::makeReverseDecoder(str, encoding),
                    [=](Encoded::ReverseDecoder<It1, Enc>& d)
                       {return nextToken(d, cmpDec, findFlags);},
                    -maxParts, flags);
        }
    }

    template <typename It1, typename It2, typename Enc>
    bool startsWithImpl(Utilities::Range<It1> str,
                        Utilities::Range<It2> cmp,
                        Enc /*encoding*/,
                        FindFlags_t /*flags*/,
                        std::true_type)
    {
        return mismatch(str, cmp).second == cmp.end();
    }

    template <typename It1, typename It2, typename Enc>
    bool startsWithImpl(Utilities::Range<It1> str,
                        Utilities::Range<It2> cmp,
                        Enc encoding,
                        FindFlags_t flags,
                        std::false_type)
    {
        return Encoded::startsWith(Encoded::makeForwardDecoder(str, encoding),
                                   Encoded::makeForwardDecoder(cmp, encoding),
                                   flags);
    }
}

}}
