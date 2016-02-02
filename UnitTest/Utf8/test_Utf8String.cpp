//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-06-02
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#include "../../Ystring/Utf8.hpp"

#include "../../Ystring/Unicode/UnicodeChars.hpp"
#include "../../Ystring/Unicode/UnicodePredicates.hpp"
#include "../../Ystring/Utf8/Utf8Chars.hpp"
#include "../Ytest/Ytest.hpp"

namespace
{
    using namespace Ystring;

    void test_append()
    {
        std::string s;
        Y_EQUAL(Utf8::append(s, Unicode::GREEK_SMALL_FINAL_SIGMA),
                UTF8_GREEK_SMALL_FINAL_SIGMA);
        Y_EQUAL(Utf8::append(s, Unicode::PUNCTUATION_SPACE),
                UTF8_GREEK_SMALL_FINAL_SIGMA UTF8_PUNCTUATION_SPACE);
    }

    void test_caseInsensitiveCompare()
    {
        Y_LESS(Utf8::caseInsensitiveCompare(
               "aBc" UTF8_GREEK_SMALL_SIGMA,
               "AbC" UTF8_GREEK_CAPITAL_SIGMA "d"), 0);
        Y_LESS(Utf8::caseInsensitiveCompare(
               "aBc" UTF8_GREEK_SMALL_SIGMA "d",
               "AbC" UTF8_GREEK_CAPITAL_TAU), 0);
        Y_EQUAL(Utf8::caseInsensitiveCompare(
               "aBc" UTF8_GREEK_SMALL_SIGMA,
               "AbC" UTF8_GREEK_CAPITAL_SIGMA), 0);
        Y_GREATER(Utf8::caseInsensitiveCompare(
               "aBc" UTF8_GREEK_SMALL_SIGMA "a",
               "AbC" UTF8_GREEK_CAPITAL_SIGMA), 0);
        Y_GREATER(Utf8::caseInsensitiveCompare(
               "aBc" UTF8_GREEK_SMALL_PSI "d",
               "AbC" UTF8_GREEK_CAPITAL_TAU), 0);
    }

    void test_caseInsensitiveEqual()
    {
        Y_ASSERT(Utf8::caseInsensitiveEqual(
                "aBc" UTF8_GREEK_SMALL_SIGMA,
                "AbC" UTF8_GREEK_CAPITAL_SIGMA));
        Y_ASSERT(!Utf8::caseInsensitiveEqual(
                "aBc&8q" UTF8_GREEK_SMALL_SIGMA,
                "AbC&8p" UTF8_GREEK_CAPITAL_SIGMA));
    }

    void test_caseInsensitiveLess()
    {
        Y_ASSERT(!Utf8::caseInsensitiveLess(
                "aBc" UTF8_GREEK_SMALL_SIGMA "D",
                "AbC" UTF8_GREEK_CAPITAL_SIGMA "d"));
        Y_ASSERT(Utf8::caseInsensitiveLess(
                "aBc" UTF8_GREEK_SMALL_SIGMA "d",
                "AbC" UTF8_GREEK_CAPITAL_TAU));
    }

    void test_contains()
    {
        Y_ASSERT(Utf8::contains("ABCDE", 'D'));
        Y_ASSERT(!Utf8::contains("ABCDE", 'F'));
    }

    void test_countCharacters()
    {
        std::string s("A" UTF8_COMBINING_RING_ABOVE
                              "BCDE" UTF8_COMBINING_TILDE);
        Y_EQUAL(Utf8::countCharacters(s), 5);
        Y_EQUAL(Utf8::countCharacters(s.begin(), s.end()), 5);
    }

    void test_countCodePoints()
    {
        Y_EQUAL(Utf8::countCodePoints(
                "A" UTF8_COMBINING_RING_ABOVE "BCDE" UTF8_COMBINING_TILDE),
                7);
    }

    void test_endsWith()
    {
        Y_ASSERT(Utf8::endsWith("aBc" UTF8_GREEK_SMALL_SIGMA "D",
                                 "C" UTF8_GREEK_CAPITAL_SIGMA "d",
                                 FindFlags::CASE_INSENSITIVE));
        Y_ASSERT(!Utf8::endsWith("aBc" UTF8_GREEK_SMALL_SIGMA "D",
                                  "E" UTF8_GREEK_CAPITAL_SIGMA "d",
                                  FindFlags::CASE_INSENSITIVE));
        Y_ASSERT(Utf8::endsWith("aBc" UTF8_GREEK_SMALL_SIGMA "D",
                                 "c" UTF8_GREEK_SMALL_SIGMA "D"));
    }

    void test_escape_BACKSLASH()
    {
        const char str[] = "ab\x01""cd\nef\x7Fgh\x80";
        Y_EQUAL(Utf8::escape(str), "ab\\x01cd\\nef\\x7Fgh\\x80");
        Y_EQUAL(Utf8::escape("\xef\xbf\xbf"), "\xef\xbf\xbf");
    }

    void test_escape_BACKSLASH_ASCII()
    {
        Y_EQUAL(Utf8::escape("\xef\xbf\xbf", EscapeType::BACKSLASH_ASCII),
                 "\\xEF\\xBF\\xBF");
    }

    void test_escape_BACKSLASH_ASCII_SMART()
    {
        Y_EQUAL(Utf8::escape("\n\tABCD", EscapeType::BACKSLASH_ASCII_SMART),
                 "\\n\\tABCD");
        Y_EQUAL(Utf8::escape("\x7f", EscapeType::BACKSLASH_ASCII_SMART),
                 "\\x7F");
        Y_EQUAL(Utf8::escape("\xc2\x80", EscapeType::BACKSLASH_ASCII_SMART),
                 "\\x80");
        Y_EQUAL(Utf8::escape("\xc4\x80", EscapeType::BACKSLASH_ASCII_SMART),
                 "\\u0100");
        Y_EQUAL(Utf8::escape("\xef\xbf\xbf",
                             EscapeType::BACKSLASH_ASCII_SMART),
                 "\\uFFFF");
        Y_EQUAL(Utf8::escape("\xf0\x90\x80\x80",
                              EscapeType::BACKSLASH_ASCII_SMART),
                 "\\U00010000");
        Y_EQUAL(Utf8::escape("\xF3\xBF\xBF\xBF",
                              EscapeType::BACKSLASH_ASCII_SMART),
                 "\\U000FFFFF");
    }

    void test_escape_JSON()
    {
        Y_EQUAL(Utf8::escape("\n\tABCD", EscapeType::JSON), "\\n\\tABCD");
        Y_EQUAL(Utf8::escape("\x7f", EscapeType::JSON), "\\u007F");
        Y_EQUAL(Utf8::escape("\xc2\x80", EscapeType::JSON), "\\u0080");
    }

    void test_escape_JSON_ASCII()
    {
        Y_EQUAL(Utf8::escape("\n\t\"ABCD", EscapeType::JSON_ASCII),
                 "\\n\\t\\\"ABCD");
        Y_EQUAL(Utf8::escape("\x7f", EscapeType::JSON_ASCII),
                 "\\u007F");
        Y_EQUAL(Utf8::escape("\xc2\x80", EscapeType::JSON_ASCII),
                 "\\u0080");
        Y_EQUAL(Utf8::escape("\xc4\x80", EscapeType::JSON_ASCII),
                 "\\u0100");
        Y_EQUAL(Utf8::escape("\xef\xbf\xbf", EscapeType::JSON_ASCII),
                 "\\uFFFF");
    }

    void test_escape_URL_QUERY()
    {
        Y_EQUAL(Utf8::escape("{lokasjon: {vegreferanse: [\"E6\", \"E18\"] }, "
                             "objektTyper: [{id: 45, antall: 10}]}",
                             EscapeType::URL_QUERY),
                "%7Blokasjon%3A%20%7Bvegreferanse%3A%20%5B%22E6%22%2C%20"
                "%22E18%22%5D%20%7D%2C%20objektTyper%3A%20%5B%7Bid%3A%20"
                "45%2C%20antall%3A%2010%7D%5D%7D");
    }

    void test_escape_XML_ATTRIBUTE()
    {
        Y_EQUAL(Utf8::escape("\n\tA&\"'<B>", EscapeType::XML_ATTRIBUTE),
                "&#xA;&#x9;A&amp;&quot;&apos;&lt;B&gt;");
    }

    void test_escape_XML_TEXT()
    {
        Y_EQUAL(Utf8::escape("\n\tA&\"'<B>", EscapeType::XML_TEXT),
                "\n\tA&amp;\"\'&lt;B&gt;");
    }

    void test_findLast()
    {
        auto s = std::string("abc_gh" UTF8_GREEK_CAPITAL_SIGMA  "IJ_gH"
                             UTF8_GREEK_SMALL_SIGMA "Ij_kLM_nop");
        auto r = Utf8::findLast(s, "gh" UTF8_GREEK_CAPITAL_SIGMA "ij",
                                FindFlags::CASE_INSENSITIVE);
        Y_EQUAL(std::string(r.first, r.second),
                 "gH" UTF8_GREEK_SMALL_SIGMA "Ij");
        auto t = Utf8::findLast(r.first, r.second,
                                UTF8_GREEK_CAPITAL_SIGMA "i",
                                FindFlags::CASE_INSENSITIVE);
        Y_EQUAL(std::string(t.first, t.second),
                UTF8_GREEK_SMALL_SIGMA "I");
        auto u = Utf8::findLast(r.first, r.second,
                                UTF8_GREEK_CAPITAL_SIGMA "i");
        Y_ASSERT(u.first == u.second && u.first == r.first);
    }

    void test_findLastNewline()
    {
        auto str = std::string("abc\ndef\r\nghi");
        auto s = make_pair(begin(str), end(str));
        auto r = Utf8::findLastNewline(str);
        Y_EQUAL(std::string(r.second, s.second), "ghi");
        auto t = make_pair(s.first, r.first);
        r = Utf8::findLastNewline(t.first, t.second);
        Y_EQUAL(std::string(r.first, r.second), "\n");
        Y_EQUAL(std::string(r.second, t.second), "def");
        t.second = r.first;
        r = Utf8::findLastNewline(t.first, t.second);
        Y_ASSERT(r.first == r.second);
        Y_ASSERT(r.first == t.first);
        Y_EQUAL(std::string(r.first, t.second), "abc");
    }

    void test_findFirst()
    {
        auto s = std::string(
                "abc_ghIJ_gH" UTF8_GREEK_SMALL_SIGMA "Ij_kLM_nop");
        auto r = Utf8::findFirst(s, "gh" UTF8_GREEK_CAPITAL_SIGMA "ij",
                                 FindFlags::CASE_INSENSITIVE);
        Y_EQUAL(std::string(r.first, r.second),
                 "gH" UTF8_GREEK_SMALL_SIGMA "Ij");
        auto t = Utf8::findFirst(r.first, r.second,
                                 UTF8_GREEK_CAPITAL_SIGMA "i",
                                 FindFlags::CASE_INSENSITIVE);
        Y_EQUAL(std::string(t.first, t.second), UTF8_GREEK_SMALL_SIGMA "I");
        auto u = Utf8::findFirst(r.first, r.second,
                                 UTF8_GREEK_CAPITAL_SIGMA "i");
        Y_ASSERT(u.first == u.second && u.second == r.second);
    }

    void test_findFirstNewline()
    {
        auto str = std::string("abc\ndef\r\nghi");
        auto s = make_pair(begin(str), end(str));
        auto r = Utf8::findFirstNewline(str);
        Y_EQUAL(std::string(s.first, r.first), "abc");
        auto t = make_pair(r.second, s.second);
        r = Utf8::findFirstNewline(t.first, t.second);
        Y_EQUAL(std::string(t.first, r.first), "def");
        t.first = r.second;
        r = Utf8::findFirstNewline(t.first, t.second);
        Y_ASSERT(r.first == r.second);
        Y_EQUAL(std::string(t.first, r.first), "ghi");
    }

    void test_getCodePoint()
    {
        auto str = "The " UTF8_GREEK_SMALL_OMEGA
                   UTF8_COMBINING_BRIDGE_ABOVE UTF8_COMBINING_TILDE
                   " and the A" UTF8_COMBINING_INVERTED_BREVE
                   UTF8_COMBINING_DOT_ABOVE ".";
        Y_EQUAL(Utf8::getCodePoint(str, 0), 'T');
        Y_EQUAL(Utf8::getCodePoint(str, -1), '.');
        Y_EQUAL(Utf8::getCodePoint(str, 4), Unicode::GREEK_SMALL_OMEGA);
        Y_EQUAL(Utf8::getCodePoint(str, 5), Unicode::COMBINING_BRIDGE_ABOVE);
        Y_EQUAL(Utf8::getCodePoint(str, -3),
                Unicode::COMBINING_INVERTED_BREVE);
        Y_EQUAL(Utf8::getCodePoint(str, -4), 'A');
    }

    void test_hasEscapedCharacters_JSON()
    {
        Y_ASSERT(Utf8::hasEscapedCharacters("ABC\\n", EscapeType::JSON));
        Y_ASSERT(!Utf8::hasEscapedCharacters("ABC\n", EscapeType::JSON));
        Y_ASSERT(Utf8::hasEscapedCharacters("ABC\\ ", EscapeType::JSON));
    }

    void test_hasUnescapedCharacters_JSON()
    {
        Y_ASSERT(Utf8::hasUnescapedCharacters("ABC\n", EscapeType::JSON));
        Y_ASSERT(Utf8::hasUnescapedCharacters("ABC\"", EscapeType::JSON));
        Y_ASSERT(Utf8::hasUnescapedCharacters("C:\\AB\\CD",
                                              EscapeType::JSON));
        Y_ASSERT(!Utf8::hasUnescapedCharacters("A:'&%/<",
                                               EscapeType::JSON));
        Y_ASSERT(!Utf8::hasUnescapedCharacters("/a/b/c", EscapeType::JSON));
        Y_ASSERT(!Utf8::hasUnescapedCharacters("\xc3\x80", EscapeType::JSON));
        Y_ASSERT(Utf8::hasUnescapedCharacters("\xc3\x80",
                                              EscapeType::JSON_ASCII));
    }

    void test_insert()
    {
        auto str = "The " UTF8_GREEK_SMALL_OMEGA
                   UTF8_COMBINING_BRIDGE_ABOVE UTF8_COMBINING_TILDE
                   " and the A" UTF8_COMBINING_INVERTED_BREVE
                   UTF8_COMBINING_DOT_ABOVE ".";
        auto r = Utf8::insert(Utf8::insert(str, 13, " insanely"),
                              -2, "great ");
        Y_EQUAL(r, "The " UTF8_GREEK_SMALL_OMEGA
                     UTF8_COMBINING_BRIDGE_ABOVE UTF8_COMBINING_TILDE
                     " and the insanely great A" UTF8_COMBINING_INVERTED_BREVE
                     UTF8_COMBINING_DOT_ABOVE ".");
    }

    void test_insertChar()
    {
        auto str = "The " UTF8_GREEK_SMALL_OMEGA
                   UTF8_COMBINING_BRIDGE_ABOVE UTF8_COMBINING_TILDE
                   " and the A" UTF8_COMBINING_INVERTED_BREVE
                   UTF8_COMBINING_DOT_ABOVE ".";
        auto r = Utf8::insert(str, 5, Unicode::GREEK_SMALL_FINAL_SIGMA);
        Y_EQUAL(r, "The " UTF8_GREEK_SMALL_OMEGA
                    UTF8_COMBINING_BRIDGE_ABOVE UTF8_COMBINING_TILDE
                    UTF8_GREEK_SMALL_FINAL_SIGMA
                    " and the A" UTF8_COMBINING_INVERTED_BREVE
                    UTF8_COMBINING_DOT_ABOVE ".");
    }

    void test_isAlphaNumeric()
    {
        Y_ASSERT(Utf8::isAlphaNumeric("Ab1"));
        Y_ASSERT(!Utf8::isAlphaNumeric("Ab-1"));
        Y_ASSERT(!Utf8::isAlphaNumeric(""));
        std::string s("2v" UTF8_GREEK_SMALL_OMEGA
                              UTF8_COMBINING_BRIDGE_ABOVE);
        Y_ASSERT(Utf8::isAlphaNumeric(begin(s), end(s)));
    }

    void test_isValidUtf8()
    {
        Y_ASSERT(Utf8::isValidUtf8("AB\xC1\x80"));
        Y_ASSERT(!Utf8::isValidUtf8("AB\xC0\x7F"));
        Y_ASSERT(!Utf8::isValidUtf8("\xC0\xFF"));
        Y_ASSERT(Utf8::isValidUtf8("\xE2\xBF\x80"));
        Y_ASSERT(Utf8::isValidUtf8("\xF3\xA0\xA0\xA0"));
        Y_ASSERT(!Utf8::isValidUtf8("\xF4\x80\x80\x80"));
        Y_ASSERT(!Utf8::isValidUtf8("\xF8\xA0\xA0\xA0\xA0"));
    }

    void test_join()
    {
        std::string rawStrings[] = {"foo", "faa", "fii", "fee", "fuu"};
        auto result1 = Utf8::join(rawStrings, 5);
        Y_EQUAL(result1, "foofaafiifeefuu");
        auto result2 = Utf8::join(rawStrings, 5, ":-:");
        Y_EQUAL(result2, "foo:-:faa:-:fii:-:fee:-:fuu");
        std::vector<std::string> strings(std::begin(rawStrings),
                                         std::end(rawStrings));
        result1 = Utf8::join(strings);
        Y_EQUAL(result1, "foofaafiifeefuu");
        result2 = Utf8::join(strings, ":-:");
        Y_EQUAL(result2, "foo:-:faa:-:fii:-:fee:-:fuu");
    }

    void test_lower()
    {
        Y_EQUAL(Utf8::lower("aBc" UTF8_GREEK_CAPITAL_SIGMA "d12$E"),
                 "abc" UTF8_GREEK_SMALL_SIGMA "d12$e");
    }

    void test_nextCharacter_const()
    {
        const std::string str("AB" UTF8_GREEK_SMALL_OMEGA
                              UTF8_COMBINING_BRIDGE_ABOVE
                              UTF8_COMBINING_TILDE "C");
        auto b = str.begin(), e = str.end();
        Y_EQUAL(distance(str.begin(), Utf8::nextCharacter(b, e)), 1);
        Y_EQUAL(distance(str.begin(), Utf8::nextCharacter(b, e, 0)), 0);
        Y_EQUAL(distance(str.begin(), Utf8::nextCharacter(b, e, 1)), 1);
        Y_EQUAL(distance(str.begin(), Utf8::nextCharacter(b, e, 2)), 2);
        Y_EQUAL(distance(str.begin(), Utf8::nextCharacter(b, e, 3)), 8);
        Y_EQUAL(distance(str.begin(), Utf8::nextCharacter(b, e, 4)), 9);
        Y_THROWS(Utf8::nextCharacter(b, e, 5), YstringException);
    }

    void test_nextCharacter_mutable()
    {
        std::string str("AB" UTF8_GREEK_SMALL_OMEGA
                                UTF8_COMBINING_BRIDGE_ABOVE
                                UTF8_COMBINING_TILDE "C");
        auto b = str.begin(), e = str.end();
        Y_EQUAL(distance(str.begin(), Utf8::nextCharacter(b, e)), 1);
        Y_EQUAL(distance(str.begin(), Utf8::nextCharacter(b, e, 0)), 0);
        Y_EQUAL(distance(str.begin(), Utf8::nextCharacter(b, e, 1)), 1);
        Y_EQUAL(distance(str.begin(), Utf8::nextCharacter(b, e, 2)), 2);
        Y_EQUAL(distance(str.begin(), Utf8::nextCharacter(b, e, 3)), 8);
        Y_EQUAL(distance(str.begin(), Utf8::nextCharacter(b, e, 4)), 9);
        Y_THROWS(Utf8::nextCharacter(b, e, 5), YstringException);
    }

    void test_nthCharacter()
    {
        std::string str("AB" UTF8_GREEK_SMALL_OMEGA
                                UTF8_COMBINING_BRIDGE_ABOVE
                                UTF8_COMBINING_TILDE "C");
        Y_EQUAL(distance(str.begin(), Utf8::nthCharacter(str, 0)), 0);
        Y_EQUAL(distance(str.begin(), Utf8::nthCharacter(str, 1)), 1);
        Y_EQUAL(distance(str.begin(), Utf8::nthCharacter(str, 2)), 2);
        Y_EQUAL(distance(str.begin(), Utf8::nthCharacter(str, 3)), 8);
        Y_EQUAL(distance(str.begin(), Utf8::nthCharacter(str, 4)), 9);
        Y_EQUAL(distance(str.begin(), Utf8::nthCharacter(str, -1)), 8);
        Y_EQUAL(distance(str.begin(), Utf8::nthCharacter(str, -2)), 2);
        Y_EQUAL(distance(str.begin(), Utf8::nthCharacter(str, -3)), 1);
        Y_EQUAL(distance(str.begin(), Utf8::nthCharacter(str, -4)), 0);
        Y_THROWS(Utf8::nthCharacter(str, 5), YstringException);
        Y_THROWS(Utf8::nthCharacter(str, -5), YstringException);
    }

    void test_prevCharacter_const()
    {
        const std::string str("AB" UTF8_GREEK_SMALL_OMEGA
                              UTF8_COMBINING_BRIDGE_ABOVE
                              UTF8_COMBINING_TILDE "C");
        auto b = str.begin(), e = str.end();
        Y_EQUAL(distance(str.begin(), Utf8::prevCharacter(b, e)), 8);
        Y_EQUAL(distance(str.begin(), Utf8::prevCharacter(b, e, 0)), 9);
        Y_EQUAL(distance(str.begin(), Utf8::prevCharacter(b, e, 1)), 8);
        Y_EQUAL(distance(str.begin(), Utf8::prevCharacter(b, e, 2)), 2);
        Y_EQUAL(distance(str.begin(), Utf8::prevCharacter(b, e, 3)), 1);
        Y_EQUAL(distance(str.begin(), Utf8::prevCharacter(b, e, 4)), 0);
        Y_THROWS(Utf8::prevCharacter(b, e, 5), YstringException);
    }

    void test_prevCharacter_mutable()
    {
        std::string str("AB" UTF8_GREEK_SMALL_OMEGA
                                UTF8_COMBINING_BRIDGE_ABOVE
                                UTF8_COMBINING_TILDE "C");
        auto b = str.begin(), e = str.end();
        Y_EQUAL(distance(str.begin(), Utf8::prevCharacter(b, e)), 8);
        Y_EQUAL(distance(str.begin(), Utf8::prevCharacter(b, e, 0)), 9);
        Y_EQUAL(distance(str.begin(), Utf8::prevCharacter(b, e, 1)), 8);
        Y_EQUAL(distance(str.begin(), Utf8::prevCharacter(b, e, 2)), 2);
        Y_EQUAL(distance(str.begin(), Utf8::prevCharacter(b, e, 3)), 1);
        Y_EQUAL(distance(str.begin(), Utf8::prevCharacter(b, e, 4)), 0);
        Y_THROWS(Utf8::prevCharacter(b, e, 5), YstringException);
    }

    void test_replace_indexes()
    {
        auto s = "The " UTF8_GREEK_SMALL_OMEGA
                 UTF8_COMBINING_BRIDGE_ABOVE UTF8_COMBINING_TILDE
                 " and the A" UTF8_COMBINING_INVERTED_BREVE
                 UTF8_COMBINING_DOT_ABOVE ".";
        Y_EQUAL(Utf8::replace(s, 6, -3, "beats no"),
                "The " UTF8_GREEK_SMALL_OMEGA
                UTF8_COMBINING_BRIDGE_ABOVE UTF8_COMBINING_TILDE
                " beats no A" UTF8_COMBINING_INVERTED_BREVE
                UTF8_COMBINING_DOT_ABOVE ".");
    }

    void test_replace_string()
    {
        auto s = "The " UTF8_GREEK_SMALL_OMEGA " and the A.";
        Y_EQUAL(Utf8::replace(s,
                              UTF8_GREEK_SMALL_OMEGA " and",
                              UTF8_GREEK_CAPITAL_OMEGA " or"),
                "The " UTF8_GREEK_CAPITAL_OMEGA " or the A.");
        Y_EQUAL(Utf8::replace(s,
                              UTF8_GREEK_CAPITAL_OMEGA " aNd",
                              UTF8_GREEK_CAPITAL_SIGMA " or"),
                s);
        Y_EQUAL(Utf8::replace(s,
                              UTF8_GREEK_CAPITAL_OMEGA " aNd",
                              UTF8_GREEK_CAPITAL_SIGMA " or",
                              0, FindFlags::CASE_INSENSITIVE),
                "The " UTF8_GREEK_CAPITAL_SIGMA " or the A.");
        Y_EQUAL(Utf8::replace(s, UTF8_GREEK_SMALL_OMEGA " and", ""),
                "The  the A.");
        Y_EQUAL(Utf8::replace(s, "", "foo"), s);
    }

    void test_replace_string_backwards()
    {
        Y_EQUAL(Utf8::replace("123 foo 456 foo 789 foo 012", "foo",
                              "bar", -2),
                "123 foo 456 bar 789 bar 012");
    }

    void test_replaceCodePoint()
    {
        Y_EQUAL(Utf8::replaceCodePoint("AB" UTF8_GREEK_SMALL_GAMMA "D",
                                       Unicode::GREEK_SMALL_GAMMA,
                                       Unicode::FIGURE_SPACE),
                "AB" UTF8_FIGURE_SPACE "D");
        Y_EQUAL(Utf8::replaceCodePoint("ABCDCDECDEFGCD", 'C', '_', 3),
                "AB_D_DE_DEFGCD");
        Y_EQUAL(Utf8::replaceCodePoint("ABCDCDECDEFGCD", 'C', '_', -3),
                "ABCD_DE_DEFG_D");
    }

    void test_replaceInvalidUtf8()
    {
        auto s = "ABC\xC0\xDF" "DEF\xD0\x80\x80" "GH\xE8\x80" "I\xC8";
        Y_EQUAL(Utf8::replaceInvalidUtf8(s, '?'), "ABC??DEF\xD0\x80?GH?I?");
    }

    void test_replaceInvalidUtf8InPlace()
    {
        std::string s("ABC\xC0\xDF" "DEF\xD0\x80\x80" "GH\xE8\x80" "I\xC8");
        Y_EQUAL(Utf8::replaceInvalidUtf8InPlace(s),
                "ABC??DEF\xD0\x80?GH??I?");
    }

    void test_reverse()
    {
        auto s = "The " UTF8_GREEK_SMALL_OMEGA UTF8_COMBINING_BRIDGE_ABOVE
                UTF8_COMBINING_TILDE " and the A"
                UTF8_COMBINING_INVERTED_BREVE UTF8_COMBINING_DOT_ABOVE ".";
        std::string result;
        Y_EQUAL(Utf8::reverse(s),
                ".A" UTF8_COMBINING_INVERTED_BREVE UTF8_COMBINING_DOT_ABOVE
                " eht dna " UTF8_GREEK_SMALL_OMEGA
                UTF8_COMBINING_BRIDGE_ABOVE UTF8_COMBINING_TILDE " ehT");
    }

    void test_split_caseInsensitive_NonASCII()
    {
        auto parts = Utf8::split(
                ":" UTF8_GREEK_CAPITAL_OMEGA "Q:foo:"
                UTF8_GREEK_CAPITAL_OMEGA "q:faa:"
                UTF8_GREEK_SMALL_OMEGA "Q:bor:"
                UTF8_GREEK_SMALL_OMEGA "q:",
                ":" UTF8_GREEK_SMALL_OMEGA "q:",
                3,
                SplitFlags::CASE_INSENSITIVE);
        Y_EQUAL(parts.size(), 4);
        Y_EQUAL(parts[0], "");
        Y_EQUAL(parts[1], "foo");
        Y_EQUAL(parts[2], "faa");
        Y_EQUAL(parts[3], "bor:" UTF8_GREEK_SMALL_OMEGA "q:");
    }

    void test_split_caseInsensitive_NoTail()
    {
        auto parts = Utf8::split("123:aB:321:AB:234:ab:", ":ab:", 0,
                                 SplitFlags::CASE_INSENSITIVE);
        Y_EQUAL(parts.size(), 4);
        Y_EQUAL(parts[0], "123");
        Y_EQUAL(parts[1], "321");
        Y_EQUAL(parts[2], "234");
        Y_EQUAL(parts[3], "");
    }

    void test_split_caseInsensitive_reverse()
    {
        auto parts = Utf8::split("1234ab4567AB8901aB2345", "AB", -2,
                                 SplitFlags::CASE_INSENSITIVE |
                                 SplitFlags::IGNORE_REMAINDER);
        Y_EQUAL(parts.size(), 2);
        Y_EQUAL(parts[0], "2345");
        Y_EQUAL(parts[1], "8901");
    }

    void test_split_caseInsensitive_Tail()
    {
        auto parts = Utf8::split("123:aB:321:AB:234:Ab:432", ":ab:", 0,
                                 SplitFlags::CASE_INSENSITIVE);
        Y_EQUAL(parts.size(), 4);
        Y_EQUAL(parts[0], "123");
        Y_EQUAL(parts[1], "321");
        Y_EQUAL(parts[2], "234");
        Y_EQUAL(parts[3], "432");
    }

    void test_split_caseSensitive_Tail()
    {
        auto parts = Utf8::split("123:aB:321:AB:234:AB:432", ":AB:");
        Y_EQUAL(parts.size(), 3);
        Y_EQUAL(parts[0], "123:aB:321");
        Y_EQUAL(parts[1], "234");
        Y_EQUAL(parts[2], "432");
    }

    void test_split_caseSensitive_NoTail()
    {
        auto parts = Utf8::split("123:aB:321:AB:234:AB:", ":AB:");
        Y_EQUAL(parts.size(), 3);
        Y_EQUAL(parts[0], "123:aB:321");
        Y_EQUAL(parts[1], "234");
        Y_EQUAL(parts[2], "");
    }

    void test_split_whitespace()
    {
        auto parts = Utf8::split(" foo faa\r\n\tfee bar "
                                         UTF8_EM_SPACE "\tbor ");
        Y_EQUAL(parts.size(), 5);
        Y_EQUAL(parts[0], "foo");
        Y_EQUAL(parts[1], "faa");
        Y_EQUAL(parts[2], "fee");
        Y_EQUAL(parts[3], "bar");
        Y_EQUAL(parts[4], "bor");
    }

    void test_split_whitespace_backwards()
    {
        auto parts = Utf8::split("haa baa ett yui ert swr", -2);
        Y_EQUAL(parts.size(), 3);
        Y_EQUAL(parts[0], "swr");
        Y_EQUAL(parts[1], "ert");
        Y_EQUAL(parts[2], "haa baa ett yui");
    }

    void test_splitIf()
    {
        auto parts = Utf8::splitIf(
                " foo faa\r\n\tfee bar " UTF8_EM_SPACE "\tbor ",
                Unicode::isWhitespace, 0, SplitFlags::IGNORE_EMPTY);
        Y_EQUAL(parts.size(), 5);
        Y_EQUAL(parts[0], "foo");
        Y_EQUAL(parts[1], "faa");
        Y_EQUAL(parts[2], "fee");
        Y_EQUAL(parts[3], "bar");
        Y_EQUAL(parts[4], "bor");
    }

    void do_test_splitIf(const std::string& s,
                         SplitFlags_t flags, ptrdiff_t count,
                         const std::string& expected)
    {
        auto parts = Utf8::splitIf(s, [](uint32_t c){return c == ':';},
                                   count, flags);
        Y_EQUAL(parts.size(), expected.size());
        for (auto i = 0u; i < parts.size(); ++i)
        {
            auto expect = expected[i] == ' ' ? std::string()
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
        Y_CALL(do_test_splitIf("", D, 0, " "));
        Y_CALL(do_test_splitIf("", IF, 0, ""));
        Y_CALL(do_test_splitIf("", II + IB, 0, " "));
        Y_CALL(do_test_splitIf(":", D, 0, "  "));
        Y_CALL(do_test_splitIf(":", IF, 0, " "));
        Y_CALL(do_test_splitIf(":", IB, 0, " "));
        Y_CALL(do_test_splitIf(":", IF + IB, 0, ""));
        Y_CALL(do_test_splitIf(":", IF + II + IB, 0, ""));
        Y_CALL(do_test_splitIf(":", IR, 1, " "));
        Y_CALL(do_test_splitIf("a:", IR, 1, "a"));
        Y_CALL(do_test_splitIf("a:a", IR, 1, "a"));
        Y_CALL(do_test_splitIf("::", D, 0, "   "));
        Y_CALL(do_test_splitIf("::", IF + II + IB, 0, ""));
        Y_CALL(do_test_splitIf("::", II, 0, "  "));
        Y_CALL(do_test_splitIf(":a", IF, 0, "a"));
        Y_CALL(do_test_splitIf("a::b", II, 1, "ab"));
        Y_CALL(do_test_splitIf("a:b::c", IR, -1, "c"));
        Y_CALL(do_test_splitIf("a:b::", IR, -1, " "));
        Y_CALL(do_test_splitIf("a:b::", IE, -1, "ba"));
    }

    void test_splitLines()
    {
        auto parts = Utf8::splitLines(
                " foo\nfaa \r\n\tfee bar \vbor\f\rrubb");
        Y_EQUAL(parts.size(), 6);
        Y_EQUAL(parts[0], " foo");
        Y_EQUAL(parts[1], "faa ");
        Y_EQUAL(parts[2], "\tfee bar ");
        Y_EQUAL(parts[3], "bor");
        Y_EQUAL(parts[4], "");
        Y_EQUAL(parts[5], "rubb");
    }

    void test_startsWith()
    {
        Y_ASSERT(Utf8::startsWith("qF" UTF8_GREEK_SMALL_SIGMA "aBcD",
                                  "qF" UTF8_GREEK_CAPITAL_SIGMA,
                                  FindFlags::CASE_INSENSITIVE));
        Y_ASSERT(!Utf8::startsWith("qF" UTF8_GREEK_SMALL_SIGMA "aBcD",
                                   "qF" UTF8_GREEK_CAPITAL_SIGMA));
        Y_ASSERT(!Utf8::startsWith("qF" UTF8_GREEK_SMALL_SIGMA "aBcD",
                                   "qF" UTF8_GREEK_CAPITAL_SIGMA "g",
                                   FindFlags::CASE_INSENSITIVE));
    }

    void test_substring()
    {
        std::string s("AB" UTF8_COMBINING_BRIDGE_ABOVE "CD");
        Y_EQUAL(Utf8::substring(s, 0),
                "AB" UTF8_COMBINING_BRIDGE_ABOVE "CD");
        Y_EQUAL(Utf8::substring(s, 0, 4),
                "AB" UTF8_COMBINING_BRIDGE_ABOVE "CD");
        Y_EQUAL(Utf8::substring(s, 1, 3),
                "B" UTF8_COMBINING_BRIDGE_ABOVE "C");
        Y_EQUAL(Utf8::substring(s, 2, 2), "");
        Y_EQUAL(Utf8::substring(s, 3, 1), "");
        Y_EQUAL(Utf8::substring(s, 1, -1),
                "B" UTF8_COMBINING_BRIDGE_ABOVE "C");
        Y_EQUAL(Utf8::substring(s, 2, -2), "");
        Y_EQUAL(Utf8::substring(s, 3, -4), "");
        Y_EQUAL(Utf8::substring(s, -3),
                "B" UTF8_COMBINING_BRIDGE_ABOVE "CD");
        Y_EQUAL(Utf8::substring(s, -3, -1),
                "B" UTF8_COMBINING_BRIDGE_ABOVE "C");
        Y_EQUAL(Utf8::substring(s, -2, -2), "");
        Y_EQUAL(Utf8::substring(s, -1, -3), "");
    }

    void test_title()
    {
        Y_EQUAL(Utf8::title("aBc " UTF8_GREEK_SMALL_SIGMA "De.fooB"),
                "Abc " UTF8_GREEK_CAPITAL_SIGMA "de.Foob");
    }

    void test_toUtf8_fromLatin1()
    {
        Y_EQUAL(Utf8::toUtf8("\xC5rb\xF8ker", Encoding::LATIN_1),
                UTF8_LATIN_CAPITAL_A_WITH_RING_ABOVE "rb"
                UTF8_LATIN_SMALL_O_WITH_STROKE "ker");
    }

    void test_toUtf8_fromUtf8()
    {
        Y_EQUAL(Utf8::toUtf8(UTF8_LATIN_CAPITAL_A_WITH_RING_ABOVE "rb"
                             UTF8_LATIN_SMALL_O_WITH_STROKE "ker",
                             Encoding::UTF_8),
                UTF8_LATIN_CAPITAL_A_WITH_RING_ABOVE "rb"
                UTF8_LATIN_SMALL_O_WITH_STROKE "ker");
    }

    #ifdef YSTRING_WCHAR_IS_2_BYTES

    void test_toUtf8_fromUtf16_wstring()
    {
        Y_EQUAL(Utf8::toUtf8(L"\u00C5rb\u00F8ker", Encoding::UTF_16_LE),
                UTF8_LATIN_CAPITAL_A_WITH_RING_ABOVE "rb"
                UTF8_LATIN_SMALL_O_WITH_STROKE "ker");
    }

    #endif

    void test_toUtf8_fromWindows1252()
    {
        Y_EQUAL(Utf8::toUtf8("\xC5rb\xF8ker", Encoding::WINDOWS_1252),
                UTF8_LATIN_CAPITAL_A_WITH_RING_ABOVE "rb"
                UTF8_LATIN_SMALL_O_WITH_STROKE "ker");
        Y_EQUAL(Utf8::toUtf8("\x94", Encoding::WINDOWS_1252), "\xE2\x80\x9D");
    }

    void test_trim()
    {
        Y_EQUAL(Utf8::trim(" \n\t foo bar \f\r" UTF8_PARAGRAPH_SEPARATOR),
                "foo bar");
        Y_EQUAL(Utf8::trim(":--." UTF8_GREEK_SMALL_SIGMA "foo bar:--",
                           Unicode::isPunctuation),
                UTF8_GREEK_SMALL_SIGMA "foo bar");
        Y_EQUAL(Utf8::trim("A.BC_DFB.-GA-B",
                           [](uint32_t c){return Utf8::contains("AB.-", c);}),
                "C_DFB.-G");
    }

    void test_trimEnd()
    {
        Y_EQUAL(Utf8::trimEnd(" \n\t foo bar \f\r" UTF8_PARAGRAPH_SEPARATOR),
                " \n\t foo bar");
        Y_EQUAL(Utf8::trimEnd(":--." UTF8_GREEK_SMALL_SIGMA "foo bar:--",
                              Unicode::isPunctuation),
                ":--." UTF8_GREEK_SMALL_SIGMA "foo bar");
    }

    void test_trimStart()
    {
        Y_EQUAL(Utf8::trimStart(
                " \n\t" UTF8_PARAGRAPH_SEPARATOR " foo bar \f "),
                "foo bar \f ");
        Y_EQUAL(Utf8::trimStart(":--." UTF8_GREEK_SMALL_SIGMA "foo bar:--",
                                Unicode::isPunctuation),
                UTF8_GREEK_SMALL_SIGMA "foo bar:--");
    }

    void test_unescape_BACKSLASH()
    {
        Y_EQUAL(Utf8::unescape("\\u00C6\\n\\t\\\\\\x41"),
                                UTF8_LATIN_CAPITAL_AE "\n\t\\A");
        Y_EQUAL(Utf8::unescape("\\1A"), "\x01""A");
        Y_EQUAL(Utf8::unescape("\\01A"), "\x01""A");
        Y_EQUAL(Utf8::unescape("\\1234"), "\x53""4");
    }

    void test_unescape_JSON()
    {
        Y_EQUAL(Utf8::unescape("\\u00C6\\n\\t\\\\\\x41", EscapeType::JSON),
                                UTF8_LATIN_CAPITAL_AE "\n\t\\A");
        Y_EQUAL(Utf8::unescape("\\1A", EscapeType::JSON), "1A");
    }

    void test_upper()
    {
        Y_EQUAL(Utf8::upper("aBc" UTF8_GREEK_SMALL_SIGMA "D"),
                 "ABC" UTF8_GREEK_CAPITAL_SIGMA "D");
    }

    Y_SUBTEST("Utf8",
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
              test_escape_URL_QUERY,
              test_escape_XML_ATTRIBUTE,
              test_escape_XML_TEXT,
              test_findLast,
              test_findLastNewline,
              test_findFirst,
              test_findFirstNewline,
              test_getCodePoint,
              test_hasEscapedCharacters_JSON,
              test_hasUnescapedCharacters_JSON,
              test_insert,
              test_insertChar,
              test_isAlphaNumeric,
              test_isValidUtf8,
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
              test_replaceInvalidUtf8,
              test_replaceInvalidUtf8InPlace,
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
              test_toUtf8_fromLatin1,
              test_toUtf8_fromUtf8,
              test_toUtf8_fromWindows1252,
              test_trim,
              test_trimEnd,
              test_trimStart,
              test_unescape_BACKSLASH,
              test_unescape_JSON,
              test_upper);

#ifdef YSTRING_WCHAR_IS_2_BYTES

    Y_SUBTEST("Utf8",
              test_toUtf8_fromUtf16_wstring);

#endif

}
