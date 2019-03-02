//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-06-02.
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#pragma once

#include "DecoderStringFunctions.hpp"
#include "Encoder.hpp"
#include "ForwardDecoder.hpp"
#include "ReverseDecoder.hpp"
#include "../Utilities/CountingOutputIterator.hpp"
#include "GenericConvert.hpp"
#include "GenericEscape.hpp"
#include "GenericJoin.hpp"
#include "GenericSplit.hpp"
#include "StringTypeTraits.hpp"

namespace Ystring { namespace Generic
{
    namespace Detail
    {
        template <typename It1, typename It2, typename Enc>
        bool endsWithImpl(Range<It1> str,
                          Range<It2> cmp,
                          Enc /*encoding*/,
                          FindFlags_t /*flags*/,
                          std::true_type);

        template <typename It1, typename It2, typename Enc>
        bool endsWithImpl(Range<It1> str,
                          Range<It2> cmp,
                          Enc encoding,
                          FindFlags_t flags,
                          std::false_type);

        template <typename It1, typename It2, typename Enc>
        Range<It1> findFirstImpl(Range<It1> str,
                                 Range<It2> cmp,
                                 Enc /*encoding*/,
                                 FindFlags_t /*flags*/,
                                 std::true_type);

        template <typename It1, typename It2, typename Enc>
        Range<It1> findFirstImpl(Range<It1> str,
                                 Range<It2> cmp,
                                 Enc encoding,
                                 FindFlags_t flags,
                                 std::false_type);

        template <typename It1, typename It2, typename Enc>
        Range<It1> findLastImpl(Range<It1> str,
                                Range<It2> cmp,
                                Enc /*encoding*/,
                                FindFlags_t /*flags*/,
                                std::true_type);

        template <typename It1, typename It2, typename Enc>
        Range<It1> findLastImpl(Range<It1> str,
                                Range<It2> cmp,
                                Enc encoding,
                                FindFlags_t flags,
                                std::false_type);

        template <typename It1, typename It2, typename Enc>
        std::vector<Range<It1>> findPositionsFwd(
                Range<It1> str, Range<It2> cmp,
                Enc encoding, size_t maxCount, FindFlags_t flags);

        template <typename It1, typename It2, typename Enc>
        std::vector<Range<It1>> findPositionsRev(
                Range<It1> str, Range<It2> cmp,
                Enc encoding, size_t maxCount, FindFlags_t flags);

        template <typename Str, typename It1, typename It2, typename Enc>
        Str replaceFwd(Range<It1> str, Range<It2> cmp, Range<It2> rep,
                       Enc encoding,
                       size_t maxReplacements,
                       FindFlags_t flags);

        template <typename Str, typename It1, typename It2, typename Enc>
        Str replaceRev(Range<It1> str, Range<It2> cmp, Range<It2> rep,
                       Enc encoding,
                       size_t maxReplacements,
                       FindFlags_t flags);

        template <typename It1, typename It2, typename Enc>
        bool startsWithImpl(Range<It1> str,
                            Range<It2> cmp,
                            Enc /*encoding*/,
                            FindFlags_t /*flags*/,
                            std::true_type);

        template <typename It1, typename It2, typename Enc>
        bool startsWithImpl(Range<It1> str,
                            Range<It2> cmp,
                            Enc encoding,
                            FindFlags_t flags,
                            std::false_type);
    }

    template <typename Str, typename Enc>
    void append(StringReference<Str>& dst, char32_t chr, Enc encoding)
    {
        auto encoder = dst.getEncoder(encoding);
        encoder.encode(chr);
    }

    template <typename Str, typename Enc>
    void append(StringReference<Str>&& dst, char32_t chr, Enc encoding)
    {
        append(dst, chr, encoding);
    }

    template <typename Str, typename It, typename Enc>
    void appendLower(StringReference<Str>& dst,
                     Range<It> src,
                     Enc encoding)
    {
        EncodedString::appendLower(
                dst.getEncoder(encoding),
                EncodedString::makeForwardDecoder(src, encoding));
        dst.terminate();
    }

    template <typename Str, typename It, typename Enc>
    void appendTitle(StringReference<Str>& dst,
                     Range<It> src,
                     Enc encoding)
    {
        EncodedString::appendTitle(
                dst.getEncoder(encoding),
                EncodedString::makeForwardDecoder(src, encoding));
        dst.terminate();
    }

    template <typename Str, typename It, typename Enc>
    void appendUpper(StringReference<Str>& dst,
                     Range<It> src,
                     Enc encoding)
    {
        EncodedString::appendUpper(
                dst.getEncoder(encoding),
                EncodedString::makeForwardDecoder(src, encoding));
        dst.terminate();
    }

    template <typename It1, typename It2, typename Enc>
    int32_t caseInsensitiveCompare(Range<It1> str,
                                   Range<It2> cmp,
                                   Enc encoding)
    {
        return caseInsensitiveCompare(
                EncodedString::makeForwardDecoder(str, encoding),
                EncodedString::makeForwardDecoder(cmp, encoding));
    }

    template <typename It1, typename It2, typename Enc>
    bool caseInsensitiveEqual(Range<It1> str,
                              Range<It2> cmp,
                              Enc encoding)
    {
        return caseInsensitiveEqual(
                EncodedString::makeForwardDecoder(str, encoding),
                EncodedString::makeForwardDecoder(cmp, encoding));
    }

    template <typename It1, typename It2, typename Enc>
    bool caseInsensitiveLess(Range<It1> str,
                             Range<It2> cmp,
                             Enc encoding)
    {
        return caseInsensitiveLess(
                EncodedString::makeForwardDecoder(str, encoding),
                EncodedString::makeForwardDecoder(cmp, encoding));
    }

    template <typename It, typename Enc>
    bool contains(Range<It> str, char32_t chr, Enc encoding)
    {
        auto dec = EncodedString::makeForwardDecoder(str, encoding);
        return EncodedString::advanceUntil(
                dec, [=](char32_t c){return c == chr;});
    }

    template <typename It, typename Enc>
    size_t countCharacters(Range<It> str, Enc encoding)
    {
        auto dec = EncodedString::makeForwardDecoder(str, encoding);
        return advanceCharacters(dec, SIZE_MAX);
    }

    template <typename It, typename Enc>
    size_t countCodePoints(Range<It> str, Enc encoding)
    {
        auto dec = EncodedString::makeForwardDecoder(str, encoding);
        size_t n = 0;
        char32_t ch;
        while (dec.next(ch))
            ++n;
        return n;
    }

    template <typename It1, typename It2, typename Enc>
    bool endsWith(Range<It1> str,
                  Range<It2> cmp,
                  Enc encoding,
                  FindFlags_t flags)
    {
        if (flags == FindFlags::CASE_INSENSITIVE)
            return Detail::endsWithImpl(str, cmp, encoding, flags,
                                        std::false_type());
        else
            return Detail::endsWithImpl(
                    str, cmp, encoding, flags,
                    SameIteratorValueType<It1, It2>());
    }

    template <typename It1, typename It2, typename Enc>
    Range<It1> findFirst(Range<It1> str,
                         Range<It2> cmp,
                         Enc encoding,
                         FindFlags_t flags)
    {
        if (flags == FindFlags::CASE_INSENSITIVE)
            return Detail::findFirstImpl(str, cmp, encoding, flags,
                                         std::false_type());
        else
            return Detail::findFirstImpl(
                    str, cmp, encoding, flags,
                    CanCompareRawValues<It1, Enc, It2, Enc>());
    }

    template <typename It, typename Enc>
    Range<It> findFirstNewline(Range<It> str, Enc encoding)
    {
        auto dec = EncodedString::makeForwardDecoder(str, encoding);
        return EncodedString::nextNewline(dec).getRange();
    }

    template <typename It1, typename It2, typename Enc>
    Range<It1> findLast(Range<It1> str,
                        Range<It2> cmp,
                        Enc encoding,
                        FindFlags_t flags)
    {
        if (flags == FindFlags::CASE_INSENSITIVE)
            return Detail::findLastImpl(str, cmp, encoding, flags,
                                        std::false_type());
        else
            return Detail::findLastImpl(
                    str, cmp, encoding, flags,
                    CanCompareRawValues<It1, Enc, It2, Enc>());
    }

    template <typename It, typename Enc>
    Range<It> findLastNewline(Range<It> str, Enc encoding)
    {
        auto dec = EncodedString::makeReverseDecoder(str, encoding);
        return EncodedString::nextNewline(dec).getRange();
    }

    template <typename It, typename Enc>
    std::pair<Range<It>, Range<It>> findInsertPosition(Range<It> str,
                                                       ptrdiff_t pos,
                                                       Enc encoding)
    {
        Range<It> range1 = str;
        Range<It> range2 = str;
        It insertPos;
        if (pos >= 0)
        {
            auto dec = EncodedString::makeForwardDecoder(str, encoding);
            advanceCharacters(dec, static_cast<size_t>(pos));
            range1.end() = range2.begin() = dec.begin();
        }
        else
        {
            auto dec = EncodedString::makeReverseDecoder(str, encoding);
            advanceCharacters(dec, static_cast<size_t>(-pos));
            range1.end() = range2.begin() = dec.end();
        }
        return std::make_pair(range1, range2);
    }

    template <typename It, typename Enc>
    char32_t getCodePoint(Range<It> str, ptrdiff_t pos, Enc encoding)
    {
        auto it = str.begin();
        if (pos > 0)
        {
            encoding.skipNext(it, str.end(), static_cast<size_t>(pos));
        }
        else if (pos < 0)
        {
            it = str.end();
            encoding.skipPrev(str.begin(), it, static_cast<size_t>(-pos));
        }
        char32_t chr;
        if (!encoding.next(chr, it, str.end()))
            YSTRING_THROW("No character at position " + std::to_string(pos));
        return chr;
    }

    template<typename It, typename Enc>
    Range<It> getValidSubstring(Range<It> str, Enc encoding)
    {
        auto it = str.begin();
        while (encoding.next(it, str.end()))
        {}
        return makeRange(it, str.end());
    }

    template <typename Str, typename It1, typename It2, typename Enc>
    Str insert(Range<It1> str, ptrdiff_t pos, Range<It2> sub, Enc encoding)
    {
        auto ranges = findInsertPosition(str, pos, encoding);
        auto result = Str();
        auto ref = makeStringReference(result);
        auto appender = ref.getAppender();
        appender.append(ranges.first);
        appender.append(sub);
        appender.append(ranges.second);
        return result;
    }

    template <typename Str, typename It, typename Enc>
    Str insert(Range<It> str, ptrdiff_t pos, char32_t chr, Enc encoding)
    {
        auto ranges = findInsertPosition(str, pos, encoding);
        auto result = Str();
        auto ref = makeStringReference(result);
        ref.getAppender().append(ranges.first);
        ref.getEncoder(encoding).encode(chr);
        ref.getAppender().append(ranges.second);
        return result;
    }

    template <typename It, typename Enc>
    bool isAlphaNumeric(Range<It> str, Enc encoding)
    {
        return isAlphaNumeric(EncodedString::makeForwardDecoder(str, encoding));
    }

    template <typename Str, typename It, typename Enc>
    Str lower(Range<It> src, Enc encoding)
    {
        auto str = Str();
        auto ref = makeStringReference(str);
        appendLower(ref, src, encoding);
        return str;
    }

    template <typename It, typename Enc>
    It nextCharacter(Range<It> str, size_t n, Enc encoding)
    {
        auto dec = EncodedString::makeForwardDecoder(str, encoding);
        if (advanceCharacters(dec, n) != n)
            YSTRING_THROW("can't advance beyond the end of the range");
        return dec.begin();
    }

    template <typename It, typename Enc>
    It nthCharacter(Range<It> str, ptrdiff_t n, Enc encoding)
    {
        if (n >= 0)
            return nextCharacter(str, static_cast<size_t>(n), encoding);
        else
            return prevCharacter(str, static_cast<size_t>(-n), encoding);
    }

    template <typename It, typename Enc>
    It prevCharacter(Range<It> str, size_t n, Enc encoding)
    {
        auto dec = EncodedString::makeReverseDecoder(str, encoding);
        if (advanceCharacters(dec, n) != n)
            YSTRING_THROW("can't advance beyond the start of the range");
        return dec.end();
    }

    template <typename It1, typename It2, typename Enc>
    std::vector<Range<It1>> findPositions(Range<It1> str, Range<It2> cmp,
                                          Enc encoding,
                                          ptrdiff_t maxCount,
                                          FindFlags_t flags)
    {
        if (maxCount >= 0)
        {
            return Detail::findPositionsFwd(str, cmp, encoding,
                                            static_cast<size_t>(maxCount), flags);
        }
        else
        {
            return Detail::findPositionsRev(str, cmp, encoding,
                                            static_cast<size_t>(-maxCount), flags);
        }
    }

    template <typename Str, typename It1, typename It2, typename Enc>
    Str replace(Range<It1> str, Range<It2> cmp, Range<It2> rep,
                Enc encoding,
                ptrdiff_t maxReplacements,
                FindFlags_t flags)
    {
        if (cmp.begin() == cmp.end())
            return Str(str.begin(), str.end());

        if (maxReplacements >= 0)
            return Detail::replaceFwd<Str>(str, cmp, rep, encoding,
                                           static_cast<size_t>(maxReplacements), flags);
        else
            return Detail::replaceRev<Str>(str, cmp, rep, encoding,
                                           static_cast<size_t>(-maxReplacements), flags);
    }

    template <typename Str, typename It1, typename It2, typename Enc>
    Str replace(Range<It1> str, ptrdiff_t start, ptrdiff_t end,
                Range<It2> rep, Enc encoding)
    {
        auto sub = subrange(str, start, end, encoding);
        auto result = Str();
        auto ref = makeStringReference(result);
        auto appender = ref.getAppender();
        appender.append(makeRange(str.begin(), sub.begin()));
        appender.append(rep);
        appender.append(makeRange(sub.end(), str.end()));
        return result;
    }

    template <typename Str, typename It, typename Enc>
    Str reverse(Range<It> src, Enc encoding)
    {
        Str result(getSize(src), 0);
        auto dst = begin(result);
        auto dec = EncodedString::makeReverseDecoder(src, encoding);
        while (advanceCharacter(dec))
        {
            src.begin() = dec.end();
            dst = copy(src, dst);
            src.end() = src.begin();
        }
        return result;
    }

    template <typename It1, typename It2>
    size_t sizeOfJoin(It1 first, It1 last, Range<It2> delimiter)
    {
        size_t n = 0, len = 0;
        for (; first != last; ++first)
        {
            len += getSize(makeRange(*first));
            ++n;
        }
        return len + (n - 1) * getSize(delimiter);
    }

    template <typename It>
    size_t sizeOfJoin(It first, It last)
    {
        size_t size = 0;
        for (; first != last; ++first)
            size += getSize(makeRange(first));
        return size;
    }

    template <typename It, typename Enc>
    size_t sizeOfLower(Range<It> src, Enc encoding)
    {
        size_t n = 0;
        Utilities::CountingOutputIterator<typename Enc::CanonicalType> it(&n);
        EncodedString::appendLower(
                EncodedString::makeEncoder(it, encoding),
                EncodedString::makeForwardDecoder(src, encoding));
        return n;
    }

    template <typename It, typename Enc>
    size_t sizeOfUpper(Range<It> src, Enc encoding)
    {
        size_t n = 0;
        Utilities::CountingOutputIterator<typename Enc::CanonicalType> it(&n);
        EncodedString::appendUpper(
                EncodedString::makeEncoder(it, encoding),
                EncodedString::makeForwardDecoder(src, encoding));
        return n;
    }

    template <typename It1, typename It2, typename Enc>
    bool startsWith(Range<It1> str,
                    Range<It2> cmp,
                    Enc encoding,
                    FindFlags_t flags)
    {
        if (flags == FindFlags::CASE_INSENSITIVE)
        {
            return Detail::startsWithImpl(str, cmp, encoding, flags,
                                          std::false_type());
        }
        else
        {
            return Detail::startsWithImpl(str, cmp, encoding, flags,
                                          SameIteratorValueType<It1, It2>());
        }
    }

    template <typename It, typename Enc>
    Range<It> subrange(Range<It> str, ptrdiff_t start, ptrdiff_t end,
                       Enc encoding)
    {
        if (end == PTRDIFF_MAX)
            return makeRange(nthCharacter(str, start, encoding), str.end());

        It first, last;
        auto sameSign = start >= 0 == end >= 0;
        if (sameSign)
        {
            if (start >= end)
            {
                first = nthCharacter(str, start, encoding);
                last = first;
            }
            else if (start >= 0)
            {
                first = nthCharacter(str, start, encoding);
                last = nthCharacter(makeRange(first, str.end()), end - start,
                                     encoding);
            }
            else
            {
                last = nthCharacter(str, end, encoding);
                first = nthCharacter(makeRange(str.begin(), last),
                                     start - end, encoding);
            }
        }
        else
        {
            first = nthCharacter(str, start, encoding);
            last = nthCharacter(str, end, encoding);
            using std::distance;
            if (distance(str.begin(), first) > distance(str.begin(), last))
            {
                last = first;
            }
        }

        return Range<It>(first, last);
    }

    template <typename Str, typename It, typename Enc>
    Str substring(Range<It> str, ptrdiff_t start, ptrdiff_t end, Enc encoding)
    {
        auto sub = subrange(str, start, end, encoding);
        return Str(sub.begin(), sub.end());
    }

    template <typename Str, typename It, typename Enc>
    Str title(Range<It> src, Enc encoding)
    {
        auto str = Str();
        auto ref = makeStringReference(str);
        appendTitle(ref, src, encoding);
        return str;
    }

    template <typename It, typename Enc, typename UnaryPred>
    Range<It> trim(Range<It> str,
                   Enc encoding,
                   UnaryPred trimChar)
    {
        return trimEnd(trimStart(str, encoding, trimChar),
                       encoding, trimChar);
    }

    template <typename It, typename Enc, typename UnaryPred>
    Range<It> trimEnd(Range<It> str,
                      Enc encoding,
                      UnaryPred trimChar)
    {
        auto dec = EncodedString::makeReverseDecoder(str, encoding);
        advanceWhile(dec, trimChar);
        return dec.getRange();
    }

    template <typename It, typename Enc, typename UnaryPred>
    Range<It> trimStart(Range<It> str,
                        Enc encoding,
                        UnaryPred trimChar)
    {
        auto dec = EncodedString::makeForwardDecoder(str, encoding);
        advanceWhile(dec, trimChar);
        return dec.getRange();
    }

    template <typename Str, typename It, typename Enc>
    Str upper(Range<It> src, Enc encoding)
    {
        auto str = Str();
        auto ref = makeStringReference(str);
        appendUpper(ref, src, encoding);
        return str;
    }

    namespace Detail
    {
        template <typename It1, typename It2, typename Enc>
        bool endsWithImpl(Range<It1> str,
                          Range<It2> cmp,
                          Enc /*encoding*/,
                          FindFlags_t /*flags*/,
                          std::true_type)
        {
            auto strRange = makeReverseRange(str);
            auto cmpRange = makeReverseRange(cmp);
            return mismatch(strRange, cmpRange).second == cmpRange.end();
        }

        template <typename It1, typename It2, typename Enc>
        bool endsWithImpl(Range<It1> str,
                          Range<It2> cmp,
                          Enc encoding,
                          FindFlags_t flags,
                          std::false_type)
        {
            return EncodedString::startsWith(
                    EncodedString::makeReverseDecoder(str, encoding),
                    EncodedString::makeReverseDecoder(cmp, encoding),
                    flags);
        }

        template <typename It1, typename It2, typename Enc>
        Range<It1> findFirstImpl(Range<It1> str,
                                 Range<It2> cmp,
                                 Enc /*encoding*/,
                                 FindFlags_t /*flags*/,
                                 std::true_type)
        {
            return search(str, cmp);
        }

        template <typename It1, typename It2, typename Enc>
        Range<It1> findFirstImpl(Range<It1> str,
                                 Range<It2> cmp,
                                 Enc encoding,
                                 FindFlags_t flags,
                                 std::false_type)
        {
            auto strDec = EncodedString::makeForwardDecoder(str, encoding);
            return EncodedString::find(strDec,
                                 EncodedString::makeForwardDecoder(cmp, encoding),
                                 flags).getRange();
        }

        template <typename It1, typename It2, typename Enc>
        Range<It1> findLastImpl(Range<It1> str,
                                Range<It2> cmp,
                                Enc /*encoding*/,
                                FindFlags_t /*flags*/,
                                std::true_type)
        {
            return searchLast(str, cmp);
        }

        template <typename It1, typename It2, typename Enc>
        Range<It1> findLastImpl(Range<It1> str,
                                Range<It2> cmp,
                                Enc encoding,
                                FindFlags_t flags,
                                std::false_type)
        {
            auto strDec = EncodedString::makeReverseDecoder(str, encoding);
            return EncodedString::find(
                    strDec,
                    EncodedString::makeReverseDecoder(cmp, encoding),
                    flags).getRange();
        }

        template <typename It1, typename It2, typename Enc>
        std::vector<Range<It1>> findPositionsFwd(
                Range<It1> str, Range<It2> cmp,
                Enc encoding, size_t maxCount, FindFlags_t flags)
        {
            std::vector<Range<It1>> result;
            auto nxt = findFirst(str, cmp, encoding, flags);
            while (nxt.begin() != nxt.end())
            {
                result.push_back(nxt);
                if (--maxCount == 0)
                    break;
                str.begin() = nxt.end();
                nxt = findFirst(str, cmp, encoding, flags);
            }
            return result;
        }

        template <typename It1, typename It2, typename Enc>
        std::vector<Range<It1>> findPositionsRev(
                Range<It1> str, Range<It2> cmp,
                Enc encoding, size_t maxCount, FindFlags_t flags)
        {
            std::vector<Range<It1>> result;
            auto prv = findLast(str, cmp, encoding, flags);
            while (prv.begin() != prv.end())
            {
                result.push_back(prv);
                if (--maxCount == 0)
                    break;
                str.end() = prv.begin();
                prv = findLast(str, cmp, encoding, flags);
            }
            return result;
        }

        template <typename Str, typename It1, typename It2, typename Enc>
        Str replaceFwd(Range<It1> str, Range<It2> cmp, Range<It2> rep,
                       Enc encoding,
                       size_t maxReplacements,
                       FindFlags_t flags)
        {
            auto result = Str();
            auto ref = makeStringReference(result);
            auto appender = ref.getAppender();
            auto sub = findFirst(str, cmp, encoding, flags);
            while (sub.begin() != sub.end())
            {
                appender.append(makeRange(str.begin(), sub.begin()));
                appender.append(rep);
                str.begin() = sub.end();
                if (--maxReplacements == 0)
                    break;
                sub = findFirst(str, cmp, encoding, flags);
            }
            appender.append(str);
            return result;
        }

        template <typename Str, typename It1, typename It2, typename Enc>
        Str replaceRev(Range<It1> str, Range<It2> cmp, Range<It2> rep,
                       Enc encoding,
                       size_t maxReplacements,
                       FindFlags_t flags)
        {
            auto positions = findPositionsRev(str, cmp, encoding,
                                              maxReplacements, flags);
            auto result = Str();
            auto ref = makeStringReference(result);
            auto appender = ref.getAppender();
            for (auto it = positions.rbegin(); it != positions.rend(); ++it)
            {
                appender.append(makeRange(str.begin(), it->begin()));
                appender.append(rep);
                str.begin() = it->end();
            }
            appender.append(str);
            return result;
        }

        template <typename It1, typename It2, typename Enc>
        bool startsWithImpl(Range<It1> str,
                            Range<It2> cmp,
                            Enc /*encoding*/,
                            FindFlags_t /*flags*/,
                            std::true_type)
        {
            return mismatch(str, cmp).second == cmp.end();
        }

        template <typename It1, typename It2, typename Enc>
        bool startsWithImpl(Range<It1> str,
                            Range<It2> cmp,
                            Enc encoding,
                            FindFlags_t flags,
                            std::false_type)
        {
            return EncodedString::startsWith(
                    EncodedString::makeForwardDecoder(str, encoding),
                    EncodedString::makeForwardDecoder(cmp, encoding),
                    flags);
        }
    }
}}
