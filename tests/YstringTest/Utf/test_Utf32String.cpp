//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-09-17.
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#include "Ystring/Utf32.hpp"

#include "Ystring/Unicode/UnicodePredicates.hpp"
#include "Ystring/Utf/Utf8Chars.hpp"
#include "Ystring/Utf/Utf32Chars.hpp"
#include "Ytest/Ytest.hpp"

namespace
{
    using namespace Ystring;

    void test_append()
    {
        std::u32string s;
        Y_EQUAL(Utf32::append(s, Unicode::GREEK_SMALL_FINAL_SIGMA),
                UTF32_GREEK_SMALL_FINAL_SIGMA);
        Y_EQUAL(Utf32::append(s, Unicode::PUNCTUATION_SPACE),
                UTF32_GREEK_SMALL_FINAL_SIGMA UTF32_PUNCTUATION_SPACE);
    }

    void test_caseInsensitiveCompare()
    {
        Y_LESS(Utf32::caseInsensitiveCompare(
                U"aBc" UTF32_GREEK_SMALL_SIGMA,
                U"AbC" UTF32_GREEK_CAPITAL_SIGMA U"d"), 0);
        Y_LESS(Utf32::caseInsensitiveCompare(
                U"aBc" UTF32_GREEK_SMALL_SIGMA U"d",
                U"AbC" UTF32_GREEK_CAPITAL_TAU), 0);
        Y_EQUAL(Utf32::caseInsensitiveCompare(
                U"aBc" UTF32_GREEK_SMALL_SIGMA,
                U"AbC" UTF32_GREEK_CAPITAL_SIGMA), 0);
        Y_GREATER(Utf32::caseInsensitiveCompare(
                U"aBc" UTF32_GREEK_SMALL_SIGMA U"a",
                U"AbC" UTF32_GREEK_CAPITAL_SIGMA), 0);
        Y_GREATER(Utf32::caseInsensitiveCompare(
                U"aBc" UTF32_GREEK_SMALL_PSI U"d",
                U"AbC" UTF32_GREEK_CAPITAL_TAU), 0);
    }

    void test_caseInsensitiveEqual()
    {
        Y_ASSERT(Utf32::caseInsensitiveEqual(
                U"aBc" UTF32_GREEK_SMALL_SIGMA,
                U"AbC" UTF32_GREEK_CAPITAL_SIGMA));
        Y_ASSERT(!Utf32::caseInsensitiveEqual(
                U"aBc&8q" UTF32_GREEK_SMALL_SIGMA,
                U"AbC&8p" UTF32_GREEK_CAPITAL_SIGMA));
    }

    void test_caseInsensitiveLess()
    {
        Y_ASSERT(!Utf32::caseInsensitiveLess(
                U"aBc" UTF32_GREEK_SMALL_SIGMA U"D",
                U"AbC" UTF32_GREEK_CAPITAL_SIGMA U"d"));
        Y_ASSERT(Utf32::caseInsensitiveLess(
                U"aBc" UTF32_GREEK_SMALL_SIGMA U"d",
                U"AbC" UTF32_GREEK_CAPITAL_TAU));
    }

    void test_contains()
    {
        Y_ASSERT(Utf32::contains(U"ABCDE", 'D'));
        Y_ASSERT(!Utf32::contains(U"ABCDE", 'F'));
    }

    void test_countCharacters()
    {
        Y_EQUAL(Utf32::countCharacters(
                U"A" UTF32_COMBINING_RING_ABOVE U"BCDE" UTF32_COMBINING_TILDE),
                5);
    }

    void test_countCodePoints()
    {
        Y_EQUAL(Utf32::countCodePoints(
                U"A" UTF32_COMBINING_RING_ABOVE U"BCDE" UTF32_COMBINING_TILDE),
                7);
    }

    void test_endsWith()
    {
        Y_ASSERT(Utf32::endsWith(U"aBc" UTF32_GREEK_SMALL_SIGMA U"D",
                                 U"C" UTF32_GREEK_CAPITAL_SIGMA U"d",
                                 FindFlags::CASE_INSENSITIVE));
        Y_ASSERT(!Utf32::endsWith(U"aBc" UTF32_GREEK_SMALL_SIGMA U"D",
                                  U"E" UTF32_GREEK_CAPITAL_SIGMA U"d",
                                  FindFlags::CASE_INSENSITIVE));
        Y_ASSERT(Utf32::endsWith(U"aBc" UTF32_GREEK_SMALL_SIGMA U"D",
                                 U"c" UTF32_GREEK_SMALL_SIGMA U"D"));
    }

    void test_escape_BACKSLASH()
    {
        const char32_t str[] = U"ab\x01" U"cd\nef\x7Fgh\x80";
        auto expected = U"ab\\U00000001cd\\nef\\U0000007Fgh\\U00000080";
        Y_EQUAL(Utf32::escape(str), expected);
        Y_EQUAL(Utf32::escape(U"\uFFFF"), U"\uFFFF");
    }

    void test_escape_BACKSLASH_ASCII()
    {
        auto expected = U"\\U0000FFFF";
        Y_EQUAL(Utf32::escape(U"\uFFFF", EscapeType::BACKSLASH_ASCII),
                 expected);
    }

    void test_escape_BACKSLASH_ASCII_SMART()
    {
        Y_EQUAL(Utf32::escape(U"\n\tABCD", EscapeType::BACKSLASH_ASCII_SMART),
                U"\\n\\tABCD");
        Y_EQUAL(Utf32::escape(U"\u001F", EscapeType::BACKSLASH_ASCII_SMART),
                U"\\x1F");
        Y_EQUAL(Utf32::escape(U"\u00FF", EscapeType::BACKSLASH_ASCII_SMART),
                U"\\xFF");
        Y_EQUAL(Utf32::escape(U"\u0100", EscapeType::BACKSLASH_ASCII_SMART),
                U"\\u0100");
        Y_EQUAL(Utf32::escape(U"\uFFFF", EscapeType::BACKSLASH_ASCII_SMART),
                U"\\uFFFF");
        Y_EQUAL(Utf32::escape(U"\U00010000", EscapeType::BACKSLASH_ASCII_SMART),
                U"\\U00010000");
        Y_EQUAL(Utf32::escape(U"\U000FFFFF", EscapeType::BACKSLASH_ASCII_SMART),
                U"\\U000FFFFF");
    }

    void test_escape_JSON()
    {
        Y_EQUAL(Utf32::escape(U"\n\tABCD", EscapeType::JSON), U"\\n\\tABCD");
        Y_EQUAL(Utf32::escape(U"\x7f", EscapeType::JSON), U"\\u007F");
        Y_EQUAL(Utf32::escape(U"\x80", EscapeType::JSON), U"\\u0080");
    }

    void test_escape_JSON_ASCII()
    {
        Y_EQUAL(Utf32::escape(U"\n\t\"ABCD", EscapeType::JSON_ASCII),
                U"\\n\\t\\\"ABCD");
        Y_EQUAL(Utf32::escape(U"\x7f", EscapeType::JSON_ASCII),
                U"\\u007F");
        Y_EQUAL(Utf32::escape(U"\x80", EscapeType::JSON_ASCII),
                U"\\u0080");
        Y_EQUAL(Utf32::escape(U"\u0100", EscapeType::JSON_ASCII),
                U"\\u0100");
        Y_EQUAL(Utf32::escape(U"\uFFFF", EscapeType::JSON_ASCII),
                U"\\uFFFF");
    }

    void test_escape_XML_ATTRIBUTE()
    {
        Y_EQUAL(Utf32::escape(U"\n\tA&\"'<B>", EscapeType::XML_ATTRIBUTE),
                U"&#xA;&#x9;A&amp;&quot;&apos;&lt;B&gt;");
    }

    void test_escape_XML_TEXT()
    {
        Y_EQUAL(Utf32::escape(U"\n\tA&\"'<B>", EscapeType::XML_TEXT),
                U"\n\tA&amp;\"\'&lt;B&gt;");
    }

    void test_findLast()
    {
        auto s = std::u32string(U"abc_gh" UTF32_GREEK_CAPITAL_SIGMA  U"IJ_gH"
                             UTF32_GREEK_SMALL_SIGMA U"Ij_kLM_nop");
        auto r = Utf32::findLast(s, U"gh" UTF32_GREEK_CAPITAL_SIGMA U"ij",
                                FindFlags::CASE_INSENSITIVE);
        Y_EQUAL(std::u32string(r.first, r.second),
                 U"gH" UTF32_GREEK_SMALL_SIGMA U"Ij");
        auto t = Utf32::findLast(r.first, r.second,
                                 UTF32_GREEK_CAPITAL_SIGMA U"i",
                                 FindFlags::CASE_INSENSITIVE);
        Y_EQUAL(std::u32string(t.first, t.second),
                UTF32_GREEK_SMALL_SIGMA U"I");
        auto u = Utf32::findLast(r.first, r.second,
                                 UTF32_GREEK_CAPITAL_SIGMA U"i");
        Y_ASSERT(u.first == u.second && u.first == r.first);
    }

    void test_findLastNewline()
    {
        auto str = std::u32string(U"abc\ndef\r\nghi");
        auto s = make_pair(begin(str), end(str));
        auto r = Utf32::findLastNewline(str);
        Y_EQUAL(std::u32string(r.second, s.second), U"ghi");
        auto t = make_pair(s.first, r.first);
        r = Utf32::findLastNewline(t.first, t.second);
        Y_EQUAL(std::u32string(r.first, r.second), U"\n");
        Y_EQUAL(std::u32string(r.second, t.second), U"def");
        t.second = r.first;
        r = Utf32::findLastNewline(t.first, t.second);
        Y_ASSERT(r.first == r.second);
        Y_ASSERT(r.first == t.first);
        Y_EQUAL(std::u32string(r.first, t.second), U"abc");
    }

    void test_findFirst()
    {
        auto s = std::u32string(U"abc_ghIJ_gH" UTF32_GREEK_SMALL_SIGMA
                              U"Ij_kLM_nop");
        auto r = Utf32::findFirst(s, U"gh" UTF32_GREEK_CAPITAL_SIGMA U"ij",
                                   FindFlags::CASE_INSENSITIVE);
        Y_EQUAL(std::u32string(r.first, r.second),
                 U"gH" UTF32_GREEK_SMALL_SIGMA U"Ij");
        auto t = Utf32::findFirst(r.first, r.second,
                                  UTF32_GREEK_CAPITAL_SIGMA U"i",
                                  FindFlags::CASE_INSENSITIVE);
        Y_EQUAL(std::u32string(t.first, t.second),
                UTF32_GREEK_SMALL_SIGMA U"I");
        auto u = Utf32::findFirst(r.first, r.second,
                                  UTF32_GREEK_CAPITAL_SIGMA U"i");
        Y_ASSERT(u.first == u.second && u.second == r.second);
    }

    void test_findFirstNewline()
    {
        auto str = std::u32string(U"abc\ndef\r\nghi");
        auto s = make_pair(begin(str), end(str));
        auto r = Utf32::findFirstNewline(str);
        Y_EQUAL(std::u32string(s.first, r.first), U"abc");
        auto t = make_pair(r.second, s.second);
        r = Utf32::findFirstNewline(t.first, t.second);
        Y_EQUAL(std::u32string(t.first, r.first), U"def");
        t.first = r.second;
        r = Utf32::findFirstNewline(t.first, t.second);
        Y_ASSERT(r.first == r.second);
        Y_EQUAL(std::u32string(t.first, r.first), U"ghi");
    }

    void test_insert()
    {
        auto str = U"The " UTF32_GREEK_SMALL_OMEGA
                   UTF32_COMBINING_BRIDGE_ABOVE UTF32_COMBINING_TILDE
                   U" and the A" UTF32_COMBINING_INVERTED_BREVE
                   UTF32_COMBINING_DOT_ABOVE U".";
        auto r = Utf32::insert(Utf32::insert(str, 13, U" insanely"),
                               -2, U"great ");
        Y_EQUAL(r, U"The " UTF32_GREEK_SMALL_OMEGA
                UTF32_COMBINING_BRIDGE_ABOVE UTF32_COMBINING_TILDE
                U" and the insanely great A" UTF32_COMBINING_INVERTED_BREVE
                UTF32_COMBINING_DOT_ABOVE U".");
    }

    void test_insertChar()
    {
        auto str = U"The " UTF32_GREEK_SMALL_OMEGA
                   UTF32_COMBINING_BRIDGE_ABOVE UTF32_COMBINING_TILDE
                   U" and the A" UTF32_COMBINING_INVERTED_BREVE
                   UTF32_COMBINING_DOT_ABOVE U".";
        auto r = Utf32::insert(str, 5, Unicode::GREEK_SMALL_FINAL_SIGMA);
        Y_EQUAL(r, U"The " UTF32_GREEK_SMALL_OMEGA
                    UTF32_COMBINING_BRIDGE_ABOVE UTF32_COMBINING_TILDE
                    UTF32_GREEK_SMALL_FINAL_SIGMA
                    U" and the A" UTF32_COMBINING_INVERTED_BREVE
                    UTF32_COMBINING_DOT_ABOVE U".");
    }

    void test_isAlphaNumeric()
    {
        Y_ASSERT(Utf32::isAlphaNumeric(U"Ab1"));
        Y_ASSERT(!Utf32::isAlphaNumeric(U"Ab-1"));
        Y_ASSERT(!Utf32::isAlphaNumeric(U""));
        std::u32string s(U"2v" UTF32_GREEK_SMALL_OMEGA
                               UTF32_COMBINING_BRIDGE_ABOVE);
        Y_ASSERT(Utf32::isAlphaNumeric(begin(s), end(s)));
    }

    //void test_isValidUtf16()
    //{
    //    Y_ASSERT(Utf32::isValidUtf16(U"AB\xC1\x80"));
    //    Y_ASSERT(!Utf32::isValidUtf16(U"AB\xC0\x7F"));
    //    Y_ASSERT(!Utf32::isValidUtf16(U"\xC0\xFF"));
    //    Y_ASSERT(Utf32::isValidUtf16(U"\xE2\xBF\x80"));
    //    Y_ASSERT(!Utf32::isValidUtf16(U"\xE2\xBF\xC0"));
    //}

    void test_join()
    {
        std::u32string rawStrings[] = {U"foo", U"faa", U"fii", U"fee",
                                       U"fuU"};
        auto result1 = Utf32::join(rawStrings, 5);
        Y_EQUAL(result1, U"foofaafiifeefuU");
        auto result2 = Utf32::join(rawStrings, 5, U":-:");
        Y_EQUAL(result2, U"foo:-:faa:-:fii:-:fee:-:fuU");
        std::vector<std::u32string> strings(std::begin(rawStrings),
                                          std::end(rawStrings));
        result1 = Utf32::join(strings);
        Y_EQUAL(result1, U"foofaafiifeefuU");
        result2 = Utf32::join(strings, U":-:");
        Y_EQUAL(result2, U"foo:-:faa:-:fii:-:fee:-:fuU");
    }

    void test_lower()
    {
        Y_EQUAL(Utf32::lower(U"aBc" UTF32_GREEK_CAPITAL_SIGMA U"d12$E"),
                U"abc" UTF32_GREEK_SMALL_SIGMA U"d12$e");
    }

    void test_nextCharacter_const()
    {
        const std::u32string str(U"AB" UTF32_GREEK_SMALL_OMEGA
                              UTF32_COMBINING_BRIDGE_ABOVE
                              UTF32_COMBINING_TILDE U"C");
        auto b = str.begin(), e = str.end();
        Y_EQUAL(distance(str.begin(), Utf32::nextCharacter(b, e)), 1);
        Y_EQUAL(distance(str.begin(), Utf32::nextCharacter(b, e, 0)), 0);
        Y_EQUAL(distance(str.begin(), Utf32::nextCharacter(b, e, 1)), 1);
        Y_EQUAL(distance(str.begin(), Utf32::nextCharacter(b, e, 2)), 2);
        Y_EQUAL(distance(str.begin(), Utf32::nextCharacter(b, e, 3)), 5);
        Y_EQUAL(distance(str.begin(), Utf32::nextCharacter(b, e, 4)), 6);
        Y_THROWS(Utf32::nextCharacter(b, e, 5), YstringException);
    }

    void test_nextCharacter_mutable()
    {
        std::u32string str(U"AB" UTF32_GREEK_SMALL_OMEGA
                                 UTF32_COMBINING_BRIDGE_ABOVE
                                 UTF32_COMBINING_TILDE U"C");
        auto b = str.begin(), e = str.end();
        Y_EQUAL(distance(str.begin(), Utf32::nextCharacter(b, e)), 1);
        Y_EQUAL(distance(str.begin(), Utf32::nextCharacter(b, e, 0)), 0);
        Y_EQUAL(distance(str.begin(), Utf32::nextCharacter(b, e, 1)), 1);
        Y_EQUAL(distance(str.begin(), Utf32::nextCharacter(b, e, 2)), 2);
        Y_EQUAL(distance(str.begin(), Utf32::nextCharacter(b, e, 3)), 5);
        Y_EQUAL(distance(str.begin(), Utf32::nextCharacter(b, e, 4)), 6);
        Y_THROWS(Utf32::nextCharacter(b, e, 5), YstringException);
    }

    void test_nthCharacter()
    {
        std::u32string str(U"AB" UTF32_GREEK_SMALL_OMEGA
                                 UTF32_COMBINING_BRIDGE_ABOVE
                                 UTF32_COMBINING_TILDE U"C");
        Y_EQUAL(distance(str.begin(), Utf32::nthCharacter(str, 0)), 0);
        Y_EQUAL(distance(str.begin(), Utf32::nthCharacter(str, 1)), 1);
        Y_EQUAL(distance(str.begin(), Utf32::nthCharacter(str, 2)), 2);
        Y_EQUAL(distance(str.begin(), Utf32::nthCharacter(str, 3)), 5);
        Y_EQUAL(distance(str.begin(), Utf32::nthCharacter(str, 4)), 6);
        Y_EQUAL(distance(str.begin(), Utf32::nthCharacter(str, -1)), 5);
        Y_EQUAL(distance(str.begin(), Utf32::nthCharacter(str, -2)), 2);
        Y_EQUAL(distance(str.begin(), Utf32::nthCharacter(str, -3)), 1);
        Y_EQUAL(distance(str.begin(), Utf32::nthCharacter(str, -4)), 0);
        Y_THROWS(Utf32::nthCharacter(str, 5), YstringException);
        Y_THROWS(Utf32::nthCharacter(str, -5), YstringException);
    }

    void test_prevCharacter_const()
    {
        const std::u32string str(U"AB" UTF32_GREEK_SMALL_OMEGA
                              UTF32_COMBINING_BRIDGE_ABOVE
                              UTF32_COMBINING_TILDE U"C");
        auto b = str.begin(), e = str.end();
        Y_EQUAL(distance(str.begin(), Utf32::prevCharacter(b, e)), 5);
        Y_EQUAL(distance(str.begin(), Utf32::prevCharacter(b, e, 0)), 6);
        Y_EQUAL(distance(str.begin(), Utf32::prevCharacter(b, e, 1)), 5);
        Y_EQUAL(distance(str.begin(), Utf32::prevCharacter(b, e, 2)), 2);
        Y_EQUAL(distance(str.begin(), Utf32::prevCharacter(b, e, 3)), 1);
        Y_EQUAL(distance(str.begin(), Utf32::prevCharacter(b, e, 4)), 0);
        Y_THROWS(Utf32::prevCharacter(b, e, 5), YstringException);
    }

    void test_prevCharacter_mutable()
    {
        std::u32string str(U"AB" UTF32_GREEK_SMALL_OMEGA
                                   UTF32_COMBINING_BRIDGE_ABOVE
                                   UTF32_COMBINING_TILDE U"C");
        auto b = str.begin(), e = str.end();
        Y_EQUAL(distance(str.begin(), Utf32::prevCharacter(b, e)), 5);
        Y_EQUAL(distance(str.begin(), Utf32::prevCharacter(b, e, 0)), 6);
        Y_EQUAL(distance(str.begin(), Utf32::prevCharacter(b, e, 1)), 5);
        Y_EQUAL(distance(str.begin(), Utf32::prevCharacter(b, e, 2)), 2);
        Y_EQUAL(distance(str.begin(), Utf32::prevCharacter(b, e, 3)), 1);
        Y_EQUAL(distance(str.begin(), Utf32::prevCharacter(b, e, 4)), 0);
        Y_THROWS(Utf32::prevCharacter(b, e, 5), YstringException);
    }

    void test_replace_indexes()
    {
        auto s = U"The " UTF32_GREEK_SMALL_OMEGA
                 UTF32_COMBINING_BRIDGE_ABOVE UTF32_COMBINING_TILDE
                 U" and the A" UTF32_COMBINING_INVERTED_BREVE
                 UTF32_COMBINING_DOT_ABOVE U".";
        Y_EQUAL(Utf32::replace(s, 6, -3, U"beats no"),
                 U"The " UTF32_GREEK_SMALL_OMEGA
                 UTF32_COMBINING_BRIDGE_ABOVE UTF32_COMBINING_TILDE
                 U" beats no A" UTF32_COMBINING_INVERTED_BREVE
                 UTF32_COMBINING_DOT_ABOVE U".");
    }

    void test_replace_string()
    {
        auto s = U"The " UTF32_GREEK_SMALL_OMEGA U" and the A.";
        Y_EQUAL(Utf32::replace(s,
                               UTF32_GREEK_SMALL_OMEGA U" and",
                               UTF32_GREEK_CAPITAL_OMEGA U" or"),
                 U"The " UTF32_GREEK_CAPITAL_OMEGA U" or the A.");
        Y_EQUAL(Utf32::replace(s,
                               UTF32_GREEK_CAPITAL_OMEGA U" aNd",
                               UTF32_GREEK_CAPITAL_SIGMA U" or"),
                 s);
        Y_EQUAL(Utf32::replace(s,
                               UTF32_GREEK_CAPITAL_OMEGA U" aNd",
                               UTF32_GREEK_CAPITAL_SIGMA U" or",
                               0, FindFlags::CASE_INSENSITIVE),
                U"The " UTF32_GREEK_CAPITAL_SIGMA U" or the A.");
        Y_EQUAL(Utf32::replace(s, UTF32_GREEK_SMALL_OMEGA U" and", U""),
                U"The  the A.");
        Y_EQUAL(Utf32::replace(s, U"", U"foo"), s);
    }

    void test_replace_string_backwards()
    {
        Y_EQUAL(Utf32::replace(U"123 foo 456 foo 789 foo 012",
                               U"foo", U"bar", -2),
                U"123 foo 456 bar 789 bar 012");
    }

    void test_replaceCodePoint()
    {
        Y_EQUAL(Utf32::replaceCodePoint(U"AB" UTF32_GREEK_SMALL_GAMMA U"D",
                                        Unicode::GREEK_SMALL_GAMMA,
                                        Unicode::FIGURE_SPACE),
                U"AB" UTF32_FIGURE_SPACE U"D");
        Y_EQUAL(Utf32::replaceCodePoint(U"ABCDCDECDEFGCD", 'C', '_', 3),
                U"AB_D_DE_DEFGCD");
        Y_EQUAL(Utf32::replaceCodePoint(U"ABCDCDECDEFGCD", 'C', '_', -3),
                U"ABCD_DE_DEFG_D");
    }

    void test_replaceInvalidUtf16()
    {
        // TODO: Implement unit test for replaceInvalidUtf16.
        //auto s = U"A\uD800M\uD800\uDC00Q\uDC00X";
        //Y_EQUAL(Utf32::replaceInvalidUtf16(s), U"A?M\uD800\uDC00Q?X");
    }

    void test_replaceInvalidUtf16InPlace()
    {
        // TODO: Implement unit test for replaceInvalidUtf16InPlace.
        //auto s = U"A\uD800M\uD800\uDC00Q\uDC00X";
        //Y_EQUAL(Utf32::replaceInvalidUtf16InPlace(s), U"A?M\uD800\uDC00Q?X");
    }

    void test_reverse()
    {
        auto s = U"The " UTF32_GREEK_SMALL_OMEGA UTF32_COMBINING_BRIDGE_ABOVE
                 UTF32_COMBINING_TILDE U" and the A"
                 UTF32_COMBINING_INVERTED_BREVE UTF32_COMBINING_DOT_ABOVE U".";
        std::u32string result;
        Y_EQUAL(Utf32::reverse(s),
                U".A" UTF32_COMBINING_INVERTED_BREVE UTF32_COMBINING_DOT_ABOVE
                U" eht dna " UTF32_GREEK_SMALL_OMEGA
                UTF32_COMBINING_BRIDGE_ABOVE UTF32_COMBINING_TILDE U" ehT");
    }

    void test_split_caseInsensitive_NonASCII()
    {
        auto parts = Utf32::split(
                U":" UTF32_GREEK_CAPITAL_OMEGA U"Q:foo:"
                UTF32_GREEK_CAPITAL_OMEGA U"q:faa:"
                UTF32_GREEK_SMALL_OMEGA U"Q:bor:"
                UTF32_GREEK_SMALL_OMEGA U"q:",
                U":" UTF32_GREEK_SMALL_OMEGA U"q:",
                3,
                SplitFlags::CASE_INSENSITIVE);
        Y_EQUAL(parts.size(), 4);
        Y_EQUAL(parts[0], U"");
        Y_EQUAL(parts[1], U"foo");
        Y_EQUAL(parts[2], U"faa");
        Y_EQUAL(parts[3], U"bor:" UTF32_GREEK_SMALL_OMEGA U"q:");
    }

    void test_split_caseInsensitive_NoTail()
    {
        auto parts = Utf32::split(U"123:aB:321:AB:234:ab:", U":ab:", 0,
                                   SplitFlags::CASE_INSENSITIVE);
        Y_EQUAL(parts.size(), 4);
        Y_EQUAL(parts[0], U"123");
        Y_EQUAL(parts[1], U"321");
        Y_EQUAL(parts[2], U"234");
        Y_EQUAL(parts[3], U"");
    }

    void test_split_caseInsensitive_reverse()
    {
        auto parts = Utf32::split(U"1234ab4567AB8901aB2345", U"AB", -2,
                                  SplitFlags::CASE_INSENSITIVE |
                                  SplitFlags::IGNORE_REMAINDER);
        Y_EQUAL(parts.size(), 2);
        Y_EQUAL(parts[0], U"2345");
        Y_EQUAL(parts[1], U"8901");
    }

    void test_split_caseInsensitive_Tail()
    {
        auto parts = Utf32::split(U"123:aB:321:AB:234:Ab:432", U":ab:", 0,
                                  SplitFlags::CASE_INSENSITIVE);
        Y_EQUAL(parts.size(), 4);
        Y_EQUAL(parts[0], U"123");
        Y_EQUAL(parts[1], U"321");
        Y_EQUAL(parts[2], U"234");
        Y_EQUAL(parts[3], U"432");
    }

    void test_split_caseSensitive_Tail()
    {
        auto parts = Utf32::split(U"123:aB:321:AB:234:AB:432", U":AB:");
        Y_EQUAL(parts.size(), 3);
        Y_EQUAL(parts[0], U"123:aB:321");
        Y_EQUAL(parts[1], U"234");
        Y_EQUAL(parts[2], U"432");
    }

    void test_split_caseSensitive_NoTail()
    {
        auto parts = Utf32::split(U"123:aB:321:AB:234:AB:", U":AB:");
        Y_EQUAL(parts.size(), 3);
        Y_EQUAL(parts[0], U"123:aB:321");
        Y_EQUAL(parts[1], U"234");
        Y_EQUAL(parts[2], U"");
    }

    void test_split_whitespace()
    {
        auto parts = Utf32::split(U" foo faa\r\n\tfee bar "
                                          UTF32_EM_SPACE U"\tbor ");
        Y_EQUAL(parts.size(), 5);
        Y_EQUAL(parts[0], U"foo");
        Y_EQUAL(parts[1], U"faa");
        Y_EQUAL(parts[2], U"fee");
        Y_EQUAL(parts[3], U"bar");
        Y_EQUAL(parts[4], U"bor");
    }

    void test_split_whitespace_backwards()
    {
        auto parts = Utf32::split(U"haa baa ett yui ert swr", -2);
        Y_EQUAL(parts.size(), 3);
        Y_EQUAL(parts[0], U"swr");
        Y_EQUAL(parts[1], U"ert");
        Y_EQUAL(parts[2], U"haa baa ett yui");
    }

    void test_splitIf()
    {
        auto parts = Utf32::splitIf(
                U" foo faa\r\n\tfee bar " UTF32_EM_SPACE U"\tbor ",
                Unicode::isWhitespace, 0, SplitFlags::IGNORE_EMPTY);
        Y_EQUAL(parts.size(), 5);
        Y_EQUAL(parts[0], U"foo");
        Y_EQUAL(parts[1], U"faa");
        Y_EQUAL(parts[2], U"fee");
        Y_EQUAL(parts[3], U"bar");
        Y_EQUAL(parts[4], U"bor");
    }

    void do_test_splitIf(const std::u32string& s,
                         SplitFlags_t flags, ptrdiff_t count,
                         const std::u32string& expected)
    {
        auto parts = Utf32::splitIf(s, [](char32_t c){return c == ':';},
                                   count, flags);
        Y_EQUAL(parts.size(), expected.size());
        for (auto i = 0u; i < parts.size(); ++i)
        {
            auto expect = expected[i] == ' ' ? std::u32string()
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
        Y_CALL(do_test_splitIf(U"", D, 0, U" "));
        Y_CALL(do_test_splitIf(U"", IF, 0, U""));
        Y_CALL(do_test_splitIf(U"", II + IB, 0, U" "));
        Y_CALL(do_test_splitIf(U":", D, 0, U"  "));
        Y_CALL(do_test_splitIf(U":", IF, 0, U" "));
        Y_CALL(do_test_splitIf(U":", IB, 0, U" "));
        Y_CALL(do_test_splitIf(U":", IF + IB, 0, U""));
        Y_CALL(do_test_splitIf(U":", IF + II + IB, 0, U""));
        Y_CALL(do_test_splitIf(U":", IR, 1, U" "));
        Y_CALL(do_test_splitIf(U"a:", IR, 1, U"a"));
        Y_CALL(do_test_splitIf(U"a:a", IR, 1, U"a"));
        Y_CALL(do_test_splitIf(U"::", D, 0, U"   "));
        Y_CALL(do_test_splitIf(U"::", IF + II + IB, 0, U""));
        Y_CALL(do_test_splitIf(U"::", II, 0, U"  "));
        Y_CALL(do_test_splitIf(U":a", IF, 0, U"a"));
        Y_CALL(do_test_splitIf(U"a::b", II, 1, U"ab"));
        Y_CALL(do_test_splitIf(U"a:b::c", IR, -1, U"c"));
        Y_CALL(do_test_splitIf(U"a:b::", IR, -1, U" "));
        Y_CALL(do_test_splitIf(U"a:b::", IE, -1, U"ba"));
    }

    void test_splitLines()
    {
        auto parts = Utf32::splitLines(
                U" foo\nfaa \r\n\tfee bar \vbor\f\rrubb");
        Y_EQUAL(parts.size(), 6);
        Y_EQUAL(parts[0], U" foo");
        Y_EQUAL(parts[1], U"faa ");
        Y_EQUAL(parts[2], U"\tfee bar ");
        Y_EQUAL(parts[3], U"bor");
        Y_EQUAL(parts[4], U"");
        Y_EQUAL(parts[5], U"rubb");
    }

    void test_startsWith()
    {
        Y_ASSERT(Utf32::startsWith(U"qF" UTF32_GREEK_SMALL_SIGMA U"aBcD",
                                   U"qF" UTF32_GREEK_CAPITAL_SIGMA,
                                   FindFlags::CASE_INSENSITIVE));
        Y_ASSERT(!Utf32::startsWith(U"qF" UTF32_GREEK_SMALL_SIGMA U"aBcD",
                                    U"qF" UTF32_GREEK_CAPITAL_SIGMA));
        Y_ASSERT(!Utf32::startsWith(U"qF" UTF32_GREEK_SMALL_SIGMA U"aBcD",
                                    U"qF" UTF32_GREEK_CAPITAL_SIGMA U"g",
                                    FindFlags::CASE_INSENSITIVE));
    }

    void test_substring()
    {
        std::u32string s(U"AB" UTF32_COMBINING_BRIDGE_ABOVE U"CD");
        Y_EQUAL(Utf32::substring(s, 0),
                U"AB" UTF32_COMBINING_BRIDGE_ABOVE U"CD");
        Y_EQUAL(Utf32::substring(s, 0, 4),
                U"AB" UTF32_COMBINING_BRIDGE_ABOVE U"CD");
        Y_EQUAL(Utf32::substring(s, 1, 3),
                U"B" UTF32_COMBINING_BRIDGE_ABOVE U"C");
        Y_EQUAL(Utf32::substring(s, 2, 2), U"");
        Y_EQUAL(Utf32::substring(s, 3, 1), U"");
        Y_EQUAL(Utf32::substring(s, 1, -1),
                U"B" UTF32_COMBINING_BRIDGE_ABOVE U"C");
        Y_EQUAL(Utf32::substring(s, 2, -2), U"");
        Y_EQUAL(Utf32::substring(s, 3, -4), U"");
        Y_EQUAL(Utf32::substring(s, -3),
                U"B" UTF32_COMBINING_BRIDGE_ABOVE U"CD");
        Y_EQUAL(Utf32::substring(s, -3, -1),
                U"B" UTF32_COMBINING_BRIDGE_ABOVE U"C");
        Y_EQUAL(Utf32::substring(s, -2, -2), U"");
        Y_EQUAL(Utf32::substring(s, -1, -3), U"");
    }

    void test_title()
    {
        Y_EQUAL(Utf32::title(U"aBc " UTF32_GREEK_SMALL_SIGMA U"De.fooB"),
                U"Abc " UTF32_GREEK_CAPITAL_SIGMA U"de.Foob");
    }

    void test_toUtf32_fromLatin1()
    {
        Y_EQUAL(Utf32::toUtf32("\xC5rb\xF8ker", Encoding::LATIN_1),
                UTF32_LATIN_CAPITAL_A_WITH_RING_ABOVE U"rb"
                UTF32_LATIN_SMALL_O_WITH_STROKE U"ker");
    }

    void test_toUtf32_fromUtf8()
    {
        Y_EQUAL(Utf32::toUtf32(UTF8_LATIN_CAPITAL_A_WITH_RING_ABOVE "rb"
                               UTF8_LATIN_SMALL_O_WITH_STROKE "ker",
                               Encoding::UTF_8),
                UTF32_LATIN_CAPITAL_A_WITH_RING_ABOVE U"rb"
                UTF32_LATIN_SMALL_O_WITH_STROKE U"ker");
    }

    void test_toUtf32_fromUtf16_wstring()
    {
        Y_EQUAL(Utf32::toUtf32(u"\u00C5rb\u00F8ker", Encoding::UTF_16_LE),
                UTF32_LATIN_CAPITAL_A_WITH_RING_ABOVE U"rb"
                UTF32_LATIN_SMALL_O_WITH_STROKE U"ker");
    }

    void test_toUtf32_fromWindows1252()
    {
        Y_EQUAL(Utf32::toUtf32("\xC5rb\xF8ker", Encoding::WINDOWS_1252),
                UTF32_LATIN_CAPITAL_A_WITH_RING_ABOVE U"rb"
                UTF32_LATIN_SMALL_O_WITH_STROKE U"ker");
        Y_EQUAL(Utf32::toUtf32("\x94", Encoding::WINDOWS_1252), U"\u201D");
    }

    void test_trim()
    {
        Y_EQUAL(Utf32::trim(U" \n\t foo bar \f\r" UTF32_PARAGRAPH_SEPARATOR),
                U"foo bar");
        Y_EQUAL(Utf32::trim(U":--." UTF32_GREEK_SMALL_SIGMA U"foo bar:--",
                             Unicode::isPunctuation),
                UTF32_GREEK_SMALL_SIGMA U"foo bar");
        Y_EQUAL(Utf32::trim(
                U"A.BC_DFB.-GA-B",
                [](char32_t c){return Utf32::contains(U"AB.-", c);}),
                U"C_DFB.-G");
    }

    void test_trimEnd()
    {
        Y_EQUAL(Utf32::trimEnd(
                U" \n\t foo bar \f\r" UTF32_PARAGRAPH_SEPARATOR),
                U" \n\t foo bar");
        Y_EQUAL(Utf32::trimEnd(U":--." UTF32_GREEK_SMALL_SIGMA U"foo bar:--",
                               Unicode::isPunctuation),
                U":--." UTF32_GREEK_SMALL_SIGMA U"foo bar");
    }

    void test_trimStart()
    {
        Y_EQUAL(Utf32::trimStart(
                U" \n\t" UTF32_PARAGRAPH_SEPARATOR U" foo bar \f "),
                U"foo bar \f ");
        Y_EQUAL(Utf32::trimStart(
                U":--." UTF32_GREEK_SMALL_SIGMA U"foo bar:--",
                Unicode::isPunctuation),
                UTF32_GREEK_SMALL_SIGMA U"foo bar:--");
    }

    void test_unescape_BACKSLASH()
    {
        Y_EQUAL(Utf32::unescape(U"\\u00C6\\n\\t\\\\\\x41"),
                UTF32_LATIN_CAPITAL_AE U"\n\t\\A");
        Y_EQUAL(Utf32::unescape(U"\\1A"), U"\x01" U"A");
        Y_EQUAL(Utf32::unescape(U"\\01A"), U"\x01" U"A");
        Y_EQUAL(Utf32::unescape(U"\\1234"), U"\x53" U"4");
    }

    void test_unescape_JSON()
    {
        Y_EQUAL(Utf32::unescape(U"\\u00C6\\n\\t\\\\\\x41", EscapeType::JSON),
                UTF32_LATIN_CAPITAL_AE U"\n\t\\A");
        Y_EQUAL(Utf32::unescape(U"\\1A", EscapeType::JSON), U"1A");
    }

    void test_upper()
    {
        Y_EQUAL(Utf32::upper(U"aBc" UTF32_GREEK_SMALL_SIGMA U"D"),
                U"ABC" UTF32_GREEK_CAPITAL_SIGMA U"D");
    }

    Y_SUBTEST("Utf32",
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
    //          test_isValidUtf16,
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
              test_toUtf32_fromLatin1,
              test_toUtf32_fromUtf8,
              test_toUtf32_fromUtf16_wstring,
              test_toUtf32_fromWindows1252,
              test_trim,
              test_trimEnd,
              test_trimStart,
              test_unescape_BACKSLASH,
              test_unescape_JSON,
              test_upper);
}
