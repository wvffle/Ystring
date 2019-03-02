//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-09-12.
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#include "../../include/Ystring/Utf16.hpp"

#include "../../include/Ystring/Unicode/UnicodePredicates.hpp"
#include "../../src/Ystring/Utf8/Utf8Chars.hpp"
#include "../../src/Ystring/Utf16/Utf16Chars.hpp"
#include "../Ytest/Ytest.hpp"
#include "../../src/Ystring/Utilities/Endian.hpp"

namespace
{
    using namespace Ystring;

    void test_append()
    {
        std::u16string s;
        Y_EQUAL(Utf16::append(s, Unicode::GREEK_SMALL_FINAL_SIGMA),
                UTF16_GREEK_SMALL_FINAL_SIGMA);
        Y_EQUAL(Utf16::append(s, Unicode::PUNCTUATION_SPACE),
                UTF16_GREEK_SMALL_FINAL_SIGMA UTF16_PUNCTUATION_SPACE);
    }

    void test_caseInsensitiveCompare()
    {
        Y_LESS(Utf16::caseInsensitiveCompare(
                u"aBc" UTF16_GREEK_SMALL_SIGMA,
                u"AbC" UTF16_GREEK_CAPITAL_SIGMA u"d"), 0);
        Y_LESS(Utf16::caseInsensitiveCompare(
                u"aBc" UTF16_GREEK_SMALL_SIGMA u"d",
                u"AbC" UTF16_GREEK_CAPITAL_TAU), 0);
        Y_EQUAL(Utf16::caseInsensitiveCompare(
                u"aBc" UTF16_GREEK_SMALL_SIGMA,
                u"AbC" UTF16_GREEK_CAPITAL_SIGMA), 0);
        Y_GREATER(Utf16::caseInsensitiveCompare(
                u"aBc" UTF16_GREEK_SMALL_SIGMA u"a",
                u"AbC" UTF16_GREEK_CAPITAL_SIGMA), 0);
        Y_GREATER(Utf16::caseInsensitiveCompare(
                u"aBc" UTF16_GREEK_SMALL_PSI u"d",
                u"AbC" UTF16_GREEK_CAPITAL_TAU), 0);
    }

    void test_caseInsensitiveEqual()
    {
        Y_ASSERT(Utf16::caseInsensitiveEqual(
                u"aBc" UTF16_GREEK_SMALL_SIGMA,
                u"AbC" UTF16_GREEK_CAPITAL_SIGMA));
        Y_ASSERT(!Utf16::caseInsensitiveEqual(
                u"aBc&8q" UTF16_GREEK_SMALL_SIGMA,
                u"AbC&8p" UTF16_GREEK_CAPITAL_SIGMA));
    }

    void test_caseInsensitiveLess()
    {
        Y_ASSERT(!Utf16::caseInsensitiveLess(
                u"aBc" UTF16_GREEK_SMALL_SIGMA u"D",
                u"AbC" UTF16_GREEK_CAPITAL_SIGMA u"d"));
        Y_ASSERT(Utf16::caseInsensitiveLess(
                u"aBc" UTF16_GREEK_SMALL_SIGMA u"d",
                u"AbC" UTF16_GREEK_CAPITAL_TAU));
    }

    void test_contains()
    {
        Y_ASSERT(Utf16::contains(u"ABCDE", 'D'));
        Y_ASSERT(!Utf16::contains(u"ABCDE", 'F'));
    }

    void test_countCharacters()
    {
        Y_EQUAL(Utf16::countCharacters(
                u"A" UTF16_COMBINING_RING_ABOVE u"BCDE" UTF16_COMBINING_TILDE),
                5);
    }

    void test_countCodePoints()
    {
        Y_EQUAL(Utf16::countCodePoints(
                u"A" UTF16_COMBINING_RING_ABOVE u"BCDE" UTF16_COMBINING_TILDE),
                7);
    }

    void test_endsWith()
    {
        Y_ASSERT(Utf16::endsWith(u"aBc" UTF16_GREEK_SMALL_SIGMA u"D",
                                 u"C" UTF16_GREEK_CAPITAL_SIGMA u"d",
                                 FindFlags::CASE_INSENSITIVE));
        Y_ASSERT(!Utf16::endsWith(u"aBc" UTF16_GREEK_SMALL_SIGMA u"D",
                                  u"E" UTF16_GREEK_CAPITAL_SIGMA u"d",
                                  FindFlags::CASE_INSENSITIVE));
        Y_ASSERT(Utf16::endsWith(u"aBc" UTF16_GREEK_SMALL_SIGMA u"D",
                                 u"c" UTF16_GREEK_SMALL_SIGMA u"D"));
    }

    void test_escape_BACKSLASH()
    {
        const char16_t str[] = u"ab\x01" u"cd\nef\x7Fgh\x80";
        auto expected = u"ab\\u0001cd\\nef\\u007Fgh\\u0080";
        Y_EQUAL(Utf16::escape(str), expected);
        Y_EQUAL(Utf16::escape(u"\uFFFF"), u"\uFFFF");
    }

    void test_escape_BACKSLASH_ASCII()
    {
        auto expected = u"\\uFFFF";
        Y_EQUAL(Utf16::escape(u"\uFFFF", EscapeType::BACKSLASH_ASCII),
                 expected);
    }

    void test_escape_BACKSLASH_ASCII_SMART()
    {
        Y_EQUAL(Utf16::escape(u"\n\tABCD", EscapeType::BACKSLASH_ASCII_SMART),
                u"\\n\\tABCD");
        Y_EQUAL(Utf16::escape(u"\u001F", EscapeType::BACKSLASH_ASCII_SMART),
                u"\\x1F");
        Y_EQUAL(Utf16::escape(u"\u00FF", EscapeType::BACKSLASH_ASCII_SMART),
                u"\\xFF");
        Y_EQUAL(Utf16::escape(u"\u0100", EscapeType::BACKSLASH_ASCII_SMART),
                u"\\u0100");
        Y_EQUAL(Utf16::escape(u"\uFFFF", EscapeType::BACKSLASH_ASCII_SMART),
                u"\\uFFFF");
        Y_EQUAL(Utf16::escape(u"\U00010000", EscapeType::BACKSLASH_ASCII_SMART),
                u"\\U00010000");
        Y_EQUAL(Utf16::escape(u"\U000FFFFF", EscapeType::BACKSLASH_ASCII_SMART),
                u"\\U000FFFFF");
    }

    void test_escape_JSON()
    {
        Y_EQUAL(Utf16::escape(u"\n\tABCD", EscapeType::JSON), u"\\n\\tABCD");
        Y_EQUAL(Utf16::escape(u"\x7f", EscapeType::JSON), u"\\u007F");
        Y_EQUAL(Utf16::escape(u"\x80", EscapeType::JSON), u"\\u0080");
    }

    void test_escape_JSON_ASCII()
    {
        Y_EQUAL(Utf16::escape(u"\n\t\"ABCD", EscapeType::JSON_ASCII),
                u"\\n\\t\\\"ABCD");
        Y_EQUAL(Utf16::escape(u"\x7f", EscapeType::JSON_ASCII),
                u"\\u007F");
        Y_EQUAL(Utf16::escape(u"\x80", EscapeType::JSON_ASCII),
                u"\\u0080");
        Y_EQUAL(Utf16::escape(u"\u0100", EscapeType::JSON_ASCII),
                u"\\u0100");
        Y_EQUAL(Utf16::escape(u"\uFFFF", EscapeType::JSON_ASCII),
                u"\\uFFFF");
    }

    void test_escape_XML_ATTRIBUTE()
    {
        Y_EQUAL(Utf16::escape(u"\n\tA&\"'<B>", EscapeType::XML_ATTRIBUTE),
                u"&#xA;&#x9;A&amp;&quot;&apos;&lt;B&gt;");
    }

    void test_escape_XML_TEXT()
    {
        Y_EQUAL(Utf16::escape(u"\n\tA&\"'<B>", EscapeType::XML_TEXT),
                u"\n\tA&amp;\"\'&lt;B&gt;");
    }

    void test_findLast()
    {
        auto s = std::u16string(u"abc_gh" UTF16_GREEK_CAPITAL_SIGMA  u"IJ_gH"
                             UTF16_GREEK_SMALL_SIGMA u"Ij_kLM_nop");
        auto r = Utf16::findLast(s, u"gh" UTF16_GREEK_CAPITAL_SIGMA u"ij",
                                FindFlags::CASE_INSENSITIVE);
        Y_EQUAL(std::u16string(r.first, r.second),
                 u"gH" UTF16_GREEK_SMALL_SIGMA u"Ij");
        auto t = Utf16::findLast(r.first, r.second,
                                 UTF16_GREEK_CAPITAL_SIGMA u"i",
                                 FindFlags::CASE_INSENSITIVE);
        Y_EQUAL(std::u16string(t.first, t.second),
                UTF16_GREEK_SMALL_SIGMA u"I");
        auto u = Utf16::findLast(r.first, r.second,
                                 UTF16_GREEK_CAPITAL_SIGMA u"i");
        Y_ASSERT(u.first == u.second && u.first == r.first);
    }

    void test_findLastNewline()
    {
        auto str = std::u16string(u"abc\ndef\r\nghi");
        auto s = make_pair(begin(str), end(str));
        auto r = Utf16::findLastNewline(str);
        Y_EQUAL(std::u16string(r.second, s.second), u"ghi");
        auto t = make_pair(s.first, r.first);
        r = Utf16::findLastNewline(t.first, t.second);
        Y_EQUAL(std::u16string(r.first, r.second), u"\n");
        Y_EQUAL(std::u16string(r.second, t.second), u"def");
        t.second = r.first;
        r = Utf16::findLastNewline(t.first, t.second);
        Y_ASSERT(r.first == r.second);
        Y_ASSERT(r.first == t.first);
        Y_EQUAL(std::u16string(r.first, t.second), u"abc");
    }

    void test_findFirst()
    {
        auto s = std::u16string(u"abc_ghIJ_gH" UTF16_GREEK_SMALL_SIGMA
                              u"Ij_kLM_nop");
        auto r = Utf16::findFirst(s, u"gh" UTF16_GREEK_CAPITAL_SIGMA u"ij",
                                   FindFlags::CASE_INSENSITIVE);
        Y_EQUAL(std::u16string(r.first, r.second),
                 u"gH" UTF16_GREEK_SMALL_SIGMA u"Ij");
        auto t = Utf16::findFirst(r.first, r.second,
                                  UTF16_GREEK_CAPITAL_SIGMA u"i",
                                  FindFlags::CASE_INSENSITIVE);
        Y_EQUAL(std::u16string(t.first, t.second),
                UTF16_GREEK_SMALL_SIGMA u"I");
        auto u = Utf16::findFirst(r.first, r.second,
                                  UTF16_GREEK_CAPITAL_SIGMA u"i");
        Y_ASSERT(u.first == u.second && u.second == r.second);
    }

    void test_findFirstNewline()
    {
        auto str = std::u16string(u"abc\ndef\r\nghi");
        auto s = make_pair(begin(str), end(str));
        auto r = Utf16::findFirstNewline(str);
        Y_EQUAL(std::u16string(s.first, r.first), u"abc");
        auto t = make_pair(r.second, s.second);
        r = Utf16::findFirstNewline(t.first, t.second);
        Y_EQUAL(std::u16string(t.first, r.first), u"def");
        t.first = r.second;
        r = Utf16::findFirstNewline(t.first, t.second);
        Y_ASSERT(r.first == r.second);
        Y_EQUAL(std::u16string(t.first, r.first), u"ghi");
    }

    void test_insert()
    {
        auto str = u"The " UTF16_GREEK_SMALL_OMEGA
                   UTF16_COMBINING_BRIDGE_ABOVE UTF16_COMBINING_TILDE
                   u" and the A" UTF16_COMBINING_INVERTED_BREVE
                   UTF16_COMBINING_DOT_ABOVE u".";
        auto r = Utf16::insert(Utf16::insert(str, 13, u" insanely"),
                               -2, u"great ");
        Y_EQUAL(r, u"The " UTF16_GREEK_SMALL_OMEGA
                UTF16_COMBINING_BRIDGE_ABOVE UTF16_COMBINING_TILDE
                u" and the insanely great A" UTF16_COMBINING_INVERTED_BREVE
                UTF16_COMBINING_DOT_ABOVE u".");
    }

    void test_insertChar()
    {
        auto str = u"The " UTF16_GREEK_SMALL_OMEGA
                   UTF16_COMBINING_BRIDGE_ABOVE UTF16_COMBINING_TILDE
                   u" and the A" UTF16_COMBINING_INVERTED_BREVE
                   UTF16_COMBINING_DOT_ABOVE u".";
        auto r = Utf16::insert(str, 5, Unicode::GREEK_SMALL_FINAL_SIGMA);
        Y_EQUAL(r, u"The " UTF16_GREEK_SMALL_OMEGA
                    UTF16_COMBINING_BRIDGE_ABOVE UTF16_COMBINING_TILDE
                    UTF16_GREEK_SMALL_FINAL_SIGMA
                    u" and the A" UTF16_COMBINING_INVERTED_BREVE
                    UTF16_COMBINING_DOT_ABOVE u".");
    }

    void test_isAlphaNumeric()
    {
        Y_ASSERT(Utf16::isAlphaNumeric(u"Ab1"));
        Y_ASSERT(!Utf16::isAlphaNumeric(u"Ab-1"));
        Y_ASSERT(!Utf16::isAlphaNumeric(u""));
        std::u16string s(u"2v" UTF16_GREEK_SMALL_OMEGA
                               UTF16_COMBINING_BRIDGE_ABOVE);
        Y_ASSERT(Utf16::isAlphaNumeric(begin(s), end(s)));
    }

    void test_isValidUtf16()
    {
        Y_ASSERT(Utf16::isValidUtf16(u"\uD7FF"));
        char16_t a[] = {0xD800, 0};
        Y_ASSERT(!Utf16::isValidUtf16(std::u16string(a)));
        char16_t b[] = {0xD800, 0xDC00, 0};
        Y_ASSERT(Utf16::isValidUtf16(std::u16string(b)));
        char16_t c[] = {0xDC00, 0xD800, 0};
        Y_ASSERT(!Utf16::isValidUtf16(std::u16string(c)));
        char16_t d[] = {0xD800, 'A', 0};
        Y_ASSERT(!Utf16::isValidUtf16(std::u16string(d)));
        char16_t e[] = {0xD800, 0xDBFF, 0};
        Y_ASSERT(!Utf16::isValidUtf16(std::u16string(e)));
        Y_ASSERT(Utf16::isValidUtf16(u"\uE000"));
    }

    void test_join()
    {
        std::u16string rawStrings[] = {u"foo", u"faa", u"fii", u"fee",
                                       u"fuu"};
        auto result1 = Utf16::join(rawStrings, 5);
        Y_EQUAL(result1, u"foofaafiifeefuu");
        auto result2 = Utf16::join(rawStrings, 5, u":-:");
        Y_EQUAL(result2, u"foo:-:faa:-:fii:-:fee:-:fuu");
        std::vector<std::u16string> strings(std::begin(rawStrings),
                                          std::end(rawStrings));
        result1 = Utf16::join(strings);
        Y_EQUAL(result1, u"foofaafiifeefuu");
        result2 = Utf16::join(strings, u":-:");
        Y_EQUAL(result2, u"foo:-:faa:-:fii:-:fee:-:fuu");
    }

    void test_lower()
    {
        Y_EQUAL(Utf16::lower(u"aBc" UTF16_GREEK_CAPITAL_SIGMA u"d12$E"),
                u"abc" UTF16_GREEK_SMALL_SIGMA u"d12$e");
    }

    void test_nextCharacter_const()
    {
        const std::u16string str(u"AB" UTF16_GREEK_SMALL_OMEGA
                              UTF16_COMBINING_BRIDGE_ABOVE
                              UTF16_COMBINING_TILDE u"C");
        auto b = str.begin(), e = str.end();
        Y_EQUAL(distance(str.begin(), Utf16::nextCharacter(b, e)), 1);
        Y_EQUAL(distance(str.begin(), Utf16::nextCharacter(b, e, 0)), 0);
        Y_EQUAL(distance(str.begin(), Utf16::nextCharacter(b, e, 1)), 1);
        Y_EQUAL(distance(str.begin(), Utf16::nextCharacter(b, e, 2)), 2);
        Y_EQUAL(distance(str.begin(), Utf16::nextCharacter(b, e, 3)), 5);
        Y_EQUAL(distance(str.begin(), Utf16::nextCharacter(b, e, 4)), 6);
        Y_THROWS(Utf16::nextCharacter(b, e, 5), YstringException);
    }

    void test_nextCharacter_mutable()
    {
        std::u16string str(u"AB" UTF16_GREEK_SMALL_OMEGA
                                 UTF16_COMBINING_BRIDGE_ABOVE
                                 UTF16_COMBINING_TILDE u"C");
        auto b = str.begin(), e = str.end();
        Y_EQUAL(distance(str.begin(), Utf16::nextCharacter(b, e)), 1);
        Y_EQUAL(distance(str.begin(), Utf16::nextCharacter(b, e, 0)), 0);
        Y_EQUAL(distance(str.begin(), Utf16::nextCharacter(b, e, 1)), 1);
        Y_EQUAL(distance(str.begin(), Utf16::nextCharacter(b, e, 2)), 2);
        Y_EQUAL(distance(str.begin(), Utf16::nextCharacter(b, e, 3)), 5);
        Y_EQUAL(distance(str.begin(), Utf16::nextCharacter(b, e, 4)), 6);
        Y_THROWS(Utf16::nextCharacter(b, e, 5), YstringException);
    }

    void test_nthCharacter()
    {
        std::u16string str(u"AB" UTF16_GREEK_SMALL_OMEGA
                                 UTF16_COMBINING_BRIDGE_ABOVE
                                 UTF16_COMBINING_TILDE u"C");
        Y_EQUAL(distance(str.begin(), Utf16::nthCharacter(str, 0)), 0);
        Y_EQUAL(distance(str.begin(), Utf16::nthCharacter(str, 1)), 1);
        Y_EQUAL(distance(str.begin(), Utf16::nthCharacter(str, 2)), 2);
        Y_EQUAL(distance(str.begin(), Utf16::nthCharacter(str, 3)), 5);
        Y_EQUAL(distance(str.begin(), Utf16::nthCharacter(str, 4)), 6);
        Y_EQUAL(distance(str.begin(), Utf16::nthCharacter(str, -1)), 5);
        Y_EQUAL(distance(str.begin(), Utf16::nthCharacter(str, -2)), 2);
        Y_EQUAL(distance(str.begin(), Utf16::nthCharacter(str, -3)), 1);
        Y_EQUAL(distance(str.begin(), Utf16::nthCharacter(str, -4)), 0);
        Y_THROWS(Utf16::nthCharacter(str, 5), YstringException);
        Y_THROWS(Utf16::nthCharacter(str, -5), YstringException);
    }

    void test_prevCharacter_const()
    {
        const std::u16string str(u"AB" UTF16_GREEK_SMALL_OMEGA
                              UTF16_COMBINING_BRIDGE_ABOVE
                              UTF16_COMBINING_TILDE u"C");
        auto b = str.begin(), e = str.end();
        Y_EQUAL(distance(str.begin(), Utf16::prevCharacter(b, e)), 5);
        Y_EQUAL(distance(str.begin(), Utf16::prevCharacter(b, e, 0)), 6);
        Y_EQUAL(distance(str.begin(), Utf16::prevCharacter(b, e, 1)), 5);
        Y_EQUAL(distance(str.begin(), Utf16::prevCharacter(b, e, 2)), 2);
        Y_EQUAL(distance(str.begin(), Utf16::prevCharacter(b, e, 3)), 1);
        Y_EQUAL(distance(str.begin(), Utf16::prevCharacter(b, e, 4)), 0);
        Y_THROWS(Utf16::prevCharacter(b, e, 5), YstringException);
    }

    void test_prevCharacter_mutable()
    {
        std::u16string str(u"AB" UTF16_GREEK_SMALL_OMEGA
                                   UTF16_COMBINING_BRIDGE_ABOVE
                                   UTF16_COMBINING_TILDE u"C");
        auto b = str.begin(), e = str.end();
        Y_EQUAL(distance(str.begin(), Utf16::prevCharacter(b, e)), 5);
        Y_EQUAL(distance(str.begin(), Utf16::prevCharacter(b, e, 0)), 6);
        Y_EQUAL(distance(str.begin(), Utf16::prevCharacter(b, e, 1)), 5);
        Y_EQUAL(distance(str.begin(), Utf16::prevCharacter(b, e, 2)), 2);
        Y_EQUAL(distance(str.begin(), Utf16::prevCharacter(b, e, 3)), 1);
        Y_EQUAL(distance(str.begin(), Utf16::prevCharacter(b, e, 4)), 0);
        Y_THROWS(Utf16::prevCharacter(b, e, 5), YstringException);
    }

    void test_replace_indexes()
    {
        auto s = u"The " UTF16_GREEK_SMALL_OMEGA
                 UTF16_COMBINING_BRIDGE_ABOVE UTF16_COMBINING_TILDE
                 u" and the A" UTF16_COMBINING_INVERTED_BREVE
                 UTF16_COMBINING_DOT_ABOVE u".";
        Y_EQUAL(Utf16::replace(s, 6, -3, u"beats no"),
                 u"The " UTF16_GREEK_SMALL_OMEGA
                 UTF16_COMBINING_BRIDGE_ABOVE UTF16_COMBINING_TILDE
                 u" beats no A" UTF16_COMBINING_INVERTED_BREVE
                 UTF16_COMBINING_DOT_ABOVE u".");
    }

    void test_replace_string()
    {
        auto s = u"The " UTF16_GREEK_SMALL_OMEGA u" and the A.";
        Y_EQUAL(Utf16::replace(s,
                               UTF16_GREEK_SMALL_OMEGA u" and",
                               UTF16_GREEK_CAPITAL_OMEGA u" or"),
                 u"The " UTF16_GREEK_CAPITAL_OMEGA u" or the A.");
        Y_EQUAL(Utf16::replace(s,
                               UTF16_GREEK_CAPITAL_OMEGA u" aNd",
                               UTF16_GREEK_CAPITAL_SIGMA u" or"),
                 s);
        Y_EQUAL(Utf16::replace(s,
                               UTF16_GREEK_CAPITAL_OMEGA u" aNd",
                               UTF16_GREEK_CAPITAL_SIGMA u" or",
                               0, FindFlags::CASE_INSENSITIVE),
                u"The " UTF16_GREEK_CAPITAL_SIGMA u" or the A.");
        Y_EQUAL(Utf16::replace(s, UTF16_GREEK_SMALL_OMEGA u" and", u""),
                u"The  the A.");
        Y_EQUAL(Utf16::replace(s, u"", u"foo"), s);
    }

    void test_replace_string_backwards()
    {
        Y_EQUAL(Utf16::replace(u"123 foo 456 foo 789 foo 012",
                               u"foo", u"bar", -2),
                u"123 foo 456 bar 789 bar 012");
    }

    void test_replaceCodePoint()
    {
        Y_EQUAL(Utf16::replaceCodePoint(u"AB" UTF16_GREEK_SMALL_GAMMA u"D",
                                        Unicode::GREEK_SMALL_GAMMA,
                                        Unicode::FIGURE_SPACE),
                u"AB" UTF16_FIGURE_SPACE u"D");
        Y_EQUAL(Utf16::replaceCodePoint(u"ABCDCDECDEFGCD", 'C', '_', 3),
                u"AB_D_DE_DEFGCD");
        Y_EQUAL(Utf16::replaceCodePoint(u"ABCDCDECDEFGCD", 'C', '_', -3),
                u"ABCD_DE_DEFG_D");
    }

    void test_replaceInvalidUtf16()
    {
        char16_t raw[] = {'A', 0xD800, 'M', 0xD800, 0xDC00, 'Q', 0xDC00,
                          'X', 0};
        std::u16string s(raw);
        char16_t rawExpected[] = {
                'A', 0xFFFD, 'M', 0xD800, 0xDC00, 'Q', 0xFFFD,
                'X', 0};
        std::u16string expected(rawExpected);
        Y_EQUAL(Utf16::replaceInvalidUtf16(s), expected);
    }

    void test_replaceInvalidUtf16InPlace()
    {
        char16_t raw[] = {
                'A', 0xD800, 'M', 0xD800, 0xDC00, 'Q', 0xDC00,
                'X', 0};
        std::u16string s(raw);
        char16_t rawExpected[] = {
                'A', 0xFFFD, 'M', 0xD800, 0xDC00, 'Q', 0xFFFD,
                'X', 0};
        std::u16string expected(rawExpected);
        Y_EQUAL(Utf16::replaceInvalidUtf16InPlace(s), expected);
    }

    void test_reverse()
    {
        auto s = u"The " UTF16_GREEK_SMALL_OMEGA UTF16_COMBINING_BRIDGE_ABOVE
                 UTF16_COMBINING_TILDE u" and the A"
                 UTF16_COMBINING_INVERTED_BREVE UTF16_COMBINING_DOT_ABOVE u".";
        std::u16string result;
        Y_EQUAL(Utf16::reverse(s),
                u".A" UTF16_COMBINING_INVERTED_BREVE UTF16_COMBINING_DOT_ABOVE
                u" eht dna " UTF16_GREEK_SMALL_OMEGA
                UTF16_COMBINING_BRIDGE_ABOVE UTF16_COMBINING_TILDE u" ehT");
    }

    void test_split_caseInsensitive_NonASCII()
    {
        auto parts = Utf16::split(
                u":" UTF16_GREEK_CAPITAL_OMEGA u"Q:foo:"
                UTF16_GREEK_CAPITAL_OMEGA u"q:faa:"
                UTF16_GREEK_SMALL_OMEGA u"Q:bor:"
                UTF16_GREEK_SMALL_OMEGA u"q:",
                u":" UTF16_GREEK_SMALL_OMEGA u"q:",
                3,
                SplitFlags::CASE_INSENSITIVE);
        Y_EQUAL(parts.size(), 4);
        Y_EQUAL(parts[0], u"");
        Y_EQUAL(parts[1], u"foo");
        Y_EQUAL(parts[2], u"faa");
        Y_EQUAL(parts[3], u"bor:" UTF16_GREEK_SMALL_OMEGA u"q:");
    }

    void test_split_caseInsensitive_NoTail()
    {
        auto parts = Utf16::split(u"123:aB:321:AB:234:ab:", u":ab:", 0,
                                   SplitFlags::CASE_INSENSITIVE);
        Y_EQUAL(parts.size(), 4);
        Y_EQUAL(parts[0], u"123");
        Y_EQUAL(parts[1], u"321");
        Y_EQUAL(parts[2], u"234");
        Y_EQUAL(parts[3], u"");
    }

    void test_split_caseInsensitive_reverse()
    {
        auto parts = Utf16::split(u"1234ab4567AB8901aB2345", u"AB", -2,
                                  SplitFlags::CASE_INSENSITIVE |
                                  SplitFlags::IGNORE_REMAINDER);
        Y_EQUAL(parts.size(), 2);
        Y_EQUAL(parts[0], u"2345");
        Y_EQUAL(parts[1], u"8901");
    }

    void test_split_caseInsensitive_Tail()
    {
        auto parts = Utf16::split(u"123:aB:321:AB:234:Ab:432", u":ab:", 0,
                                  SplitFlags::CASE_INSENSITIVE);
        Y_EQUAL(parts.size(), 4);
        Y_EQUAL(parts[0], u"123");
        Y_EQUAL(parts[1], u"321");
        Y_EQUAL(parts[2], u"234");
        Y_EQUAL(parts[3], u"432");
    }

    void test_split_caseSensitive_Tail()
    {
        auto parts = Utf16::split(u"123:aB:321:AB:234:AB:432", u":AB:");
        Y_EQUAL(parts.size(), 3);
        Y_EQUAL(parts[0], u"123:aB:321");
        Y_EQUAL(parts[1], u"234");
        Y_EQUAL(parts[2], u"432");
    }

    void test_split_caseSensitive_NoTail()
    {
        auto parts = Utf16::split(u"123:aB:321:AB:234:AB:", u":AB:");
        Y_EQUAL(parts.size(), 3);
        Y_EQUAL(parts[0], u"123:aB:321");
        Y_EQUAL(parts[1], u"234");
        Y_EQUAL(parts[2], u"");
    }

    void test_split_whitespace()
    {
        auto parts = Utf16::split(u" foo faa\r\n\tfee bar "
                                          UTF16_EM_SPACE u"\tbor ");
        Y_EQUAL(parts.size(), 5);
        Y_EQUAL(parts[0], u"foo");
        Y_EQUAL(parts[1], u"faa");
        Y_EQUAL(parts[2], u"fee");
        Y_EQUAL(parts[3], u"bar");
        Y_EQUAL(parts[4], u"bor");
    }

    void test_split_whitespace_backwards()
    {
        auto parts = Utf16::split(u"haa baa ett yui ert swr", -2);
        Y_EQUAL(parts.size(), 3);
        Y_EQUAL(parts[0], u"swr");
        Y_EQUAL(parts[1], u"ert");
        Y_EQUAL(parts[2], u"haa baa ett yui");
    }

    void test_splitIf()
    {
        auto parts = Utf16::splitIf(
                u" foo faa\r\n\tfee bar " UTF16_EM_SPACE u"\tbor ",
                Unicode::isWhitespace, 0, SplitFlags::IGNORE_EMPTY);
        Y_EQUAL(parts.size(), 5);
        Y_EQUAL(parts[0], u"foo");
        Y_EQUAL(parts[1], u"faa");
        Y_EQUAL(parts[2], u"fee");
        Y_EQUAL(parts[3], u"bar");
        Y_EQUAL(parts[4], u"bor");
    }

    void do_test_splitIf(const std::u16string& s,
                         SplitFlags_t flags, ptrdiff_t count,
                         const std::u16string& expected)
    {
        auto parts = Utf16::splitIf(s, [](char32_t c){return c == ':';},
                                   count, flags);
        Y_EQUAL(parts.size(), expected.size());
        for (auto i = 0u; i < parts.size(); ++i)
        {
            auto expect = expected[i] == ' ' ? std::u16string()
                                             : expected.substr(i, 1);
            Y_EQUAL(parts[i], expect);
        }
    }


    void test_splitIf_flags()
    {
        auto D = SplitFlags::DEFAULTS;
        auto IF = SplitFlags::IGNORE_EMPTY_FRONT;
        auto II = SplitFlags::IGNORE_EMPTY_INTERMEDIATES;
        auto IB = SplitFlags::IGNORE_EMPTY_BACK;
        auto IE = SplitFlags::IGNORE_EMPTY;
        auto IR = SplitFlags::IGNORE_REMAINDER;
        Y_CALL(do_test_splitIf(u"", D, 0, u" "));
        Y_CALL(do_test_splitIf(u"", IF, 0, u""));
        Y_CALL(do_test_splitIf(u"", II + IB, 0, u" "));
        Y_CALL(do_test_splitIf(u":", D, 0, u"  "));
        Y_CALL(do_test_splitIf(u":", IF, 0, u" "));
        Y_CALL(do_test_splitIf(u":", IB, 0, u" "));
        Y_CALL(do_test_splitIf(u":", IF + IB, 0, u""));
        Y_CALL(do_test_splitIf(u":", IF + II + IB, 0, u""));
        Y_CALL(do_test_splitIf(u":", IR, 1, u" "));
        Y_CALL(do_test_splitIf(u"a:", IR, 1, u"a"));
        Y_CALL(do_test_splitIf(u"a:a", IR, 1, u"a"));
        Y_CALL(do_test_splitIf(u"::", D, 0, u"   "));
        Y_CALL(do_test_splitIf(u"::", IF + II + IB, 0, u""));
        Y_CALL(do_test_splitIf(u"::", II, 0, u"  "));
        Y_CALL(do_test_splitIf(u":a", IF, 0, u"a"));
        Y_CALL(do_test_splitIf(u"a::b", II, 1, u"ab"));
        Y_CALL(do_test_splitIf(u"a:b::c", IR, -1, u"c"));
        Y_CALL(do_test_splitIf(u"a:b::", IR, -1, u" "));
        Y_CALL(do_test_splitIf(u"a:b::", IE, -1, u"ba"));
    }

    void test_splitLines()
    {
        auto parts = Utf16::splitLines(
                u" foo\nfaa \r\n\tfee bar \vbor\f\rrubb");
        Y_EQUAL(parts.size(), 6);
        Y_EQUAL(parts[0], u" foo");
        Y_EQUAL(parts[1], u"faa ");
        Y_EQUAL(parts[2], u"\tfee bar ");
        Y_EQUAL(parts[3], u"bor");
        Y_EQUAL(parts[4], u"");
        Y_EQUAL(parts[5], u"rubb");
    }

    void test_startsWith()
    {
        Y_ASSERT(Utf16::startsWith(u"qF" UTF16_GREEK_SMALL_SIGMA u"aBcD",
                                   u"qF" UTF16_GREEK_CAPITAL_SIGMA,
                                   FindFlags::CASE_INSENSITIVE));
        Y_ASSERT(!Utf16::startsWith(u"qF" UTF16_GREEK_SMALL_SIGMA u"aBcD",
                                    u"qF" UTF16_GREEK_CAPITAL_SIGMA));
        Y_ASSERT(!Utf16::startsWith(u"qF" UTF16_GREEK_SMALL_SIGMA u"aBcD",
                                    u"qF" UTF16_GREEK_CAPITAL_SIGMA u"g",
                                    FindFlags::CASE_INSENSITIVE));
    }

    void test_substring()
    {
        std::u16string s(u"AB" UTF16_COMBINING_BRIDGE_ABOVE u"CD");
        Y_EQUAL(Utf16::substring(s, 0),
                u"AB" UTF16_COMBINING_BRIDGE_ABOVE u"CD");
        Y_EQUAL(Utf16::substring(s, 0, 4),
                u"AB" UTF16_COMBINING_BRIDGE_ABOVE u"CD");
        Y_EQUAL(Utf16::substring(s, 1, 3),
                u"B" UTF16_COMBINING_BRIDGE_ABOVE u"C");
        Y_EQUAL(Utf16::substring(s, 2, 2), u"");
        Y_EQUAL(Utf16::substring(s, 3, 1), u"");
        Y_EQUAL(Utf16::substring(s, 1, -1),
                u"B" UTF16_COMBINING_BRIDGE_ABOVE u"C");
        Y_EQUAL(Utf16::substring(s, 2, -2), u"");
        Y_EQUAL(Utf16::substring(s, 3, -4), u"");
        Y_EQUAL(Utf16::substring(s, -3),
                u"B" UTF16_COMBINING_BRIDGE_ABOVE u"CD");
        Y_EQUAL(Utf16::substring(s, -3, -1),
                u"B" UTF16_COMBINING_BRIDGE_ABOVE u"C");
        Y_EQUAL(Utf16::substring(s, -2, -2), u"");
        Y_EQUAL(Utf16::substring(s, -1, -3), u"");
    }

    void test_title()
    {
        Y_EQUAL(Utf16::title(u"aBc " UTF16_GREEK_SMALL_SIGMA u"De.fooB"),
                u"Abc " UTF16_GREEK_CAPITAL_SIGMA u"de.Foob");
    }

    void test_toUtf16_fromLatin1()
    {
        Y_EQUAL(Utf16::toUtf16("\xC5rb\xF8ker", Encoding::LATIN_1),
                UTF16_LATIN_CAPITAL_A_WITH_RING_ABOVE u"rb"
                UTF16_LATIN_SMALL_O_WITH_STROKE u"ker");
    }

    void test_toUtf16_fromUtf8()
    {
        Y_EQUAL(Utf16::toUtf16(UTF8_LATIN_CAPITAL_A_WITH_RING_ABOVE "rb"
                               UTF8_LATIN_SMALL_O_WITH_STROKE "ker",
                               Encoding::UTF_8),
                UTF16_LATIN_CAPITAL_A_WITH_RING_ABOVE u"rb"
                UTF16_LATIN_SMALL_O_WITH_STROKE u"ker");
    }

    void test_toUtf16_fromUtf16_wstring()
    {
        Y_EQUAL(Utf16::toUtf16(u"\u00C5rb\u00F8ker", Encoding::UTF_16_LE),
                UTF16_LATIN_CAPITAL_A_WITH_RING_ABOVE u"rb"
                UTF16_LATIN_SMALL_O_WITH_STROKE u"ker");
    }

    void test_toUtf16_fromWindows1252()
    {
        Y_EQUAL(Utf16::toUtf16("\xC5rb\xF8ker", Encoding::WINDOWS_1252),
                UTF16_LATIN_CAPITAL_A_WITH_RING_ABOVE u"rb"
                UTF16_LATIN_SMALL_O_WITH_STROKE u"ker");
        Y_EQUAL(Utf16::toUtf16("\x94", Encoding::WINDOWS_1252), u"\u201D");
    }

    void test_trim()
    {
        Y_EQUAL(Utf16::trim(u" \n\t foo bar \f\r" UTF16_PARAGRAPH_SEPARATOR),
                u"foo bar");
        Y_EQUAL(Utf16::trim(u":--." UTF16_GREEK_SMALL_SIGMA u"foo bar:--",
                             Unicode::isPunctuation),
                UTF16_GREEK_SMALL_SIGMA u"foo bar");
        Y_EQUAL(Utf16::trim(
                u"A.BC_DFB.-GA-B",
                [](char32_t c){return Utf16::contains(u"AB.-", c);}),
                u"C_DFB.-G");
    }

    void test_trimEnd()
    {
        Y_EQUAL(Utf16::trimEnd(
                u" \n\t foo bar \f\r" UTF16_PARAGRAPH_SEPARATOR),
                u" \n\t foo bar");
        Y_EQUAL(Utf16::trimEnd(u":--." UTF16_GREEK_SMALL_SIGMA u"foo bar:--",
                               Unicode::isPunctuation),
                u":--." UTF16_GREEK_SMALL_SIGMA u"foo bar");
    }

    void test_trimStart()
    {
        Y_EQUAL(Utf16::trimStart(
                u" \n\t" UTF16_PARAGRAPH_SEPARATOR u" foo bar \f "),
                u"foo bar \f ");
        Y_EQUAL(Utf16::trimStart(
                u":--." UTF16_GREEK_SMALL_SIGMA u"foo bar:--",
                Unicode::isPunctuation),
                UTF16_GREEK_SMALL_SIGMA u"foo bar:--");
    }

    void test_unescape_BACKSLASH()
    {
        Y_EQUAL(Utf16::unescape(u"\\u00C6\\n\\t\\\\\\x41"),
                UTF16_LATIN_CAPITAL_AE u"\n\t\\A");
        Y_EQUAL(Utf16::unescape(u"\\1A"), u"\x01" u"A");
        Y_EQUAL(Utf16::unescape(u"\\01A"), u"\x01" u"A");
        Y_EQUAL(Utf16::unescape(u"\\1234"), u"\x53" u"4");
    }

    void test_unescape_JSON()
    {
        Y_EQUAL(Utf16::unescape(u"\\u00C6\\n\\t\\\\\\x41", EscapeType::JSON),
                UTF16_LATIN_CAPITAL_AE u"\n\t\\A");
        Y_EQUAL(Utf16::unescape(u"\\1A", EscapeType::JSON), u"1A");
    }

    void test_upper()
    {
        Y_EQUAL(Utf16::upper(u"aBc" UTF16_GREEK_SMALL_SIGMA u"D"),
                u"ABC" UTF16_GREEK_CAPITAL_SIGMA u"D");
    }

    Y_SUBTEST("Utf16",
              test_append,
              test_caseInsensitiveCompare,
              test_caseInsensitiveEqual,
              test_caseInsensitiveLess,
              test_contains,
              test_countCharacters,
              test_countCodePoints,
              test_endsWith,
              test_escape_BACKSLASH,
              test_escape_BACKSLASH_ASCII,
              test_escape_BACKSLASH_ASCII_SMART,
              test_escape_JSON,
              test_escape_JSON_ASCII,
              test_escape_XML_ATTRIBUTE,
              test_escape_XML_TEXT,
              test_findLast,
              test_findLastNewline,
              test_findFirst,
              test_findFirstNewline,
              test_insert,
              test_insertChar,
              test_isAlphaNumeric,
              test_isValidUtf16,
              test_join,
              test_lower,
              test_nextCharacter_const,
              test_nextCharacter_mutable,
              test_nthCharacter,
              test_prevCharacter_const,
              test_prevCharacter_mutable,
              test_replace_indexes,
              test_replace_string,
              test_replace_string_backwards,
              test_replaceCodePoint,
              test_replaceInvalidUtf16,
              test_replaceInvalidUtf16InPlace,
              test_reverse,
              test_split_caseInsensitive_NonASCII,
              test_split_caseInsensitive_NoTail,
              test_split_caseInsensitive_reverse,
              test_split_caseInsensitive_Tail,
              test_split_caseSensitive_Tail,
              test_split_caseSensitive_NoTail,
              test_split_whitespace,
              test_split_whitespace_backwards,
              test_splitIf,
              test_splitIf_flags,
              test_splitLines,
              test_startsWith,
              test_substring,
              test_title,
              test_toUtf16_fromLatin1,
              test_toUtf16_fromUtf8,
              test_toUtf16_fromUtf16_wstring,
              test_toUtf16_fromWindows1252,
              test_trim,
              test_trimEnd,
              test_trimStart,
              test_unescape_BACKSLASH,
              test_unescape_JSON,
              test_upper);
}
