//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-07-30.
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#include "Ystring/Utf16W.hpp"

#include "Ystring/Unicode/UnicodePredicates.hpp"
#include "Ystring/Utf/Utf8Chars.hpp"
#include "Ystring/Utf16/Utf16WChars.hpp"
#include "../Ytest/Ytest.hpp"

namespace
{
    using namespace Ystring;

    void test_append()
    {
        std::wstring s;
        Y_EQUAL(Utf16W::append(s, Unicode::GREEK_SMALL_FINAL_SIGMA),
                 UTF16W_GREEK_SMALL_FINAL_SIGMA);
        Y_EQUAL(Utf16W::append(s, Unicode::PUNCTUATION_SPACE),
                 UTF16W_GREEK_SMALL_FINAL_SIGMA UTF16W_PUNCTUATION_SPACE);
    }

    void test_caseInsensitiveCompare()
    {
        Y_LESS(Utf16W::caseInsensitiveCompare(
                L"aBc" UTF16W_GREEK_SMALL_SIGMA,
                L"AbC" UTF16W_GREEK_CAPITAL_SIGMA L"d"), 0);
        Y_LESS(Utf16W::caseInsensitiveCompare(
                L"aBc" UTF16W_GREEK_SMALL_SIGMA L"d",
                L"AbC" UTF16W_GREEK_CAPITAL_TAU), 0);
        Y_EQUAL(Utf16W::caseInsensitiveCompare(
                L"aBc" UTF16W_GREEK_SMALL_SIGMA,
                L"AbC" UTF16W_GREEK_CAPITAL_SIGMA), 0);
        Y_GREATER(Utf16W::caseInsensitiveCompare(
                L"aBc" UTF16W_GREEK_SMALL_SIGMA L"a",
                L"AbC" UTF16W_GREEK_CAPITAL_SIGMA), 0);
        Y_GREATER(Utf16W::caseInsensitiveCompare(
                L"aBc" UTF16W_GREEK_SMALL_PSI L"d",
                L"AbC" UTF16W_GREEK_CAPITAL_TAU), 0);
    }

    void test_caseInsensitiveEqual()
    {
        Y_ASSERT(Utf16W::caseInsensitiveEqual(
                L"aBc" UTF16W_GREEK_SMALL_SIGMA,
                L"AbC" UTF16W_GREEK_CAPITAL_SIGMA));
        Y_ASSERT(!Utf16W::caseInsensitiveEqual(
                L"aBc&8q" UTF16W_GREEK_SMALL_SIGMA,
                L"AbC&8p" UTF16W_GREEK_CAPITAL_SIGMA));
    }

    void test_caseInsensitiveLess()
    {
        Y_ASSERT(!Utf16W::caseInsensitiveLess(
                L"aBc" UTF16W_GREEK_SMALL_SIGMA L"D",
                L"AbC" UTF16W_GREEK_CAPITAL_SIGMA L"d"));
        Y_ASSERT(Utf16W::caseInsensitiveLess(
                L"aBc" UTF16W_GREEK_SMALL_SIGMA L"d",
                L"AbC" UTF16W_GREEK_CAPITAL_TAU));
    }

    void test_contains()
    {
        Y_ASSERT(Utf16W::contains(L"ABCDE", 'D'));
        Y_ASSERT(!Utf16W::contains(L"ABCDE", 'F'));
    }

    void test_countCharacters()
    {
        Y_EQUAL(Utf16W::countCharacters(
                L"A" UTF16W_COMBINING_RING_ABOVE
                        L"BCDE" UTF16W_COMBINING_TILDE),
                5);
    }

    void test_countCodePoints()
    {
        Y_EQUAL(Utf16W::countCodePoints(
                L"A" UTF16W_COMBINING_RING_ABOVE
                        L"BCDE" UTF16W_COMBINING_TILDE),
                7);
    }

    void test_endsWith()
    {
        Y_ASSERT(Utf16W::endsWith(L"aBc" UTF16W_GREEK_SMALL_SIGMA L"D",
                                  L"C" UTF16W_GREEK_CAPITAL_SIGMA L"d",
                                  FindFlags::CASE_INSENSITIVE));
        Y_ASSERT(!Utf16W::endsWith(L"aBc" UTF16W_GREEK_SMALL_SIGMA L"D",
                                   L"E" UTF16W_GREEK_CAPITAL_SIGMA L"d",
                                   FindFlags::CASE_INSENSITIVE));
        Y_ASSERT(Utf16W::endsWith(L"aBc" UTF16W_GREEK_SMALL_SIGMA L"D",
                                  L"c" UTF16W_GREEK_SMALL_SIGMA L"D"));
    }

    void test_escape_BACKSLASH()
    {
        const wchar_t str[] = L"ab\x01" L"cd\nef\x7Fgh\x80";
    #ifdef YSTRING_WCHAR_IS_2_BYTES
        auto expected = L"ab\\u0001cd\\nef\\u007Fgh\\u0080";
    #else
        auto expected = L"ab\\U00000001cd\\nef\\U0000007Fgh\\U00000080";
    #endif
        Y_EQUAL(Utf16W::escape(str), expected);
        Y_EQUAL(Utf16W::escape(L"\uFFFF"), L"\uFFFF");
    }

    void test_escape_BACKSLASH_ASCII()
    {
    #ifdef YSTRING_WCHAR_IS_2_BYTES
        auto expected = L"\\uFFFF";
    #else
        auto expected = L"\\U0000FFFF";
    #endif
        Y_EQUAL(Utf16W::escape(L"\uFFFF", EscapeType::BACKSLASH_ASCII),
                 expected);
    }

    void test_escape_BACKSLASH_ASCII_SMART()
    {
        Y_EQUAL(Utf16W::escape(L"\n\tABCD",
                               EscapeType::BACKSLASH_ASCII_SMART),
                L"\\n\\tABCD");
        Y_EQUAL(Utf16W::escape(L"\u001F", EscapeType::BACKSLASH_ASCII_SMART),
                L"\\x1F");
        Y_EQUAL(Utf16W::escape(L"\u00FF", EscapeType::BACKSLASH_ASCII_SMART),
                L"\\xFF");
        Y_EQUAL(Utf16W::escape(L"\u0100", EscapeType::BACKSLASH_ASCII_SMART),
                L"\\u0100");
        Y_EQUAL(Utf16W::escape(L"\uFFFF", EscapeType::BACKSLASH_ASCII_SMART),
                L"\\uFFFF");
    #ifdef YSTRING_WCHAR_IS_2_BYTES
        Y_EQUAL(Utf16W::escape(L"\U00010000", EscapeType::BACKSLASH_ASCII_SMART),
                L"\\U00010000");
        Y_EQUAL(Utf16W::escape(L"\U000FFFFF", EscapeType::BACKSLASH_ASCII_SMART),
                L"\\U000FFFFF");
    #endif
    }

    void test_escape_JSON()
    {
        Y_EQUAL(Utf16W::escape(L"\n\tABCD", EscapeType::JSON), L"\\n\\tABCD");
        Y_EQUAL(Utf16W::escape(L"\x7f", EscapeType::JSON), L"\\u007F");
        Y_EQUAL(Utf16W::escape(L"\x80", EscapeType::JSON), L"\\u0080");
    }

    void test_escape_JSON_ASCII()
    {
        Y_EQUAL(Utf16W::escape(L"\n\t\"ABCD", EscapeType::JSON_ASCII),
                L"\\n\\t\\\"ABCD");
        Y_EQUAL(Utf16W::escape(L"\x7f", EscapeType::JSON_ASCII),
                L"\\u007F");
        Y_EQUAL(Utf16W::escape(L"\x80", EscapeType::JSON_ASCII),
                L"\\u0080");
        Y_EQUAL(Utf16W::escape(L"\u0100", EscapeType::JSON_ASCII),
                L"\\u0100");
        Y_EQUAL(Utf16W::escape(L"\uFFFF", EscapeType::JSON_ASCII),
                L"\\uFFFF");
    }

    void test_escape_XML_ATTRIBUTE()
    {
        Y_EQUAL(Utf16W::escape(L"\n\tA&\"'<B>", EscapeType::XML_ATTRIBUTE),
                L"&#xA;&#x9;A&amp;&quot;&apos;&lt;B&gt;");
    }

    void test_escape_XML_TEXT()
    {
        Y_EQUAL(Utf16W::escape(L"\n\tA&\"'<B>", EscapeType::XML_TEXT),
                L"\n\tA&amp;\"\'&lt;B&gt;");
    }

    void test_findLast()
    {
        auto s = std::wstring(L"abc_gh" UTF16W_GREEK_CAPITAL_SIGMA  L"IJ_gH"
                             UTF16W_GREEK_SMALL_SIGMA L"Ij_kLM_nop");
        auto r = Utf16W::findLast(s, L"gh" UTF16W_GREEK_CAPITAL_SIGMA L"ij",
                                FindFlags::CASE_INSENSITIVE);
        Y_EQUAL(std::wstring(r.first, r.second),
                 L"gH" UTF16W_GREEK_SMALL_SIGMA L"Ij");
        auto t = Utf16W::findLast(r.first, r.second,
                                  UTF16W_GREEK_CAPITAL_SIGMA L"i",
                                  FindFlags::CASE_INSENSITIVE);
        Y_EQUAL(std::wstring(t.first, t.second),
                UTF16W_GREEK_SMALL_SIGMA L"I");
        auto u = Utf16W::findLast(r.first, r.second,
                                  UTF16W_GREEK_CAPITAL_SIGMA L"i");
        Y_ASSERT(u.first == u.second && u.first == r.first);
    }

    void test_findLastNewline()
    {
        auto str = std::wstring(L"abc\ndef\r\nghi");
        auto s = make_pair(begin(str), end(str));
        auto r = Utf16W::findLastNewline(str);
        Y_EQUAL(std::wstring(r.second, s.second), L"ghi");
        auto t = make_pair(s.first, r.first);
        r = Utf16W::findLastNewline(t.first, t.second);
        Y_EQUAL(std::wstring(r.first, r.second), L"\n");
        Y_EQUAL(std::wstring(r.second, t.second), L"def");
        t.second = r.first;
        r = Utf16W::findLastNewline(t.first, t.second);
        Y_ASSERT(r.first == r.second);
        Y_ASSERT(r.first == t.first);
        Y_EQUAL(std::wstring(r.first, t.second), L"abc");
    }

    void test_findFirst()
    {
        auto s = std::wstring(L"abc_ghIJ_gH" UTF16W_GREEK_SMALL_SIGMA
                              L"Ij_kLM_nop");
        auto r = Utf16W::findFirst(s, L"gh" UTF16W_GREEK_CAPITAL_SIGMA L"ij",
                                   FindFlags::CASE_INSENSITIVE);
        Y_EQUAL(std::wstring(r.first, r.second),
                 L"gH" UTF16W_GREEK_SMALL_SIGMA L"Ij");
        auto t = Utf16W::findFirst(r.first, r.second,
                                   UTF16W_GREEK_CAPITAL_SIGMA L"i",
                                   FindFlags::CASE_INSENSITIVE);
        Y_EQUAL(std::wstring(t.first, t.second),
                UTF16W_GREEK_SMALL_SIGMA L"I");
        auto u = Utf16W::findFirst(r.first, r.second,
                                   UTF16W_GREEK_CAPITAL_SIGMA L"i");
        Y_ASSERT(u.first == u.second && u.second == r.second);
    }

    void test_findFirstNewline()
    {
        auto str = std::wstring(L"abc\ndef\r\nghi");
        auto s = make_pair(begin(str), end(str));
        auto r = Utf16W::findFirstNewline(str);
        Y_EQUAL(std::wstring(s.first, r.first), L"abc");
        auto t = make_pair(r.second, s.second);
        r = Utf16W::findFirstNewline(t.first, t.second);
        Y_EQUAL(std::wstring(t.first, r.first), L"def");
        t.first = r.second;
        r = Utf16W::findFirstNewline(t.first, t.second);
        Y_ASSERT(r.first == r.second);
        Y_EQUAL(std::wstring(t.first, r.first), L"ghi");
    }

    void test_insert()
    {
        auto str = L"The " UTF16W_GREEK_SMALL_OMEGA
                   UTF16W_COMBINING_BRIDGE_ABOVE UTF16W_COMBINING_TILDE
                   L" and the A" UTF16W_COMBINING_INVERTED_BREVE
                   UTF16W_COMBINING_DOT_ABOVE L".";
        auto r = Utf16W::insert(Utf16W::insert(str, 13, L" insanely"),
                                -2, L"great ");
        Y_EQUAL(r,
                L"The " UTF16W_GREEK_SMALL_OMEGA UTF16W_COMBINING_BRIDGE_ABOVE
                        UTF16W_COMBINING_TILDE L" and the insanely great A"
                        UTF16W_COMBINING_INVERTED_BREVE
                        UTF16W_COMBINING_DOT_ABOVE L".");
    }

    void test_insertChar()
    {
        auto str = L"The " UTF16W_GREEK_SMALL_OMEGA
                   UTF16W_COMBINING_BRIDGE_ABOVE UTF16W_COMBINING_TILDE
                   L" and the A" UTF16W_COMBINING_INVERTED_BREVE
                   UTF16W_COMBINING_DOT_ABOVE L".";
        auto r = Utf16W::insert(str, 5, Unicode::GREEK_SMALL_FINAL_SIGMA);
        Y_EQUAL(r, L"The " UTF16W_GREEK_SMALL_OMEGA
                    UTF16W_COMBINING_BRIDGE_ABOVE UTF16W_COMBINING_TILDE
                    UTF16W_GREEK_SMALL_FINAL_SIGMA
                    L" and the A" UTF16W_COMBINING_INVERTED_BREVE
                    UTF16W_COMBINING_DOT_ABOVE L".");
    }

    void test_isAlphaNumeric()
    {
        Y_ASSERT(Utf16W::isAlphaNumeric(L"Ab1"));
        Y_ASSERT(!Utf16W::isAlphaNumeric(L"Ab-1"));
        Y_ASSERT(!Utf16W::isAlphaNumeric(L""));
        std::wstring s(L"2v" UTF16W_GREEK_SMALL_OMEGA
                               UTF16W_COMBINING_BRIDGE_ABOVE);
        Y_ASSERT(Utf16W::isAlphaNumeric(begin(s), end(s)));
    }

    //void test_isValidUtf16()
    //{
    //    Y_ASSERT(Utf16W::isValidUtf16(L"AB\xC1\x80"));
    //    Y_ASSERT(!Utf16W::isValidUtf16(L"AB\xC0\x7F"));
    //    Y_ASSERT(!Utf16W::isValidUtf16(L"\xC0\xFF"));
    //    Y_ASSERT(Utf16W::isValidUtf16(L"\xE2\xBF\x80"));
    //    Y_ASSERT(!Utf16W::isValidUtf16(L"\xE2\xBF\xC0"));
    //}

    void test_join()
    {
        std::wstring rawStrings[] = {L"foo", L"faa", L"fii", L"fee", L"fuu"};
        auto result1 = Utf16W::join(rawStrings, 5);
        Y_EQUAL(result1, L"foofaafiifeefuu");
        auto result2 = Utf16W::join(rawStrings, 5, L":-:");
        Y_EQUAL(result2, L"foo:-:faa:-:fii:-:fee:-:fuu");
        std::vector<std::wstring> strings(std::begin(rawStrings),
                                          std::end(rawStrings));
        result1 = Utf16W::join(strings);
        Y_EQUAL(result1, L"foofaafiifeefuu");
        result2 = Utf16W::join(strings, L":-:");
        Y_EQUAL(result2, L"foo:-:faa:-:fii:-:fee:-:fuu");
    }

    void test_lower()
    {
        Y_EQUAL(Utf16W::lower(L"aBc" UTF16W_GREEK_CAPITAL_SIGMA L"d12$E"),
                L"abc" UTF16W_GREEK_SMALL_SIGMA L"d12$e");
    }

    void test_nextCharacter_const()
    {
        const std::wstring str(L"AB" UTF16W_GREEK_SMALL_OMEGA
                               UTF16W_COMBINING_BRIDGE_ABOVE
                               UTF16W_COMBINING_TILDE L"C");
        auto b = str.begin(), e = str.end();
        Y_EQUAL(distance(str.begin(), Utf16W::nextCharacter(b, e)), 1);
        Y_EQUAL(distance(str.begin(), Utf16W::nextCharacter(b, e, 0)), 0);
        Y_EQUAL(distance(str.begin(), Utf16W::nextCharacter(b, e, 1)), 1);
        Y_EQUAL(distance(str.begin(), Utf16W::nextCharacter(b, e, 2)), 2);
        Y_EQUAL(distance(str.begin(), Utf16W::nextCharacter(b, e, 3)), 5);
        Y_EQUAL(distance(str.begin(), Utf16W::nextCharacter(b, e, 4)), 6);
        Y_THROWS(Utf16W::nextCharacter(b, e, 5), YstringException);
    }

    void test_nextCharacter_mutable()
    {
        std::wstring str(L"AB" UTF16W_GREEK_SMALL_OMEGA
                                 UTF16W_COMBINING_BRIDGE_ABOVE
                                 UTF16W_COMBINING_TILDE L"C");
        auto b = str.begin(), e = str.end();
        Y_EQUAL(distance(str.begin(), Utf16W::nextCharacter(b, e)), 1);
        Y_EQUAL(distance(str.begin(), Utf16W::nextCharacter(b, e, 0)), 0);
        Y_EQUAL(distance(str.begin(), Utf16W::nextCharacter(b, e, 1)), 1);
        Y_EQUAL(distance(str.begin(), Utf16W::nextCharacter(b, e, 2)), 2);
        Y_EQUAL(distance(str.begin(), Utf16W::nextCharacter(b, e, 3)), 5);
        Y_EQUAL(distance(str.begin(), Utf16W::nextCharacter(b, e, 4)), 6);
        Y_THROWS(Utf16W::nextCharacter(b, e, 5), YstringException);
    }

    void test_nthCharacter()
    {
        std::wstring str(L"AB" UTF16W_GREEK_SMALL_OMEGA
                                 UTF16W_COMBINING_BRIDGE_ABOVE
                                 UTF16W_COMBINING_TILDE L"C");
        Y_EQUAL(distance(str.begin(), Utf16W::nthCharacter(str, 0)), 0);
        Y_EQUAL(distance(str.begin(), Utf16W::nthCharacter(str, 1)), 1);
        Y_EQUAL(distance(str.begin(), Utf16W::nthCharacter(str, 2)), 2);
        Y_EQUAL(distance(str.begin(), Utf16W::nthCharacter(str, 3)), 5);
        Y_EQUAL(distance(str.begin(), Utf16W::nthCharacter(str, 4)), 6);
        Y_EQUAL(distance(str.begin(), Utf16W::nthCharacter(str, -1)), 5);
        Y_EQUAL(distance(str.begin(), Utf16W::nthCharacter(str, -2)), 2);
        Y_EQUAL(distance(str.begin(), Utf16W::nthCharacter(str, -3)), 1);
        Y_EQUAL(distance(str.begin(), Utf16W::nthCharacter(str, -4)), 0);
        Y_THROWS(Utf16W::nthCharacter(str, 5), YstringException);
        Y_THROWS(Utf16W::nthCharacter(str, -5), YstringException);
    }

    void test_prevCharacter_const()
    {
        const std::wstring str(L"AB" UTF16W_GREEK_SMALL_OMEGA
                              UTF16W_COMBINING_BRIDGE_ABOVE
                              UTF16W_COMBINING_TILDE L"C");
        auto b = str.begin(), e = str.end();
        Y_EQUAL(distance(str.begin(), Utf16W::prevCharacter(b, e)), 5);
        Y_EQUAL(distance(str.begin(), Utf16W::prevCharacter(b, e, 0)), 6);
        Y_EQUAL(distance(str.begin(), Utf16W::prevCharacter(b, e, 1)), 5);
        Y_EQUAL(distance(str.begin(), Utf16W::prevCharacter(b, e, 2)), 2);
        Y_EQUAL(distance(str.begin(), Utf16W::prevCharacter(b, e, 3)), 1);
        Y_EQUAL(distance(str.begin(), Utf16W::prevCharacter(b, e, 4)), 0);
        Y_THROWS(Utf16W::prevCharacter(b, e, 5), YstringException);
    }

    void test_prevCharacter_mutable()
    {
        std::wstring str(L"AB" UTF16W_GREEK_SMALL_OMEGA
                                 UTF16W_COMBINING_BRIDGE_ABOVE
                                 UTF16W_COMBINING_TILDE L"C");
        auto b = str.begin(), e = str.end();
        Y_EQUAL(distance(str.begin(), Utf16W::prevCharacter(b, e)), 5);
        Y_EQUAL(distance(str.begin(), Utf16W::prevCharacter(b, e, 0)), 6);
        Y_EQUAL(distance(str.begin(), Utf16W::prevCharacter(b, e, 1)), 5);
        Y_EQUAL(distance(str.begin(), Utf16W::prevCharacter(b, e, 2)), 2);
        Y_EQUAL(distance(str.begin(), Utf16W::prevCharacter(b, e, 3)), 1);
        Y_EQUAL(distance(str.begin(), Utf16W::prevCharacter(b, e, 4)), 0);
        Y_THROWS(Utf16W::prevCharacter(b, e, 5), YstringException);
    }

    void test_replace_indexes()
    {
        auto s = L"The " UTF16W_GREEK_SMALL_OMEGA
                 UTF16W_COMBINING_BRIDGE_ABOVE UTF16W_COMBINING_TILDE
                 L" and the A" UTF16W_COMBINING_INVERTED_BREVE
                 UTF16W_COMBINING_DOT_ABOVE L".";
        Y_EQUAL(Utf16W::replace(s, 6, -3, L"beats no"),
                 L"The " UTF16W_GREEK_SMALL_OMEGA
                 UTF16W_COMBINING_BRIDGE_ABOVE UTF16W_COMBINING_TILDE
                 L" beats no A" UTF16W_COMBINING_INVERTED_BREVE
                 UTF16W_COMBINING_DOT_ABOVE L".");
    }

    void test_replace_string()
    {
        auto s = L"The " UTF16W_GREEK_SMALL_OMEGA L" and the A.";
        Y_EQUAL(Utf16W::replace(s,
                                UTF16W_GREEK_SMALL_OMEGA L" and",
                                UTF16W_GREEK_CAPITAL_OMEGA L" or"),
                 L"The " UTF16W_GREEK_CAPITAL_OMEGA L" or the A.");
        Y_EQUAL(Utf16W::replace(s,
                                UTF16W_GREEK_CAPITAL_OMEGA L" aNd",
                                UTF16W_GREEK_CAPITAL_SIGMA L" or"),
                 s);
        Y_EQUAL(Utf16W::replace(s,
                                UTF16W_GREEK_CAPITAL_OMEGA L" aNd",
                                UTF16W_GREEK_CAPITAL_SIGMA L" or",
                                0, FindFlags::CASE_INSENSITIVE),
                L"The " UTF16W_GREEK_CAPITAL_SIGMA L" or the A.");
        Y_EQUAL(Utf16W::replace(s, UTF16W_GREEK_SMALL_OMEGA L" and", L""),
                L"The  the A.");
        Y_EQUAL(Utf16W::replace(s, L"", L"foo"), s);
    }

    void test_replace_string_backwards()
    {
        Y_EQUAL(Utf16W::replace(L"123 foo 456 foo 789 foo 012",
                                L"foo", L"bar", -2),
                L"123 foo 456 bar 789 bar 012");
    }

    void test_replaceCodePoint()
    {
        Y_EQUAL(Utf16W::replaceCodePoint(L"AB" UTF16W_GREEK_SMALL_GAMMA L"D",
                                         Unicode::GREEK_SMALL_GAMMA,
                                         Unicode::FIGURE_SPACE),
                L"AB" UTF16W_FIGURE_SPACE L"D");
        Y_EQUAL(Utf16W::replaceCodePoint(L"ABCDCDECDEFGCD", 'C', '_', 3),
                L"AB_D_DE_DEFGCD");
        Y_EQUAL(Utf16W::replaceCodePoint(L"ABCDCDECDEFGCD", 'C', '_', -3),
                L"ABCD_DE_DEFG_D");
    }

    void test_replaceInvalidUtf16()
    {
        // TODO: Implement unit test for replaceInvalidUtf16.
        //auto s = L"A\uD800M\uD800\uDC00Q\uDC00X";
        //Y_EQUAL(Utf16W::replaceInvalidUtf16(s), L"A?M\uD800\uDC00Q?X");
    }

    void test_replaceInvalidUtf16InPlace()
    {
        // TODO: Implement unit test for replaceInvalidUtf16InPlace.
        //auto s = L"A\uD800M\uD800\uDC00Q\uDC00X";
        //Y_EQUAL(Utf16W::replaceInvalidUtf16InPlace(s), L"A?M\uD800\uDC00Q?X");
    }

    void test_reverse()
    {
        auto s = L"The " UTF16W_GREEK_SMALL_OMEGA
                UTF16W_COMBINING_BRIDGE_ABOVE UTF16W_COMBINING_TILDE
                L" and the A" UTF16W_COMBINING_INVERTED_BREVE
                UTF16W_COMBINING_DOT_ABOVE L".";
        std::wstring result;
        Y_EQUAL(Utf16W::reverse(s),
                L".A" UTF16W_COMBINING_INVERTED_BREVE
                        UTF16W_COMBINING_DOT_ABOVE L" eht dna "
                        UTF16W_GREEK_SMALL_OMEGA UTF16W_COMBINING_BRIDGE_ABOVE
                        UTF16W_COMBINING_TILDE L" ehT");
    }

    void test_split_caseInsensitive_NonASCII()
    {
        auto parts = Utf16W::split(
                L":" UTF16W_GREEK_CAPITAL_OMEGA L"Q:foo:"
                UTF16W_GREEK_CAPITAL_OMEGA L"q:faa:"
                UTF16W_GREEK_SMALL_OMEGA L"Q:bor:"
                UTF16W_GREEK_SMALL_OMEGA L"q:",
                L":" UTF16W_GREEK_SMALL_OMEGA L"q:",
                3,
                SplitFlags::CASE_INSENSITIVE);
        Y_EQUAL(parts.size(), 4);
        Y_EQUAL(parts[0], L"");
        Y_EQUAL(parts[1], L"foo");
        Y_EQUAL(parts[2], L"faa");
        Y_EQUAL(parts[3], L"bor:" UTF16W_GREEK_SMALL_OMEGA L"q:");
    }

    void test_split_caseInsensitive_NoTail()
    {
        auto parts = Utf16W::split(L"123:aB:321:AB:234:ab:", L":ab:", 0,
                                   SplitFlags::CASE_INSENSITIVE);
        Y_EQUAL(parts.size(), 4);
        Y_EQUAL(parts[0], L"123");
        Y_EQUAL(parts[1], L"321");
        Y_EQUAL(parts[2], L"234");
        Y_EQUAL(parts[3], L"");
    }

    void test_split_caseInsensitive_reverse()
    {
        auto parts = Utf16W::split(L"1234ab4567AB8901aB2345", L"AB", -2,
                                   SplitFlags::CASE_INSENSITIVE |
                                   SplitFlags::IGNORE_REMAINDER);
        Y_EQUAL(parts.size(), 2);
        Y_EQUAL(parts[0], L"2345");
        Y_EQUAL(parts[1], L"8901");
    }

    void test_split_caseInsensitive_Tail()
    {
        auto parts = Utf16W::split(L"123:aB:321:AB:234:Ab:432", L":ab:", 0,
                                 SplitFlags::CASE_INSENSITIVE);
        Y_EQUAL(parts.size(), 4);
        Y_EQUAL(parts[0], L"123");
        Y_EQUAL(parts[1], L"321");
        Y_EQUAL(parts[2], L"234");
        Y_EQUAL(parts[3], L"432");
    }

    void test_split_caseSensitive_Tail()
    {
        auto parts = Utf16W::split(L"123:aB:321:AB:234:AB:432", L":AB:");
        Y_EQUAL(parts.size(), 3);
        Y_EQUAL(parts[0], L"123:aB:321");
        Y_EQUAL(parts[1], L"234");
        Y_EQUAL(parts[2], L"432");
    }

    void test_split_caseSensitive_NoTail()
    {
        auto parts = Utf16W::split(L"123:aB:321:AB:234:AB:", L":AB:");
        Y_EQUAL(parts.size(), 3);
        Y_EQUAL(parts[0], L"123:aB:321");
        Y_EQUAL(parts[1], L"234");
        Y_EQUAL(parts[2], L"");
    }

    void test_split_whitespace()
    {
        auto parts = Utf16W::split(L" foo faa\r\n\tfee bar "
                                           UTF16W_EM_SPACE L"\tbor ");
        Y_EQUAL(parts.size(), 5);
        Y_EQUAL(parts[0], L"foo");
        Y_EQUAL(parts[1], L"faa");
        Y_EQUAL(parts[2], L"fee");
        Y_EQUAL(parts[3], L"bar");
        Y_EQUAL(parts[4], L"bor");
    }

    void test_split_whitespace_backwards()
    {
        auto parts = Utf16W::split(L"haa baa ett yui ert swr", -2);
        Y_EQUAL(parts.size(), 3);
        Y_EQUAL(parts[0], L"swr");
        Y_EQUAL(parts[1], L"ert");
        Y_EQUAL(parts[2], L"haa baa ett yui");
    }

    void test_splitIf()
    {
        auto parts = Utf16W::splitIf(
                L" foo faa\r\n\tfee bar " UTF16W_EM_SPACE L"\tbor ",
                Unicode::isWhitespace, 0, SplitFlags::IGNORE_EMPTY);
        Y_EQUAL(parts.size(), 5);
        Y_EQUAL(parts[0], L"foo");
        Y_EQUAL(parts[1], L"faa");
        Y_EQUAL(parts[2], L"fee");
        Y_EQUAL(parts[3], L"bar");
        Y_EQUAL(parts[4], L"bor");
    }

    void do_test_splitIf(const std::wstring& s,
                         SplitFlags_t flags, ptrdiff_t count,
                         const std::wstring& expected)
    {
        auto parts = Utf16W::splitIf(s, [](char32_t c){return c == ':';},
                                   count, flags);
        Y_EQUAL(parts.size(), expected.size());
        for (auto i = 0u; i < parts.size(); ++i)
        {
            auto expect = expected[i] == ' ' ? std::wstring()
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
        Y_CALL(do_test_splitIf(L"", D, 0, L" "));
        Y_CALL(do_test_splitIf(L"", IF, 0, L""));
        Y_CALL(do_test_splitIf(L"", II + IB, 0, L" "));
        Y_CALL(do_test_splitIf(L":", D, 0, L"  "));
        Y_CALL(do_test_splitIf(L":", IF, 0, L" "));
        Y_CALL(do_test_splitIf(L":", IB, 0, L" "));
        Y_CALL(do_test_splitIf(L":", IF + IB, 0, L""));
        Y_CALL(do_test_splitIf(L":", IF + II + IB, 0, L""));
        Y_CALL(do_test_splitIf(L":", IR, 1, L" "));
        Y_CALL(do_test_splitIf(L"a:", IR, 1, L"a"));
        Y_CALL(do_test_splitIf(L"a:a", IR, 1, L"a"));
        Y_CALL(do_test_splitIf(L"::", D, 0, L"   "));
        Y_CALL(do_test_splitIf(L"::", IF + II + IB, 0, L""));
        Y_CALL(do_test_splitIf(L"::", II, 0, L"  "));
        Y_CALL(do_test_splitIf(L":a", IF, 0, L"a"));
        Y_CALL(do_test_splitIf(L"a::b", II, 1, L"ab"));
        Y_CALL(do_test_splitIf(L"a:b::c", IR, -1, L"c"));
        Y_CALL(do_test_splitIf(L"a:b::", IR, -1, L" "));
        Y_CALL(do_test_splitIf(L"a:b::", IE, -1, L"ba"));
    }

    void test_splitLines()
    {
        auto parts = Utf16W::splitLines(
                L" foo\nfaa \r\n\tfee bar \vbor\f\rrubb");
        Y_EQUAL(parts.size(), 6);
        Y_EQUAL(parts[0], L" foo");
        Y_EQUAL(parts[1], L"faa ");
        Y_EQUAL(parts[2], L"\tfee bar ");
        Y_EQUAL(parts[3], L"bor");
        Y_EQUAL(parts[4], L"");
        Y_EQUAL(parts[5], L"rubb");
    }

    void test_startsWith()
    {
        Y_ASSERT(Utf16W::startsWith(L"qF" UTF16W_GREEK_SMALL_SIGMA L"aBcD",
                                    L"qF" UTF16W_GREEK_CAPITAL_SIGMA,
                                    FindFlags::CASE_INSENSITIVE));
        Y_ASSERT(!Utf16W::startsWith(L"qF" UTF16W_GREEK_SMALL_SIGMA L"aBcD",
                                     L"qF" UTF16W_GREEK_CAPITAL_SIGMA));
        Y_ASSERT(!Utf16W::startsWith(L"qF" UTF16W_GREEK_SMALL_SIGMA L"aBcD",
                                     L"qF" UTF16W_GREEK_CAPITAL_SIGMA L"g",
                                     FindFlags::CASE_INSENSITIVE));
    }

    void test_substring()
    {
        std::wstring s(L"AB" UTF16W_COMBINING_BRIDGE_ABOVE L"CD");
        Y_EQUAL(Utf16W::substring(s, 0),
                L"AB" UTF16W_COMBINING_BRIDGE_ABOVE L"CD");
        Y_EQUAL(Utf16W::substring(s, 0, 4),
                L"AB" UTF16W_COMBINING_BRIDGE_ABOVE L"CD");
        Y_EQUAL(Utf16W::substring(s, 1, 3),
                L"B" UTF16W_COMBINING_BRIDGE_ABOVE L"C");
        Y_EQUAL(Utf16W::substring(s, 2, 2), L"");
        Y_EQUAL(Utf16W::substring(s, 3, 1), L"");
        Y_EQUAL(Utf16W::substring(s, 1, -1),
                L"B" UTF16W_COMBINING_BRIDGE_ABOVE L"C");
        Y_EQUAL(Utf16W::substring(s, 2, -2), L"");
        Y_EQUAL(Utf16W::substring(s, 3, -4), L"");
        Y_EQUAL(Utf16W::substring(s, -3),
                L"B" UTF16W_COMBINING_BRIDGE_ABOVE L"CD");
        Y_EQUAL(Utf16W::substring(s, -3, -1),
                L"B" UTF16W_COMBINING_BRIDGE_ABOVE L"C");
        Y_EQUAL(Utf16W::substring(s, -2, -2), L"");
        Y_EQUAL(Utf16W::substring(s, -1, -3), L"");
    }

    void test_title()
    {
        Y_EQUAL(Utf16W::title(L"aBc " UTF16W_GREEK_SMALL_SIGMA L"De.fooB"),
                L"Abc " UTF16W_GREEK_CAPITAL_SIGMA L"de.Foob");
    }

    void test_toUtf16_fromLatin1()
    {
        Y_EQUAL(Utf16W::toUtf16("\xC5rb\xF8ker", Encoding::LATIN_1),
                UTF16W_LATIN_CAPITAL_A_WITH_RING_ABOVE L"rb"
                UTF16W_LATIN_SMALL_O_WITH_STROKE L"ker");
    }

    void test_toUtf16_fromUtf8()
    {
        Y_EQUAL(Utf16W::toUtf16(UTF8_LATIN_CAPITAL_A_WITH_RING_ABOVE "rb"
                                UTF8_LATIN_SMALL_O_WITH_STROKE "ker",
                                Encoding::UTF_8),
                UTF16W_LATIN_CAPITAL_A_WITH_RING_ABOVE L"rb"
                UTF16W_LATIN_SMALL_O_WITH_STROKE L"ker");
    }

    void test_toUtf16_fromUtf16_wstring()
    {
        Y_EQUAL(Utf16W::toUtf16(L"\u00C5rb\u00F8ker", Encoding::UTF_16_LE),
                UTF16W_LATIN_CAPITAL_A_WITH_RING_ABOVE L"rb"
                UTF16W_LATIN_SMALL_O_WITH_STROKE L"ker");
    }

    void test_toUtf16_fromWindows1252()
    {
        Y_EQUAL(Utf16W::toUtf16("\xC5rb\xF8ker", Encoding::WINDOWS_1252),
                UTF16W_LATIN_CAPITAL_A_WITH_RING_ABOVE L"rb"
                UTF16W_LATIN_SMALL_O_WITH_STROKE L"ker");
        Y_EQUAL(Utf16W::toUtf16("\x94", Encoding::WINDOWS_1252), L"\u201D");
    }

    void test_trim()
    {
        Y_EQUAL(Utf16W::trim(
                L" \n\t foo bar \f\r" UTF16W_PARAGRAPH_SEPARATOR),
                L"foo bar");
        Y_EQUAL(Utf16W::trim(L":--." UTF16W_GREEK_SMALL_SIGMA L"foo bar:--",
                             Unicode::isPunctuation),
                UTF16W_GREEK_SMALL_SIGMA L"foo bar");
        Y_EQUAL(Utf16W::trim(L"A.BC_DFB.-GA-B",
                    [](char32_t c){return Utf16W::contains(L"AB.-", c);}),
                L"C_DFB.-G");
    }

    void test_trimEnd()
    {
        Y_EQUAL(Utf16W::trimEnd(
                L" \n\t foo bar \f\r" UTF16W_PARAGRAPH_SEPARATOR),
                L" \n\t foo bar");
        Y_EQUAL(Utf16W::trimEnd(
                L":--." UTF16W_GREEK_SMALL_SIGMA L"foo bar:--",
                Unicode::isPunctuation),
                L":--." UTF16W_GREEK_SMALL_SIGMA L"foo bar");
    }

    void test_trimStart()
    {
        Y_EQUAL(Utf16W::trimStart(L" \n\t" UTF16W_PARAGRAPH_SEPARATOR
                        L" foo bar \f "), L"foo bar \f ");
        Y_EQUAL(Utf16W::trimStart(L":--." UTF16W_GREEK_SMALL_SIGMA
                        L"foo bar:--", Unicode::isPunctuation),
                UTF16W_GREEK_SMALL_SIGMA L"foo bar:--");
    }

    void test_unescape_BACKSLASH()
    {
        Y_EQUAL(Utf16W::unescape(L"\\u00C6\\n\\t\\\\\\x41"),
                                 UTF16W_LATIN_CAPITAL_AE L"\n\t\\A");
        Y_EQUAL(Utf16W::unescape(L"\\1A"), L"\x01" L"A");
        Y_EQUAL(Utf16W::unescape(L"\\01A"), L"\x01" L"A");
        Y_EQUAL(Utf16W::unescape(L"\\1234"), L"\x53" L"4");
    }

    void test_unescape_JSON()
    {
        Y_EQUAL(Utf16W::unescape(L"\\u00C6\\n\\t\\\\\\x41", EscapeType::JSON),
                                 UTF16W_LATIN_CAPITAL_AE L"\n\t\\A");
        Y_EQUAL(Utf16W::unescape(L"\\1A", EscapeType::JSON), L"1A");
    }

    void test_upper()
    {
        Y_EQUAL(Utf16W::upper(L"aBc" UTF16W_GREEK_SMALL_SIGMA L"D"),
                L"ABC" UTF16W_GREEK_CAPITAL_SIGMA L"D");
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
