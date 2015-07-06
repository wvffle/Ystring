//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-05-31
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#pragma once

#include <cstdint>
#include <functional>
#include <string>
#include <vector>
#include "../FindFlags.hpp"
#include "../SplitFlags.hpp"

namespace Ystring { namespace Utf8 {

typedef std::pair<std::string::iterator, std::string::iterator>
        StringIteratorPair;

typedef std::pair<std::string::const_iterator, std::string::const_iterator>
        StringConstIteratorPair;

/** @brief Adds @a codePoint encoded as UTF-8 to the end of@a str.
  */
std::string& append(std::string& str, uint32_t chr);

/** @brief Compares @a str and @a cmp, ignoring any differences in
  *     letter casing.
  *  @returns @arg < 0 if @a str is less than @a cmp
  *           @arg 0 if @a str is equal to @a cmp
  *           @arg > 0 if @a str is greater than @a cmp
  */
int32_t caseInsensitiveCompare(const std::string& str,
                               const std::string& cmp);

/** @brief Returns true if the upper case versions of @a str and @a cmp
  *     are equal.
  */
bool caseInsensitiveEqual(const std::string& str, const std::string& cmp);

/** @brief Returns true if the upper case version of @a str is less than
  *     @a cmp.
  *
  * Only a quick comparison of code point values are performed. This
  * function should not be used to sort strings in alphabetical order as
  * what is alphabetical order varies betweem languages and cultures.
  */
bool caseInsensitiveLess(const std::string& str, const std::string& cmp);

/** @brief Returns true if @a str contains character (code point) @a chr.
  */
bool contains(const std::string& str, uint32_t chr);

/** @brief Returns the number of characters in @a str.
  *
  * @note A composed character can consist of multiple code points.
  * @return the number of characters.
  * @throw runtime_error if str contains an invalid UTF-8 code point.
  */
size_t countCharacters(const std::string& str);

/** @brief Returns the number of code points in @a str.
  *
  * @note A composed character can consist of multiple code points.
  * @return the number of code points.
  * @throw runtime_error if str contains an invalid UTF-8 code point.
  */
size_t countCodePoints(const std::string& str);

/** @brief Returns true if @a str ends with @a cmp.
  */
bool endsWith(const std::string& str,
              const std::string& cmp,
              FindFlags_t flags = FindFlags::DEFAULTS);

// std::string escape(const std::string& str);

StringIteratorPair findLast(
        std::string& str,
        const std::string& cmp,
        FindFlags_t flags = FindFlags::DEFAULTS);

StringConstIteratorPair findLast(
        const std::string& str,
        const std::string& cmp,
        FindFlags_t flags = FindFlags::DEFAULTS);

StringIteratorPair findLast(
      std::string::iterator first,
      std::string::iterator last,
      const std::string& cmp,
      FindFlags_t flags = FindFlags::DEFAULTS);

StringConstIteratorPair findLast(
      std::string::const_iterator first,
      std::string::const_iterator last,
      const std::string& cmp,
      FindFlags_t flags = FindFlags::DEFAULTS);

StringIteratorPair findLastNewline(std::string& str);

StringConstIteratorPair findLastNewline(const std::string& str);

StringIteratorPair findLastNewline(std::string::iterator first,
                                   std::string::iterator last);

StringConstIteratorPair findLastNewline(StringConstIteratorPair str);

StringIteratorPair findNext(
        std::string& str,
        const std::string& cmp,
        FindFlags_t flags = FindFlags::DEFAULTS);

StringConstIteratorPair findNext(
        const std::string& str,
        const std::string& cmp,
        FindFlags_t flags = FindFlags::DEFAULTS);

StringIteratorPair findNext(
        std::string::iterator first,
        std::string::iterator last,
        const std::string& cmp,
        FindFlags_t flags = FindFlags::DEFAULTS);

StringConstIteratorPair findNext(
        std::string::const_iterator first,
        std::string::const_iterator last,
        const std::string& cmp,
        FindFlags_t flags = FindFlags::DEFAULTS);

StringIteratorPair findNextNewline(std::string& str);

StringConstIteratorPair findNextNewline(const std::string& str);

StringIteratorPair findNextNewline(std::string::iterator first,
                                   std::string::iterator last);

StringConstIteratorPair findNextNewline(
        std::string::const_iterator first,
        std::string::const_iterator last);

std::string insert(const std::string& str,
                   ptrdiff_t pos,
                   const std::string& sub);

std::string insert(const std::string& str, ptrdiff_t pos, uint32_t chr);

bool isAlphaNumeric(const std::string& str);
bool isAlphaNumeric(std::string::iterator first,
                    std::string::iterator last);
bool isAlphaNumeric(std::string::const_iterator first,
                    std::string::const_iterator last);

/** @brief Returns true if all characters in @a str are valid UTF-8.
  */
bool isValidUtf8(const std::string& str);

std::string join(const std::vector<std::string>& strings,
                 std::string delimiter = std::string());

std::string lower(const std::string& str);

std::string::iterator nextCharacter(std::string::iterator& first,
                                    std::string::iterator& last,
                                    size_t n = 1);

std::string::const_iterator nextCharacter(std::string::const_iterator& first,
                                          std::string::const_iterator& last,
                                          size_t n = 1);

std::string::iterator nthCharacter(std::string& str, ptrdiff_t n);

std::string::const_iterator nthCharacter(const std::string& str,
                                         ptrdiff_t n);

std::string::iterator prevCharacter(std::string::iterator& first,
                                    std::string::iterator& last,
                                    size_t n = 1);

std::string::const_iterator prevCharacter(std::string::const_iterator& first,
                                          std::string::const_iterator& last,
                                          size_t n = 1);

/** @brief Returns a copy of @a str where instances of @a from are replaced
  *      with @a to.
  *
  * @param max The maximum number of replacements that will be performed. All
  *      instances of @a from are replaced if 0.
  */
std::string replace(const std::string& str,
                    const std::string& from,
                    const std::string& to,
                    size_t max = 0,
                    FindFlags_t flags = FindFlags::DEFAULTS);

/** @brief Returns a copy of @a str with instances of @a fromChar replaced
  *      with @a toChar.
  *
  *  @param fromChar The character to replace
  *  @param toChar The replacement
  *  @param max The maximum number of replacements that will be performed. All
  *      instances of @a from are replaced if 0.
  */
// std::string replaceCodePoint(const std::string& s,
//                              uint32_t fromChar,
//                              uint32_t toChar,
//                              size_t max = 0);

std::string replace(const std::string& str,
                    ptrdiff_t start,
                    ptrdiff_t end,
                    const std::string& repl);

// std::string replaceInvalidUtf8(const std::string& str, uint32_t chr = '?');

// std::string& replaceInvalidUtf8InPlace(std::string& str, char chr = '?');

/** @brief Returns a reversed copy of @a str.
  *
  * Characters with combining marks are left intact.
  */
std::string reverse(const std::string& str);

std::vector<std::string> split(
        const std::string& str,
        ptrdiff_t maxParts = 0,
        SplitFlags_t flags = SplitFlags::IGNORE_EMPTY);

std::vector<std::string> split(
        const std::string& str,
        const std::string& sep,
        ptrdiff_t maxParts = 0,
        SplitFlags_t flags = SplitFlags::DEFAULTS);

 std::vector<std::string> splitIf(
         const std::string& str,
         std::function<bool(uint32_t)> predicate,
         ptrdiff_t maxParts = 0,
         SplitFlags_t flags = SplitFlags::DEFAULTS);

 std::vector<std::string> splitLines(
         const std::string& str,
         ptrdiff_t maxParts = 0,
         SplitFlags_t flags = SplitFlags::DEFAULTS);

bool startsWith(const std::string& str,
                const std::string& cmp,
                FindFlags_t flags = FindFlags::DEFAULTS);

std::string substring(const std::string& str,
                      ptrdiff_t startIndex,
                      ptrdiff_t endIndex = PTRDIFF_MAX);

std::string title(const std::string& str);

/** @brief Returns a UTF-8 encoded string representing @a chr
  */
// std::string toUtf8(uint32_t chr);

/** @brief Returns the UTF-8 encoded string that is equivalent to @a str.
  *
  *  @param str The string to convert from.
  *  @param encoding The encoding of @a str.
  *  @throws runtime_error if str contains any characters that aren't encoded
  *     according to @a encoding, or if @a encoding isn't an 8-bit encoding.
  */
// std::string toUtf8(const std::string& str, Encoding_t encoding);

/** @brief Returns the UTF-8 encoded string that is equivalent to @a str.
  *
  *  @param str The string to convert from.
  *  @param encoding The encoding of @a str.
  *  @throws runtime_error if str contains any characters that aren't encoded
  *     according to @a encoding, or if @a encoding isn't a 16-bit encoding.
  */
// std::string toUtf8(const std::wstring& str,
//                    Encoding_t encoding = Encoding::Utf16);

std::string trim(const std::string& str);

std::string trim(const std::string& str,
                 std::function<bool(uint32_t)> predicate);

std::string trimEnd(const std::string& str);

std::string trimEnd(const std::string& str,
                    std::function<bool(uint32_t)> predicate);

std::string trimStart(const std::string& str);

std::string trimStart(const std::string& str,
                      std::function<bool(uint32_t)> predicate);

// std::string unescape(const std::string& str);

std::string upper(const std::string& str);

}}
