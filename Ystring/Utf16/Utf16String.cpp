//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-07-29
//
// This file is distributed under the BSD License.
// License text is included with the source distribution.
//****************************************************************************
#include "Utf16String.hpp"

#include "../PrivatePlatformDetails.hpp"
#include "../Generic/GenericString.hpp"
#include "../CodePage/CodePageEncoding.hpp"
#include "../Utf8/Utf8Encoding.hpp"
#include "../Utf32/Utf32Encoding.hpp"
#include "Utf16Encoding.hpp"

namespace Ystring { namespace Utf16
{
    using Generic::makeStringReference;
    using Generic::makeRange;
    using Generic::fromRange;

    std::u16string& append(std::u16string& str, uint32_t chr)
    {
        append(makeStringReference(str), chr, Utf16Encoding());
        return str;
    }

    int32_t caseInsensitiveCompare(const std::u16string& str,
                                   const std::u16string& cmp)
    {
        return Generic::caseInsensitiveCompare(makeRange(str),
                                               makeRange(cmp),
                                               Utf16Encoding());
    }

    bool caseInsensitiveEqual(const std::u16string& str,
                              const std::u16string& cmp)
    {
        return Generic::caseInsensitiveEqual(makeRange(str),
                                             makeRange(cmp),
                                             Utf16Encoding());
    }

    bool caseInsensitiveLess(const std::u16string& str,
                             const std::u16string& cmp)
    {
        return Generic::caseInsensitiveLess(makeRange(str),
                                            makeRange(cmp),
                                            Utf16Encoding());
    }

    bool contains(const std::u16string& str, uint32_t chr)
    {
        return Generic::contains(makeRange(str), chr, Utf16Encoding());
    }

    size_t countCharacters(const std::u16string& str)
    {
        return Generic::countCharacters(makeRange(str), Utf16Encoding());
    }

    size_t countCharacters(std::string::const_iterator first,
                           std::string::const_iterator last)
    {
        return Generic::countCharacters(makeRange(first, last),
                                        Utf16Encoding());
    }

    size_t countCodePoints(const std::u16string& str)
    {
        return Generic::countCodePoints(makeRange(str), Utf16Encoding());
    }

    bool endsWith(const std::u16string& str,
                  const std::u16string& cmp,
                  FindFlags_t flags)
    {
        return Generic::endsWith(
                makeRange(str),
                makeRange(cmp),
                Utf16Encoding(),
                flags);
    }

    std::u16string escape(const std::u16string& str, EscapeType_t mode)
    {
        return Generic::escape<std::u16string>(makeRange(str), mode,
                                               Utf16Encoding());
    }

    StringIteratorPair findFirst(
            std::u16string& str,
            const std::u16string& cmp,
            FindFlags_t flags)
    {
        return Generic::findFirst(makeRange(str), makeRange(cmp),
                                  Utf16Encoding(), flags);
    }

    StringConstIteratorPair findFirst(
            const std::u16string& str,
            const std::u16string& cmp,
            FindFlags_t flags)
    {
        return Generic::findFirst(makeRange(str), makeRange(cmp),
                                  Utf16Encoding(), flags);
    }

    StringIteratorPair findFirst(
            std::u16string::iterator first,
            std::u16string::iterator last,
            const std::u16string& cmp,
            FindFlags_t flags)
    {
        return Generic::findFirst(makeRange(first, last), makeRange(cmp),
                                  Utf16Encoding(), flags);
    }

    StringConstIteratorPair findFirst(
            std::u16string::const_iterator first,
            std::u16string::const_iterator last,
            const std::u16string& cmp,
            FindFlags_t flags)
    {
        return Generic::findFirst(makeRange(first, last), makeRange(cmp),
                                  Utf16Encoding(), flags);
    }

    StringIteratorPair findFirstNewline(std::u16string& str)
    {
        return Generic::findFirstNewline(makeRange(str), Utf16Encoding());
    }

    StringConstIteratorPair findFirstNewline(const std::u16string& str)
    {
        return Generic::findFirstNewline(makeRange(str), Utf16Encoding());
    }

    StringIteratorPair findFirstNewline(
            std::u16string::iterator first,
            std::u16string::iterator last)
    {
        return Generic::findFirstNewline(makeRange(first, last),
                                         Utf16Encoding());
    }

    StringConstIteratorPair findFirstNewline(
            std::u16string::const_iterator first,
            std::u16string::const_iterator last)
    {
        return Generic::findFirstNewline(makeRange(first, last),
                                         Utf16Encoding());
    }

    StringIteratorPair findLast(
            std::u16string& str,
            const std::u16string& cmp,
            FindFlags_t flags)
    {
        return Generic::findLast(makeRange(str), makeRange(cmp),
                                 Utf16Encoding(), flags);
    }

    StringConstIteratorPair findLast(
            const std::u16string& str,
            const std::u16string& cmp,
            FindFlags_t flags)
    {
        return Generic::findLast(makeRange(str), makeRange(cmp),
                                 Utf16Encoding(), flags);
    }

    StringIteratorPair findLast(
            std::u16string::iterator first,
            std::u16string::iterator last,
            const std::u16string& cmp,
            FindFlags_t flags)
    {
        return Generic::findLast(makeRange(first, last), makeRange(cmp),
                                 Utf16Encoding(), flags);
    }

    StringConstIteratorPair findLast(
            std::u16string::const_iterator first,
            std::u16string::const_iterator last,
            const std::u16string& cmp,
            FindFlags_t flags)
    {
        return Generic::findLast(makeRange(first, last), makeRange(cmp),
                                 Utf16Encoding(), flags);
    }

    StringIteratorPair findLastNewline(std::u16string& str)
    {
        return Generic::findLastNewline(makeRange(str), Utf16Encoding());
    }

    StringConstIteratorPair findLastNewline(const std::u16string& str)
    {
        return Generic::findLastNewline(makeRange(str), Utf16Encoding());
    }

    StringIteratorPair findLastNewline(
            std::u16string::iterator first,
            std::u16string::iterator last)
    {
        return Generic::findLastNewline(makeRange(first, last),
                                        Utf16Encoding());
    }

    StringConstIteratorPair findLastNewline(
            std::u16string::const_iterator first,
            std::u16string::const_iterator last)
    {
        return Generic::findLastNewline(makeRange(first, last),
                                        Utf16Encoding());
    }

    uint32_t getCodePoint(const std::u16string& str, ptrdiff_t n)
    {
        return Generic::getCodePoint(makeRange(str), n, Utf16Encoding());
    }

    std::u16string insert(const std::u16string& str, ptrdiff_t pos,
                       const std::u16string& sub)
    {
        return Generic::insert<std::u16string>(makeRange(str), pos,
                                               makeRange(sub),
                                               Utf16Encoding());
    }

    std::u16string insert(const std::u16string& str,
                          ptrdiff_t pos,
                          uint32_t chr)
    {
        return Generic::insert<std::u16string>(makeRange(str), pos, chr,
                                               Utf16Encoding());
    }

    bool isAlphaNumeric(const std::u16string& str)
    {
        return isAlphaNumeric(makeRange(str), Utf16Encoding());
    }

    bool isAlphaNumeric(std::u16string::iterator first,
                        std::u16string::iterator last)
    {
        return isAlphaNumeric(makeRange(first, last), Utf16Encoding());
    }

    bool isAlphaNumeric(std::u16string::const_iterator first,
                        std::u16string::const_iterator last)
    {
        return isAlphaNumeric(makeRange(first, last), Utf16Encoding());
    }

    //bool isValidUtf16(const std::u16string& str)
    //{
    //    return isValidUtf16(begin(str), end(str));
    //}

    std::u16string join(const std::vector<std::u16string>& strings,
                        const std::u16string& delimiter)
    {
        return join(strings.data(), strings.size(), delimiter);
    }

    std::u16string join(const std::u16string* strings,
                        size_t count,
                        const std::u16string& delimiter)
    {
        return delimiter.empty() ?
               Generic::join<std::u16string>(strings, strings + count) :
               Generic::join<std::u16string>(strings, strings + count,
                                             makeRange(delimiter));
    }

    std::u16string lower(const std::u16string& str)
    {
        return Generic::lower<std::u16string>(makeRange(str),
                                              Utf16Encoding());
    }

    std::u16string::iterator nextCharacter(std::u16string::iterator& first,
                                           std::u16string::iterator& last,
                                           size_t n)
    {
        return Generic::nextCharacter(makeRange(first, last), n,
                                      Utf16Encoding());
    }

    std::u16string::const_iterator nextCharacter(
            std::u16string::const_iterator& first,
            std::u16string::const_iterator& last,
            size_t n)
    {
        return Generic::nextCharacter(makeRange(first, last), n,
                                      Utf16Encoding());
    }

    std::u16string::iterator nthCharacter(std::u16string& str, ptrdiff_t n)
    {
        return Generic::nthCharacter(makeRange(str), n, Utf16Encoding());
    }

    std::u16string::const_iterator nthCharacter(const std::u16string& str,
                                                ptrdiff_t n)
    {
        return Generic::nthCharacter(makeRange(str), n, Utf16Encoding());
    }

    std::u16string::iterator prevCharacter(std::u16string::iterator& first,
                                           std::u16string::iterator& last,
                                           size_t n)
    {
        return Generic::prevCharacter(makeRange(first, last), n ,
                                      Utf16Encoding());
    }

    std::u16string::const_iterator prevCharacter(
            std::u16string::const_iterator& first,
            std::u16string::const_iterator& last,
            size_t n)
    {
        return Generic::prevCharacter(makeRange(first, last), n,
                                      Utf16Encoding());
    }

    std::u16string replace(const std::u16string& str,
                           const std::u16string& cmp,
                           const std::u16string& repl,
                           ptrdiff_t maxReplacements,
                           FindFlags_t flags)
    {
        return Generic::replace<std::u16string>(
                makeRange(str), makeRange(cmp),
                makeRange(repl), Utf16Encoding(),
                maxReplacements, flags);
    }

    std::u16string replace(const std::u16string& str,
                           ptrdiff_t start,
                           ptrdiff_t end,
                           const std::u16string& repl)
    {
        return Generic::replace<std::u16string>(
                makeRange(str), start, end,
                makeRange(repl), Utf16Encoding());
    }

    std::u16string replaceCodePoint(const std::u16string& s,
                                    uint32_t from,
                                    uint32_t to,
                                    ptrdiff_t maxReplacements)
    {
        uint16_t fBuf[2];
        auto fIt = fBuf;
        auto fromSize = encodeUtf16(fIt, std::end(fBuf), from);
        uint16_t tBuf[2];
        auto tIt = tBuf;
        auto toSize = encodeUtf16(tIt, std::end(tBuf), to);
        return Generic::replace<std::u16string>(
                makeRange(s),
                makeRange(fBuf, fBuf + fromSize),
                makeRange(tBuf, tBuf + toSize),
                Utf16Encoding(),
                maxReplacements, FindFlags::DEFAULTS);
    }

    std::u16string replaceInvalidUtf16(const std::u16string& str,
                                       uint32_t chr)
    {
        std::u16string result;
        result.reserve(str.size());
        auto first = str.begin();
        auto it = str.begin();
        while (it != str.end())
        {
            uint32_t cp;
            if (nextUtf16CodePoint<false>(cp, it, str.end()) !=
                    DecoderResult::OK)
            {
                result.append(first, it);
                first = ++it;
                append(result, chr);
            }
        }
        result.append(first, str.end());
        return result;
    }

    std::u16string& replaceInvalidUtf16InPlace(std::u16string& str,
                                               uint16_t chr)
    {
        assert(chr > 0);
        auto it = str.begin();
        while (it != str.end())
        {
            uint32_t cp;
            if (nextUtf16CodePoint<false>(cp, it, str.end()) !=
                    DecoderResult::OK)
            {
                *it++ = chr;
            }
        }
        return str;
    }

    std::u16string reverse(const std::u16string& str)
    {
        return Generic::reverse<std::u16string>(makeRange(str),
                                                Utf16Encoding());
    }

    std::vector<std::u16string> split(
            const std::u16string& str,
            ptrdiff_t maxSplits,
            SplitFlags_t flags)
    {
        return Generic::split<std::u16string>(
                makeRange(str), Utf16Encoding(),
                maxSplits, flags);
    }

    std::vector<std::u16string> split(
            const std::u16string& str,
            const std::u16string& sep,
            ptrdiff_t maxSplits,
            SplitFlags_t flags)
    {
      return Generic::split<std::u16string>(
              makeRange(str), makeRange(sep), Utf16Encoding(),
              maxSplits, flags);
    }

    std::vector<std::u16string> splitIf(
            const std::u16string& str,
            std::function<bool(uint32_t)> predicate,
            ptrdiff_t maxSplits,
            SplitFlags_t flags)
    {
        return Generic::splitIf<std::u16string>(
                makeRange(str), Utf16Encoding(),
                predicate, maxSplits, flags);
    }

    std::vector<std::u16string> splitLines(
            const std::u16string& str,
            ptrdiff_t maxSplits,
            SplitFlags_t flags)
    {
        return Generic::splitLines<std::u16string>(makeRange(str),
                                                   Utf16Encoding(),
                                                   maxSplits, flags);
    }

    bool startsWith(
            const std::u16string& str,
            const std::u16string& cmp,
            FindFlags_t flags)
    {
        return Generic::startsWith(makeRange(str), makeRange(cmp),
                                   Utf16Encoding(), flags);
    }

    std::u16string substring(
            const std::u16string& str,
            ptrdiff_t start,
            ptrdiff_t end)
    {
        return Generic::substring<std::u16string>(makeRange(str), start, end,
                                                  Utf16Encoding());
    }

    std::u16string title(const std::u16string& str)
    {
        return Generic::title<std::u16string>(makeRange(str),
                                              Utf16Encoding());
    }

    std::u16string toUtf16(uint32_t chr)
    {
        std::u16string s;
        append(s, chr);
        return s;
    }

    std::u16string toUtf16(const std::string& str, Encoding_t encoding)
    {
        return toUtf16(str.data(), str.size(), encoding);
    }

    std::u16string toUtf16(const std::wstring& str, Encoding_t encoding)
    {
        return toUtf16(str.data(), str.size(), encoding);
    }

    std::u16string toUtf16(const char* str, size_t length,
                           Encoding_t encoding)
    {
        switch (encoding)
        {
        case Encoding::UTF_8:
            return Generic::convert<std::u16string>(
                    makeRange(str, str + length),
                    Utf8::Utf8Encoding(),
                    Utf16Encoding());
        case Encoding::CP_437:
            return Generic::convert<std::u16string>(
                    makeRange(str, str + length),
                    CodePage::Cp437Encoding(),
                    Utf16Encoding());
        case Encoding::LATIN_1:
            return Generic::convert<std::u16string>(
                    makeRange(str, str + length),
                    CodePage::Latin1Encoding(),
                    Utf16Encoding());
        case Encoding::WINDOWS_1252:
            return Generic::convert<std::u16string>(
                    makeRange(str, str + length),
                    CodePage::Windows1252Encoding(),
                    Utf16Encoding());
        case Encoding::UTF_16_BE:
            return Generic::convert<std::u16string>(
                    makeRange(str, str + length),
                    Utf16::Utf16BEEncoding(),
                    Utf16Encoding());
        case Encoding::UTF_16_LE:
            return Generic::convert<std::u16string>(
                    makeRange(str, str + length),
                    Utf16::Utf16LEEncoding(),
                    Utf16Encoding());
        case Encoding::UTF_32_BE:
            return Generic::convert<std::u16string>(
                    makeRange(str, str + length),
                    Utf32::Utf32BEEncoding(),
                    Utf16Encoding());
        case Encoding::UTF_32_LE:
            return Generic::convert<std::u16string>(
                    makeRange(str, str + length),
                    Utf32::Utf32LEEncoding(),
                    Utf16Encoding());
        default:
            YSTRING_THROW("toUtf16: unsupported encoding " +
                                   std::to_string(int64_t(encoding)));
        }
    }

    std::u16string toUtf16(const uint16_t* str, size_t length,
                           Encoding_t encoding)
    {
        switch (encoding)
        {
        case Encoding::UTF_16_BE:
            return Generic::convert<std::u16string>(
                    makeRange(str, str + length),
                    Utf16::Utf16BEEncoding(),
                    Utf16Encoding());
        case Encoding::UTF_16_LE:
            return Generic::convert<std::u16string>(
                    makeRange(str, str + length),
                    Utf16::Utf16LEEncoding(),
                    Utf16Encoding());
        default:
            YSTRING_THROW("toUtf16: unsupported encoding " +
                                   std::to_string(int64_t(encoding)));
        }
    }

    std::u16string toUtf16(const uint32_t* str, size_t length,
                           Encoding_t encoding)
    {
        switch (encoding)
        {
        case Encoding::UTF_16_BE:
            return Generic::convert<std::u16string>(
                    makeRange(str, str + length),
                    Utf16::Utf16BEEncoding(),
                    Utf16Encoding());
        case Encoding::UTF_16_LE:
            return Generic::convert<std::u16string>(
                    makeRange(str, str + length),
                    Utf16::Utf16LEEncoding(),
                    Utf16Encoding());
        case Encoding::UTF_32_BE:
            return Generic::convert<std::u16string>(
                    makeRange(str, str + length),
                    Utf32::Utf32BEEncoding(),
                    Utf16Encoding());
        case Encoding::UTF_32_LE:
            return Generic::convert<std::u16string>(
                    makeRange(str, str + length),
                    Utf32::Utf32LEEncoding(),
                    Utf16Encoding());
        default:
            YSTRING_THROW("toUtf16: unsupported encoding " +
                                   std::to_string(int64_t(encoding)));
        }
    }

    std::u16string toUtf16(const std::u16string& str, Encoding_t encoding)
    {
        return toUtf16(str.data(), str.size(), encoding);
    }

    std::u16string toUtf16(const std::u32string& str, Encoding_t encoding)
    {
        return toUtf16(str.data(), str.size(), encoding);
    }

    std::u16string toUtf16(const wchar_t* str, size_t length,
                           Encoding_t encoding)
    {
        return toUtf16(internal_char_type_cast(str), length, encoding);
    }

    std::u16string toUtf16(const char16_t* str, size_t length,
                           Encoding_t encoding)
    {
        return toUtf16(internal_char_type_cast(str), length, encoding);
    }

    std::u16string toUtf16(const char32_t* str, size_t length,
                           Encoding_t encoding)
    {
        return toUtf16(internal_char_type_cast(str), length, encoding);
    }

    std::u16string trim(const std::u16string& str)
    {
        return fromRange<std::u16string>(Generic::trim(
                makeRange(str),
                Utf16Encoding(),
                Unicode::isWhitespace));
    }

    std::u16string trim(const std::u16string& str,
                     std::function<bool(uint32_t)> predicate)
    {
        return fromRange<std::u16string>(Generic::trim(
                makeRange(str),
                Utf16Encoding(),
                predicate));
    }

    std::u16string trimEnd(const std::u16string& str)
    {
        return fromRange<std::u16string>(Generic::trimEnd(
                makeRange(str),
                Utf16Encoding(),
                Unicode::isWhitespace));
    }

    std::u16string trimEnd(const std::u16string& str,
                        std::function<bool(uint32_t)> predicate)
    {
        return fromRange<std::u16string>(Generic::trimEnd(
                makeRange(str),
                Utf16Encoding(),
                predicate));
    }

    std::u16string trimStart(const std::u16string& str)
    {
        return fromRange<std::u16string>(Generic::trimStart(
                makeRange(str),
                Utf16Encoding(),
                Unicode::isWhitespace));
    }

    std::u16string trimStart(const std::u16string& str,
                          std::function<bool(uint32_t)> predicate)
    {
        return fromRange<std::u16string>(Generic::trimStart(
                makeRange(str),
                Utf16Encoding(),
                predicate));
    }

    std::u16string unescape(const std::u16string& str, EscapeType_t type)
    {
        return Generic::unescape<std::u16string>(
                makeRange(str),
                type,
                Utf16Encoding());
    }

    std::u16string upper(const std::u16string& str)
    {
        return Generic::upper<std::u16string>(makeRange(str),
                                              Utf16Encoding());
    }
}}
