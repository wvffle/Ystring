//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-06-02
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#include "Ystring/Utf8/Utf8String.hpp"

#include "Ystring/Unicode/UnicodePredicates.hpp"
#include "Ystring/Utf8/Utf8Chars.hpp"
#include <JEBTest/JEBTest.hpp>

namespace {

using namespace Ystring;

void test_append()
{
    std::string s;
    JT_EQUAL(Utf8::append(s, Unicode::GREEK_SMALL_FINAL_SIGMA),
             UTF8_GREEK_SMALL_FINAL_SIGMA);
    JT_EQUAL(Utf8::append(s, Unicode::PUNCTUATION_SPACE),
             UTF8_GREEK_SMALL_FINAL_SIGMA UTF8_PUNCTUATION_SPACE);
}

void test_caseInsensitiveCompare()
{
    JT_LESS(Utf8::caseInsensitiveCompare("aBc" UTF8_GREEK_SMALL_SIGMA,
                                    "AbC" UTF8_GREEK_CAPITAL_SIGMA "d"), 0);
    JT_LESS(Utf8::caseInsensitiveCompare("aBc" UTF8_GREEK_SMALL_SIGMA "d",
                                    "AbC" UTF8_GREEK_CAPITAL_TAU), 0);
    JT_EQUAL(Utf8::caseInsensitiveCompare("aBc" UTF8_GREEK_SMALL_SIGMA,
                                    "AbC" UTF8_GREEK_CAPITAL_SIGMA), 0);
    JT_GREATER(Utf8::caseInsensitiveCompare("aBc" UTF8_GREEK_SMALL_SIGMA "a",
                                      "AbC" UTF8_GREEK_CAPITAL_SIGMA), 0);
    JT_GREATER(Utf8::caseInsensitiveCompare("aBc" UTF8_GREEK_SMALL_PSI "d",
                                      "AbC" UTF8_GREEK_CAPITAL_TAU), 0);
}

void test_caseInsensitiveEqual()
{
    JT_ASSERT(Utf8::caseInsensitiveEqual("aBc" UTF8_GREEK_SMALL_SIGMA,
                                   "AbC" UTF8_GREEK_CAPITAL_SIGMA));
    JT_ASSERT(!Utf8::caseInsensitiveEqual("aBc&8q" UTF8_GREEK_SMALL_SIGMA,
                                    "AbC&8p" UTF8_GREEK_CAPITAL_SIGMA));
}

void test_caseInsensitiveLess()
{
    JT_ASSERT(!Utf8::caseInsensitiveLess("aBc" UTF8_GREEK_SMALL_SIGMA "D",
                                   "AbC" UTF8_GREEK_CAPITAL_SIGMA "d"));
    JT_ASSERT(Utf8::caseInsensitiveLess("aBc" UTF8_GREEK_SMALL_SIGMA "d",
                                  "AbC" UTF8_GREEK_CAPITAL_TAU));
}

void test_contains()
{
    JT_ASSERT(Utf8::contains("ABCDE", 'D'));
    JT_ASSERT(!Utf8::contains("ABCDE", 'F'));
}

void test_countCharacters()
{
    JT_EQUAL(Utf8::countCharacters(
                  "A" UTF8_COMBINING_RING_ABOVE "BCDE" UTF8_COMBINING_TILDE),
             5);
}

void test_countCodePoints()
{
    JT_EQUAL(Utf8::countCodePoints(
                  "A" UTF8_COMBINING_RING_ABOVE "BCDE" UTF8_COMBINING_TILDE),
             7);
}

void test_endsWith()
{
    JT_ASSERT(Utf8::endsWith("aBc" UTF8_GREEK_SMALL_SIGMA "D",
                             "C" UTF8_GREEK_CAPITAL_SIGMA "d",
                             FindFlags::CASE_INSENSITIVE));
    JT_ASSERT(!Utf8::endsWith("aBc" UTF8_GREEK_SMALL_SIGMA "D",
                              "E" UTF8_GREEK_CAPITAL_SIGMA "d",
                              FindFlags::CASE_INSENSITIVE));
    JT_ASSERT(Utf8::endsWith("aBc" UTF8_GREEK_SMALL_SIGMA "D",
                             "c" UTF8_GREEK_SMALL_SIGMA "D"));
}

//void test_escape()
//{
//    const char str[] = "ab\x01""cd\nef\x7Fgh\x80";
//    JT_EQUAL(escape(str), "ab\\x01cd\\nef\\x7Fgh\\x80");
//}

void test_findNext()
{
    auto s = std::string("abc_ghIJ_gH" UTF8_GREEK_SMALL_SIGMA "Ij_kLM_nop");
    auto r = Utf8::findNext(s, "gh" UTF8_GREEK_CAPITAL_SIGMA "ij",
                            FindFlags::CASE_INSENSITIVE);
    JT_EQUAL(std::string(r.first, r.second),
             "gH" UTF8_GREEK_SMALL_SIGMA "Ij");
    auto t = Utf8::findNext(r, UTF8_GREEK_CAPITAL_SIGMA "i",
                            FindFlags::CASE_INSENSITIVE);
    JT_EQUAL(std::string(t.first, t.second), UTF8_GREEK_SMALL_SIGMA "I");
    auto u = Utf8::findNext(r, UTF8_GREEK_CAPITAL_SIGMA "i");
    JT_ASSERT(u.first == u.second && u.second == r.second);
}

void test_findNextNewline()
{
    auto str = std::string("abc\ndef\r\nghi");
    auto s = make_pair(begin(str), end(str));
    auto r = Utf8::findNextNewline(str);
    JT_EQUAL(std::string(s.first, r.first), "abc");
    auto t = make_pair(r.second, s.second);
    r = Utf8::findNextNewline(t);
    JT_EQUAL(std::string(t.first, r.first), "def");
    t.first = r.second;
    r = Utf8::findNextNewline(t);
    JT_ASSERT(r.first == r.second);
    JT_EQUAL(std::string(t.first, r.first), "ghi");
}

void test_insert()
{
    auto str = "The " UTF8_GREEK_SMALL_OMEGA
               UTF8_COMBINING_BRIDGE_ABOVE UTF8_COMBINING_TILDE
               " and the A" UTF8_COMBINING_INVERTED_BREVE
               UTF8_COMBINING_DOT_ABOVE ".";
    auto r = Utf8::insert(Utf8::insert(str, 13, " insanely"), -2, "great ");
    JT_EQUAL(r, "The " UTF8_GREEK_SMALL_OMEGA
                 UTF8_COMBINING_BRIDGE_ABOVE UTF8_COMBINING_TILDE
                 " and the insanely great A" UTF8_COMBINING_INVERTED_BREVE
                 UTF8_COMBINING_DOT_ABOVE ".");
}

//void test_insertChar()
//{
//    auto str = "The " UTF8_GREEK_SMALL_OMEGA
//               UTF8_COMBINING_BRIDGE_ABOVE UTF8_COMBINING_TILDE
//               " and the A" UTF8_COMBINING_INVERTED_BREVE
//               UTF8_COMBINING_DOT_ABOVE ".";
//    auto r = insert(str, 5, Unicode::GreekSmallFinalSigma);
//    JT_EQUAL(r, "The " UTF8_GREEK_SMALL_OMEGA
//                UTF8_COMBINING_BRIDGE_ABOVE UTF8_COMBINING_TILDE
//                UTF8_GREEK_SMALL_FINAL_SIGMA
//                " and the A" UTF8_COMBINING_INVERTED_BREVE
//                UTF8_COMBINING_DOT_ABOVE ".");
//}
//
//void test_insertInPlace()
//{
//    auto s = std::string("The " UTF8_GREEK_SMALL_OMEGA
//                         UTF8_COMBINING_BRIDGE_ABOVE UTF8_COMBINING_TILDE
//                         " and the A" UTF8_COMBINING_INVERTED_BREVE
//                         UTF8_COMBINING_DOT_ABOVE ".");
//    insertInPlace(insertInPlace(s, 13, " insanely"), -2, "great ");
//    JT_EQUAL(s, "The " UTF8_GREEK_SMALL_OMEGA
//                 UTF8_COMBINING_BRIDGE_ABOVE UTF8_COMBINING_TILDE
//                 " and the insanely great A" UTF8_COMBINING_INVERTED_BREVE
//                 UTF8_COMBINING_DOT_ABOVE ".");
//}
//
//void test_isAlphaNumeric()
//{
//    JT_ASSERT(isAlphaNumeric("Ab1"));
//    JT_ASSERT(!isAlphaNumeric("Ab-1"));
//    JT_ASSERT(!isAlphaNumeric(""));
//    std::string s("2v" UTF8_GREEK_SMALL_OMEGA "1A");
//    JT_ASSERT(isAlphaNumeric(begin(s), end(s)));
//}
//
//void test_isValidUtf8()
//{
//    JT_ASSERT(isValidUtf8("AB\xC1\x80"));
//    JT_ASSERT(!isValidUtf8("AB\xC0\xBF"));
//}

void test_join()
{
    auto strings = std::vector<std::string>{"foo", "faa", "fii", "fee", "fuu"};
    auto result1 = Utf8::join(strings);
    JT_EQUAL(result1, "foofaafiifeefuu");
    auto result2 = Utf8::join(strings, ":-:");
    JT_EQUAL(result2, "foo:-:faa:-:fii:-:fee:-:fuu");
}

void test_lower()
{
    JT_EQUAL(Utf8::lower("aBc" UTF8_GREEK_CAPITAL_SIGMA "d12$E"),
             "abc" UTF8_GREEK_SMALL_SIGMA "d12$e");
}

//void test_nthCharacter()
//{
//    std::string str("The " UTF8_GREEK_SMALL_OMEGA
//                    UTF8_COMBINING_BRIDGE_ABOVE UTF8_COMBINING_TILDE
//                    " and the A" UTF8_COMBINING_INVERTED_BREVE
//                    UTF8_COMBINING_DOT_ABOVE ".");
//    JT_ASSERT(nthCharacter(str, 0) == begin(str));
//    JT_ASSERT(nthCharacter(str, 4) == begin(str) + 4);
//    JT_ASSERT(nthCharacter(str, 5) == begin(str) + 10);
//    JT_ASSERT(nthCharacter(str, 14) == begin(str) + 19);
//    JT_ASSERT(nthCharacter(str, 15) == begin(str) + 24);
//    JT_ASSERT(nthCharacter(str, 16) == begin(str) + 25);
//    JT_ASSERT(nthCharacter(str, 17) == begin(str) + 25);
//    JT_ASSERT(nthCharacter(str, -1) == begin(str) + 24);
//    JT_ASSERT(nthCharacter(str, -2) == begin(str) + 19);
//    JT_ASSERT(nthCharacter(str, -16) == begin(str));
//    JT_ASSERT(nthCharacter(str, -17) == begin(str));
//}
//
//void test_replace_indexes()
//{
//    auto s = "The " UTF8_GREEK_SMALL_OMEGA
//             UTF8_COMBINING_BRIDGE_ABOVE UTF8_COMBINING_TILDE
//             " and the A" UTF8_COMBINING_INVERTED_BREVE
//             UTF8_COMBINING_DOT_ABOVE ".";
//    JT_EQUAL(replace(s, 6, -3, "beats no"),
//             "The " UTF8_GREEK_SMALL_OMEGA
//             UTF8_COMBINING_BRIDGE_ABOVE UTF8_COMBINING_TILDE
//             " beats no A" UTF8_COMBINING_INVERTED_BREVE
//             UTF8_COMBINING_DOT_ABOVE ".");
//}
//
//void test_replace_string()
//{
//    auto s = "The " UTF8_GREEK_SMALL_OMEGA " and the A.";
//    JT_EQUAL(replace(s,
//                     UTF8_GREEK_SMALL_OMEGA " and",
//                     UTF8_GREEK_CAPITAL_OMEGA " or"),
//             "The " UTF8_GREEK_CAPITAL_OMEGA " or the A.");
//    JT_EQUAL(replace(s,
//                     UTF8_GREEK_CAPITAL_OMEGA " aNd",
//                     UTF8_GREEK_CAPITAL_SIGMA " or"),
//             s);
//    JT_EQUAL(replace(s,
//                     UTF8_GREEK_CAPITAL_OMEGA " aNd",
//                     UTF8_GREEK_CAPITAL_SIGMA " or",
//                     0, FindFlags::CaseInsensitive),
//             "The " UTF8_GREEK_CAPITAL_SIGMA " or the A.");
//    JT_EQUAL(replace(s, UTF8_GREEK_SMALL_OMEGA " and", ""), "The  the A.");
//    JT_EQUAL(replace(s, "", "foo"), s);
//}
//
//void test_replaceCodePoint()
//{
//    JT_EQUAL(replaceCodePoint("AB" UTF8_GREEK_SMALL_GAMMA "D",
//                              Unicode::GreekSmallGamma,
//                              Unicode::FigureSpace),
//             "AB" UTF8_FIGURE_SPACE "D");
//    JT_EQUAL(replaceCodePoint("ABCDCDECDEFGCD", 'C', '_', 3),
//             "AB_D_DE_DEFGCD");
//}
//
//void test_replaceInPlace()
//{
//    auto s = std::string("The " UTF8_GREEK_SMALL_OMEGA
//                         UTF8_COMBINING_BRIDGE_ABOVE UTF8_COMBINING_TILDE
//                         " and the A" UTF8_COMBINING_INVERTED_BREVE
//                         UTF8_COMBINING_DOT_ABOVE ".");
//    replaceInPlace(s, 6, -3, "beats no");
//    JT_EQUAL(s, "The " UTF8_GREEK_SMALL_OMEGA
//                UTF8_COMBINING_BRIDGE_ABOVE UTF8_COMBINING_TILDE
//                " beats no A" UTF8_COMBINING_INVERTED_BREVE
//                UTF8_COMBINING_DOT_ABOVE ".");
//}
//
//void test_replaceInvalidUtf8()
//{
//    auto s = "ABC\xC0\xBF" "DEF\xD0\x80\x80" "GH\xE8\x80" "I\xC8";
//    JT_EQUAL(replaceInvalidUtf8(s), "ABC??DEF\xD0\x80?GH??I?");
//}
//
//void test_replaceInvalidUtf8InPlace()
//{
//    std::string s("ABC\xC0\xBF" "DEF\xD0\x80\x80" "GH\xE8\x80" "I\xC8");
//    JT_EQUAL(replaceInvalidUtf8InPlace(s), "ABC??DEF\xD0\x80?GH??I?");
//}

void test_reverse()
{
    auto s = "The " UTF8_GREEK_SMALL_OMEGA UTF8_COMBINING_BRIDGE_ABOVE
             UTF8_COMBINING_TILDE " and the A" UTF8_COMBINING_INVERTED_BREVE
             UTF8_COMBINING_DOT_ABOVE ".";
    std::string result;
    JT_EQUAL(Utf8::reverse(s),
             ".A" UTF8_COMBINING_INVERTED_BREVE UTF8_COMBINING_DOT_ABOVE
             " eht dna " UTF8_GREEK_SMALL_OMEGA UTF8_COMBINING_BRIDGE_ABOVE
             UTF8_COMBINING_TILDE " ehT");
}

void test_split_caseInsensitive()
{
    auto parts = Utf8::split(
            ":" UTF8_GREEK_CAPITAL_OMEGA "Q:foo:"
            UTF8_GREEK_CAPITAL_OMEGA "q:faa:"
            UTF8_GREEK_SMALL_OMEGA "Q:bor:"
            UTF8_GREEK_SMALL_OMEGA "q:",
            ":" UTF8_GREEK_SMALL_OMEGA "q:",
            4,
            SplitFlags::CASE_INSENSITIVE);
    JT_EQUAL(parts.size(), 4);
    JT_EQUAL(parts[0], "");
    JT_EQUAL(parts[1], "foo");
    JT_EQUAL(parts[2], "faa");
    JT_EQUAL(parts[3], "bor:" UTF8_GREEK_SMALL_OMEGA "q:");
}

void test_split_caseInsensitive_reverse()
{
    auto parts = Utf8::split("1234ab4567AB8901aB2345", "AB", -3,
                             SplitFlags::CASE_INSENSITIVE |
                             SplitFlags::IGNORE_REMAINDER);
    JT_EQUAL(parts.size(), 2);
    JT_EQUAL(parts[0], "2345");
    JT_EQUAL(parts[1], "8901");
}

void test_split_caseSensitive_sameEncoding()
{
    auto parts = Utf8::split("123:aB:321:AB:234:AB:", ":AB:");
    JT_EQUAL(parts.size(), 3);
    JT_EQUAL(parts[0], "123:aB:321");
    JT_EQUAL(parts[1], "234");
    JT_EQUAL(parts[2], "");
}

void test_split_whitespace()
{
    auto parts = Utf8::split(" foo faa\r\n\tfee bar " UTF8_EM_SPACE "\tbor ");
    JT_EQUAL(parts.size(), 5);
    JT_EQUAL(parts[0], "foo");
    JT_EQUAL(parts[1], "faa");
    JT_EQUAL(parts[2], "fee");
    JT_EQUAL(parts[3], "bar");
    JT_EQUAL(parts[4], "bor");
}

void test_split_whitespace_backwards()
{
    auto parts = Utf8::split("haa baa ett yui ert swr", -3);
    JT_EQUAL(parts.size(), 3);
    JT_EQUAL(parts[0], "swr");
    JT_EQUAL(parts[1], "ert");
    JT_EQUAL(parts[2], "haa baa ett yui");
}

void test_splitIf()
{
    auto parts = Utf8::splitIf(
            " foo faa\r\n\tfee bar " UTF8_EM_SPACE "\tbor ",
            Unicode::isWhitespace, 0, SplitFlags::IGNORE_EMPTY);
    JT_EQUAL(parts.size(), 5);
    JT_EQUAL(parts[0], "foo");
    JT_EQUAL(parts[1], "faa");
    JT_EQUAL(parts[2], "fee");
    JT_EQUAL(parts[3], "bar");
    JT_EQUAL(parts[4], "bor");
}

void test_splitLines()
{
    auto parts = Utf8::splitLines(" foo\nfaa \r\n\tfee bar \vbor\f\rrubb");
    JT_EQUAL(parts.size(), 6);
    JT_EQUAL(parts[0], " foo");
    JT_EQUAL(parts[1], "faa ");
    JT_EQUAL(parts[2], "\tfee bar ");
    JT_EQUAL(parts[3], "bor");
    JT_EQUAL(parts[4], "");
    JT_EQUAL(parts[5], "rubb");
}

void test_startsWith()
{
    JT_ASSERT(Utf8::startsWith("qF" UTF8_GREEK_SMALL_SIGMA "aBcD",
                               "qF" UTF8_GREEK_CAPITAL_SIGMA,
                               FindFlags::CASE_INSENSITIVE));
    JT_ASSERT(!Utf8::startsWith("qF" UTF8_GREEK_SMALL_SIGMA "aBcD",
                                "qF" UTF8_GREEK_CAPITAL_SIGMA));
    JT_ASSERT(!Utf8::startsWith("qF" UTF8_GREEK_SMALL_SIGMA "aBcD",
                                "qF" UTF8_GREEK_CAPITAL_SIGMA "g",
                                FindFlags::CASE_INSENSITIVE));
}

//void test_substring()
//{
//    std::string s("ABCD");
//    JT_EQUAL(substring(s, 0), "ABCD");
//    JT_EQUAL(substring(s, 0, 5), "ABCD");
//    JT_EQUAL(substring(s, 1, 3), "BC");
//    JT_EQUAL(substring(s, 2, 2), "");
//    JT_EQUAL(substring(s, 3, 1), "");
//    JT_EQUAL(substring(s, 1, -1), "BC");
//    JT_EQUAL(substring(s, 2, -2), "");
//    JT_EQUAL(substring(s, 3, -4), "");
//    JT_EQUAL(substring(s, -3), "BCD");
//    JT_EQUAL(substring(s, -3, -1), "BC");
//    JT_EQUAL(substring(s, -2, -2), "");
//    JT_EQUAL(substring(s, -1, -3), "");
//}

void test_title()
{
    JT_EQUAL(Utf8::title("aBc " UTF8_GREEK_SMALL_SIGMA "De.fooB"),
             "Abc " UTF8_GREEK_CAPITAL_SIGMA "de.Foob");
}

//void test_toUtf8_fromLatin1()
//{
//    JT_EQUAL(toUtf8("\xC5rb\xF8ker", Encoding::Latin1),
//             UTF8_LATIN_CAPITAL_A_WITH_RING_ABOVE "rb"
//             UTF8_LATIN_SMALL_O_WITH_STROKE "ker");
//}
//
//void test_toUtf8_fromUtf8()
//{
//    JT_EQUAL(toUtf8(UTF8_LATIN_CAPITAL_A_WITH_RING_ABOVE "rb"
//                    UTF8_LATIN_SMALL_O_WITH_STROKE "ker", Encoding::Utf8),
//             UTF8_LATIN_CAPITAL_A_WITH_RING_ABOVE "rb"
//             UTF8_LATIN_SMALL_O_WITH_STROKE "ker");
//}
//
//void test_toUtf8_fromUtf16()
//{
//    JT_EQUAL(toUtf8(L"\u00C5rb\u00F8ker"),
//             UTF8_LATIN_CAPITAL_A_WITH_RING_ABOVE "rb"
//             UTF8_LATIN_SMALL_O_WITH_STROKE "ker");
//}

void test_trim()
{
    JT_EQUAL(Utf8::trim(" \n\t foo bar \f\r" UTF8_PARAGRAPH_SEPARATOR),
             "foo bar");
    JT_EQUAL(Utf8::trim(":--." UTF8_GREEK_SMALL_SIGMA "foo bar:--",
                        Unicode::isPunctuation),
             UTF8_GREEK_SMALL_SIGMA "foo bar");
    JT_EQUAL(Utf8::trim("A.BC_DFB.-GA-B",
                        [](uint32_t c){return Utf8::contains("AB.-", c);}),
             "C_DFB.-G");
}

void test_trimEnd()
{
    JT_EQUAL(Utf8::trimEnd(" \n\t foo bar \f\r" UTF8_PARAGRAPH_SEPARATOR),
             " \n\t foo bar");
    JT_EQUAL(Utf8::trimEnd(":--." UTF8_GREEK_SMALL_SIGMA "foo bar:--",
                           Unicode::isPunctuation),
             ":--." UTF8_GREEK_SMALL_SIGMA "foo bar");
}

void test_trimStart()
{
    JT_EQUAL(Utf8::trimStart(" \n\t" UTF8_PARAGRAPH_SEPARATOR " foo bar \f\r"),
             "foo bar \f\r");
    JT_EQUAL(Utf8::trimStart(":--." UTF8_GREEK_SMALL_SIGMA "foo bar:--",
                             Unicode::isPunctuation),
             UTF8_GREEK_SMALL_SIGMA "foo bar:--");
}

//void test_unescape()
//{
//    JT_EQUAL(unescape("\\u00C6\\n\\t\\\\\\x41"),
//                      UTF8_LATIN_CAPITAL_AE "\n\t\\A");
//}

void test_upper()
{
    JT_EQUAL(Utf8::upper("aBc" UTF8_GREEK_SMALL_SIGMA "D"),
             "ABC" UTF8_GREEK_CAPITAL_SIGMA "D");
}

JT_SUBTEST("Utf8",
           test_append,
           test_caseInsensitiveCompare,
           test_caseInsensitiveEqual,
           test_caseInsensitiveLess,
           test_contains,
           test_countCharacters,
           test_countCodePoints,
           test_endsWith,
//           test_escape,
           test_findNext,
           test_findNextNewline,
           test_insert,
//           test_insertChar,
//           test_insertInPlace,
//           test_isAlphaNumeric,
//           test_isValidUtf8,
           test_join,
           test_lower,
//           test_nthCharacter,
//           test_replace_indexes,
//           test_replace_string,
//           test_replaceCodePoint,
//           test_replaceInPlace,
//           test_replaceInvalidUtf8,
//           test_replaceInvalidUtf8InPlace,
           test_reverse,
           test_split_caseInsensitive,
           test_split_caseInsensitive_reverse,
           test_split_caseSensitive_sameEncoding,
           test_split_whitespace,
           test_split_whitespace_backwards,
           test_splitIf,
           test_splitLines,
           test_startsWith,
//           test_substring,
           test_title,
//           test_toUtf8_fromLatin1,
//           test_toUtf8_fromUtf8,
//           test_toUtf8_fromUtf16,
           test_trim,
           test_trimEnd,
           test_trimStart,
//           test_unescape,
           test_upper);
}
