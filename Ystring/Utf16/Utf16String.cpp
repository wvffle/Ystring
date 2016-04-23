//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-09-11.
//
// This file is distributed under the Simplified BSD License.
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
    typedef std::u16string String;
    typedef Utf16Encoding Enc;

    String& append(String& str, char32_t chr)
    {
        append(makeStringReference(str), chr, Enc());
        return str;
    }

    int32_t caseInsensitiveCompare(const String& str, const String& cmp)
    {
        return Generic::caseInsensitiveCompare(makeRange(str),
                                               makeRange(cmp),
                                               Enc());
    }

    bool caseInsensitiveEqual(const String& str, const String& cmp)
    {
        return Generic::caseInsensitiveEqual(makeRange(str),
                                             makeRange(cmp),
                                             Enc());
    }

    bool caseInsensitiveLess(const String& str, const String& cmp)
    {
        return Generic::caseInsensitiveLess(makeRange(str),
                                            makeRange(cmp),
                                            Enc());
    }

    bool contains(const String& str, char32_t chr)
    {
        return Generic::contains(makeRange(str), chr, Enc());
    }

    size_t countCharacters(const String& str)
    {
        return Generic::countCharacters(makeRange(str), Enc());
    }

    size_t countCharacters(std::string::const_iterator first,
                           std::string::const_iterator last)
    {
        return Generic::countCharacters(makeRange(first, last), Enc());
    }

    size_t countCodePoints(const String& str)
    {
        return Generic::countCodePoints(makeRange(str), Enc());
    }

    bool endsWith(const String& str, const String& cmp, FindFlags_t flags)
    {
        return Generic::endsWith(
                makeRange(str), makeRange(cmp), Enc(), flags);
    }

    String escape(const String& str, EscapeType_t mode)
    {
        return Generic::escape<String>(makeRange(str), mode, Enc());
    }

    StringIteratorPair findFirst(
            String& str,
            const String& cmp,
            FindFlags_t flags)
    {
        return Generic::findFirst(makeRange(str), makeRange(cmp),
                                  Enc(), flags);
    }

    StringConstIteratorPair findFirst(
            const String& str,
            const String& cmp,
            FindFlags_t flags)
    {
        return Generic::findFirst(makeRange(str), makeRange(cmp),
                                  Enc(), flags);
    }

    StringIteratorPair findFirst(
            String::iterator first,
            String::iterator last,
            const String& cmp,
            FindFlags_t flags)
    {
        return Generic::findFirst(makeRange(first, last), makeRange(cmp),
                                  Enc(), flags);
    }

    StringConstIteratorPair findFirst(
            String::const_iterator first,
            String::const_iterator last,
            const String& cmp,
            FindFlags_t flags)
    {
        return Generic::findFirst(makeRange(first, last), makeRange(cmp),
                                  Enc(), flags);
    }

    StringIteratorPair findFirstNewline(String& str)
    {
        return Generic::findFirstNewline(makeRange(str), Enc());
    }

    StringConstIteratorPair findFirstNewline(const String& str)
    {
        return Generic::findFirstNewline(makeRange(str), Enc());
    }

    StringIteratorPair findFirstNewline(String::iterator first,
                                        String::iterator last)
    {
        return Generic::findFirstNewline(makeRange(first, last), Enc());
    }

    StringConstIteratorPair findFirstNewline(String::const_iterator first,
                                             String::const_iterator last)
    {
        return Generic::findFirstNewline(makeRange(first, last), Enc());
    }

    StringIteratorPair findLast(
            String& str,
            const String& cmp,
            FindFlags_t flags)
    {
        return Generic::findLast(makeRange(str), makeRange(cmp),
                                 Enc(), flags);
    }

    StringConstIteratorPair findLast(
            const String& str,
            const String& cmp,
            FindFlags_t flags)
    {
        return Generic::findLast(makeRange(str), makeRange(cmp),
                                 Enc(), flags);
    }

    StringIteratorPair findLast(
            String::iterator first,
            String::iterator last,
            const String& cmp,
            FindFlags_t flags)
    {
        return Generic::findLast(makeRange(first, last), makeRange(cmp),
                                 Enc(), flags);
    }

    StringConstIteratorPair findLast(
            String::const_iterator first,
            String::const_iterator last,
            const String& cmp,
            FindFlags_t flags)
    {
        return Generic::findLast(makeRange(first, last), makeRange(cmp),
                                 Enc(), flags);
    }

    StringIteratorPair findLastNewline(String& str)
    {
        return Generic::findLastNewline(makeRange(str), Enc());
    }

    StringConstIteratorPair findLastNewline(const String& str)
    {
        return Generic::findLastNewline(makeRange(str), Enc());
    }

    StringIteratorPair findLastNewline(String::iterator first,
                                       String::iterator last)
    {
        return Generic::findLastNewline(makeRange(first, last), Enc());
    }

    StringConstIteratorPair findLastNewline(
            String::const_iterator first,
            String::const_iterator last)
    {
        return Generic::findLastNewline(makeRange(first, last), Enc());
    }

    char32_t getCodePoint(const String& str, ptrdiff_t n)
    {
        return Generic::getCodePoint(makeRange(str), n, Enc());
    }

    bool hasEscapedCharacters(const std::string& str, EscapeType_t type)
    {
        return Generic::hasEscapedCharacters(makeRange(str), type);
    }

    bool hasUnescapedCharacters(const std::string& str, EscapeType_t type)
    {
        return Generic::hasUnescapedCharacters(makeRange(str), type, Enc());
    }

    String insert(const String& str, ptrdiff_t pos, const String& sub)
    {
        return Generic::insert<String>(
                makeRange(str), pos, makeRange(sub), Enc());
    }

    String insert(const String& str, ptrdiff_t pos, char32_t chr)
    {
        return Generic::insert<String>(makeRange(str), pos, chr, Enc());
    }

    bool isAlphaNumeric(const String& str)
    {
        return isAlphaNumeric(makeRange(str), Enc());
    }

    bool isAlphaNumeric(String::iterator first, String::iterator last)
    {
        return isAlphaNumeric(makeRange(first, last), Enc());
    }

    bool isAlphaNumeric(String::const_iterator first,
                        String::const_iterator last)
    {
        return isAlphaNumeric(makeRange(first, last), Enc());
    }

    bool isValidUtf16(const String& str)
    {
        return DecoderResult::OK == std::get<2>(
                nextInvalidUtf16CodePoint<false>(begin(str), end(str)));
    }

    String join(const std::vector<String>& strings,
                const String& delimiter)
    {
        return join(strings.data(), strings.size(), delimiter);
    }

    String join(const String* strings, size_t count, const String& delimiter)
    {
        return delimiter.empty() ?
               Generic::join<String>(strings, strings + count) :
               Generic::join<String>(
                        strings, strings + count, makeRange(delimiter));
    }

    String lower(const String& str)
    {
        return Generic::lower<String>(makeRange(str), Enc());
    }

    String::iterator nextCharacter(String::iterator& first,
                                   String::iterator& last,
                                   size_t n)
    {
        return Generic::nextCharacter(makeRange(first, last), n, Enc());
    }

    String::const_iterator nextCharacter(
            String::const_iterator& first,
            String::const_iterator& last,
            size_t n)
    {
        return Generic::nextCharacter(makeRange(first, last), n, Enc());
    }

    String::iterator nthCharacter(String& str, ptrdiff_t n)
    {
        return Generic::nthCharacter(makeRange(str), n, Enc());
    }

    String::const_iterator nthCharacter(const String& str, ptrdiff_t n)
    {
        return Generic::nthCharacter(makeRange(str), n, Enc());
    }

    String::iterator prevCharacter(String::iterator& first,
                                   String::iterator& last,
                                   size_t n)
    {
        return Generic::prevCharacter(makeRange(first, last), n , Enc());
    }

    String::const_iterator prevCharacter(String::const_iterator& first,
                                         String::const_iterator& last,
                                         size_t n)
    {
        return Generic::prevCharacter(makeRange(first, last), n, Enc());
    }

    String replace(const String& str,
                   const String& cmp,
                   const String& repl,
                   ptrdiff_t maxReplacements,
                   FindFlags_t flags)
    {
        return Generic::replace<String>(
                makeRange(str), makeRange(cmp),
                makeRange(repl), Enc(),
                maxReplacements, flags);
    }

    String replace(const String& str,
                   ptrdiff_t start, ptrdiff_t end,
                   const String& repl)
    {
        return Generic::replace<String>(
                makeRange(str), start, end, makeRange(repl), Enc());
    }

    String replaceCodePoint(const String& s,
                            char32_t from,
                            char32_t to,
                            ptrdiff_t maxReplacements)
    {
        char16_t fBuf[2];
        auto fIt = std::begin(fBuf);
        auto fromSize = encodeUtf16(fIt, std::end(fBuf), from);
        char16_t tBuf[2];
        auto tIt = std::begin(tBuf);
        auto toSize = encodeUtf16(tIt, std::end(tBuf), to);
        return Generic::replace<String>(
                makeRange(s),
                makeRange(fBuf, fBuf + fromSize),
                makeRange(tBuf, tBuf + toSize),
                Enc(),
                maxReplacements, FindFlags::DEFAULTS);
    }

    String replaceInvalidUtf16(const String& str, char32_t chr)
    {
        String result;
        result.reserve(str.size());
        auto it = str.begin();
        auto end = str.end();
        while (true)
        {
            auto invalid = nextInvalidUtf16CodePoint<false>(it, end);
            result.append(it, std::get<0>(invalid));
            if (std::get<0>(invalid) == end)
                break;
            append(result, chr);
            it = std::get<1>(invalid);
        }
        return result;
    }

    String& replaceInvalidUtf16InPlace(String& str, char16_t chr)
    {
        assert(chr > 0);
        auto it = str.begin();
        while (it != str.end())
        {
            char32_t cp;
            if (nextUtf16CodePoint<false>(cp, it, str.end()) !=
                    DecoderResult::OK)
            {
                *it++ = chr;
            }
        }
        return str;
    }

    String reverse(const String& str)
    {
        return Generic::reverse<String>(makeRange(str), Enc());
    }

    std::vector<String> split(const String& str,
                              ptrdiff_t maxSplits,
                              SplitFlags_t flags)
    {
        return Generic::split<String>(
                makeRange(str), Enc(), maxSplits, flags);
    }

    std::vector<String> split(const String& str,
                              const String& sep,
                              ptrdiff_t maxSplits,
                              SplitFlags_t flags)
    {
      return Generic::split<String>(
              makeRange(str), makeRange(sep), Enc(), maxSplits, flags);
    }

    std::vector<String> splitIf(const String& str,
                                std::function<bool(char32_t)> predicate,
                                ptrdiff_t maxSplits,
                                SplitFlags_t flags)
    {
        return Generic::splitIf<String>(
                makeRange(str), Enc(), predicate, maxSplits, flags);
    }

    std::vector<String> splitLines(const String& str,
                                   ptrdiff_t maxSplits,
                                   SplitFlags_t flags)
    {
        return Generic::splitLines<String>(
                makeRange(str), Enc(), maxSplits, flags);
    }

    bool startsWith(const String& str, const String& cmp, FindFlags_t flags)
    {
        return Generic::startsWith(makeRange(str), makeRange(cmp),
                                   Enc(), flags);
    }

    String substring(const String& str, ptrdiff_t start, ptrdiff_t end)
    {
        return Generic::substring<String>(makeRange(str), start, end, Enc());
    }

    String title(const String& str)
    {
        return Generic::title<String>(makeRange(str), Enc());
    }

    String toUtf16(char32_t chr)
    {
        String s;
        append(s, chr);
        return s;
    }

    String toUtf16(const std::string& str, Encoding_t encoding)
    {
        return toUtf16(str.data(), str.size(), encoding);
    }

    String toUtf16(const std::wstring& str, Encoding_t encoding)
    {
        return toUtf16(str.data(), str.size(), encoding);
    }

    #define CASE_ENCODING(enumName, encodingName) \
        case enumName: \
            return Generic::convert<String>( \
                    makeRange(str, str + length), \
                    encodingName(), \
                    Enc())

    String toUtf16(const char* str, size_t length, Encoding_t encoding)
    {
        switch (encoding)
        {
        CASE_ENCODING(Encoding::UTF_8, Utf8::Utf8Encoding);
        CASE_ENCODING(Encoding::IBM_437, CodePage::Ibm437Encoding);
        CASE_ENCODING(Encoding::IBM_850, CodePage::Ibm850Encoding);
        CASE_ENCODING(Encoding::LATIN_1, CodePage::Latin1Encoding);
        CASE_ENCODING(Encoding::LATIN_5, CodePage::Latin5Encoding);
        CASE_ENCODING(Encoding::LATIN_6, CodePage::Latin6Encoding);
        CASE_ENCODING(Encoding::LATIN_9, CodePage::Latin9Encoding);
        CASE_ENCODING(Encoding::WINDOWS_1250, CodePage::Windows1250Encoding);
        CASE_ENCODING(Encoding::WINDOWS_1252, CodePage::Windows1252Encoding);
        CASE_ENCODING(Encoding::UTF_16_BE, Utf16::Utf16BEEncoding);
        CASE_ENCODING(Encoding::UTF_16_LE, Utf16::Utf16LEEncoding);
        CASE_ENCODING(Encoding::UTF_32_BE, Utf32::Utf32BEEncoding);
        CASE_ENCODING(Encoding::UTF_32_LE, Utf32::Utf32LEEncoding);
        default:
            YSTRING_THROW("toUtf16: unsupported encoding " +
                          std::to_string(int64_t(encoding)));
        }
    }

    String toUtf16(const char16_t* str, size_t length, Encoding_t encoding)
    {
        switch (encoding)
        {
        CASE_ENCODING(Encoding::UTF_16_BE, Utf16::Utf16BEEncoding);
        CASE_ENCODING(Encoding::UTF_16_LE, Utf16::Utf16LEEncoding);
        default:
            YSTRING_THROW("toUtf16: unsupported encoding " +
                          std::to_string(int64_t(encoding)));
        }
    }

    String toUtf16(const char32_t* str, size_t length, Encoding_t encoding)
    {
        switch (encoding)
        {
        CASE_ENCODING(Encoding::UTF_32_BE, Utf32::Utf32BEEncoding);
        CASE_ENCODING(Encoding::UTF_32_LE, Utf32::Utf32LEEncoding);
        default:
            YSTRING_THROW("toUtf16: unsupported encoding " +
                          std::to_string(int64_t(encoding)));
        }
    }

    String toUtf16(const std::u16string& str, Encoding_t encoding)
    {
        return toUtf16(str.data(), str.size(), encoding);
    }

    String toUtf16(const std::u32string& str, Encoding_t encoding)
    {
        return toUtf16(str.data(), str.size(), encoding);
    }

    String toUtf16(const wchar_t* str, size_t length, Encoding_t encoding)
    {
        return toUtf16(internal_char_type_cast(str), length, encoding);
    }

    String trim(const String& str)
    {
        return fromRange<String>(Generic::trim(
                makeRange(str), Enc(), Unicode::isWhitespace));
    }

    String trim(const String& str, std::function<bool(char32_t)> predicate)
    {
        return fromRange<String>(Generic::trim(
                makeRange(str), Enc(), predicate));
    }

    String trimEnd(const String& str)
    {
        return fromRange<String>(Generic::trimEnd(
                makeRange(str), Enc(), Unicode::isWhitespace));
    }

    String trimEnd(const String& str, std::function<bool(char32_t)> predicate)
    {
        return fromRange<String>(Generic::trimEnd(
                makeRange(str), Enc(), predicate));
    }

    String trimStart(const String& str)
    {
        return fromRange<String>(Generic::trimStart(
                makeRange(str), Enc(), Unicode::isWhitespace));
    }

    String trimStart(const String& str,
                     std::function<bool(char32_t)> predicate)
    {
        return fromRange<String>(Generic::trimStart(
                makeRange(str), Enc(), predicate));
    }

    String unescape(const String& str, EscapeType_t type)
    {
        return Generic::unescape<String>(makeRange(str), type, Enc());
    }

    String upper(const String& str)
    {
        return Generic::upper<String>(makeRange(str), Enc());
    }
}}
