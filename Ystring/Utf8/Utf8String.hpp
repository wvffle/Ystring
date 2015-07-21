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
#include "../Encoding.hpp"
#include "../EscapeType.hpp"
#include "../FindFlags.hpp"
#include "../SplitFlags.hpp"

/** @file
  * @brief The function library for UTF-8 encoded strings.
  */

namespace Ystring { namespace Utf8 {

/** @brief The result of certain find-functions that accept mutable
  *     strings or their iterators.
  */
typedef std::pair<std::string::iterator, std::string::iterator>
        StringIteratorPair;

/** @brief The result of certain find-functions that accept immutable
  *     or their strings.
  */
typedef std::pair<std::string::const_iterator, std::string::const_iterator>
        StringConstIteratorPair;

/** @brief Adds @a codePoint encoded as UTF-8 to the end of @a str.
  */
std::string& append(std::string& str, uint32_t chr);

/** @brief Compares @a str and @a cmp, ignoring any differences in
  *     letter casing.
  *
  * @note Composed and decomposed versions of the same characters are treated
  *     as different characters (the decomposed character is typically "the
  *     "lesser" one).
  * @returns @arg < 0 if @a str is less than @a cmp
  *          @arg 0 if @a str is equal to @a cmp
  *          @arg > 0 if @a str is greater than @a cmp
  * @throw logic_error if str contains an invalid UTF-8 code point.
  */
int32_t caseInsensitiveCompare(const std::string& str,
                               const std::string& cmp);

/** @brief Returns true if the upper case versions of @a str and @a cmp
  *     are equal.
  *
  * @note Composed and decomposed versions of the same characters are treated
  *     as different characters (the decomposed character is typically "the
  *     "lesser" one).
  * @throw logic_error if str contains an invalid UTF-8 code point.
  */
bool caseInsensitiveEqual(const std::string& str, const std::string& cmp);

/** @brief Returns true if the upper case version of @a str is less
  *     than @a cmp.
  *
  * Only a quick comparison of code point values are performed. This
  * function should not be used to sort strings in alphabetical order as
  * what is alphabetical order varies between languages and cultures.
  * @throw logic_error if str contains an invalid UTF-8 code point.
  */
bool caseInsensitiveLess(const std::string& str, const std::string& cmp);

/** @brief Returns true if @a str contains code point @a chr.
  * @throw logic_error if str contains an invalid UTF-8 code point.
  */
bool contains(const std::string& str, uint32_t chr);

/** @brief Returns the number of characters in @a str.
  *
  * @note A composed character can consist of multiple code points.
  * @return the number of characters.
  * @throw logic_error if str contains an invalid UTF-8 code point.
  */
size_t countCharacters(const std::string& str);

/** @brief Returns the number of code points in @a str.
  *
  * @note A composed character can consist of multiple code points.
  * @return the number of code points.
  * @throw logic_error if str contains an invalid UTF-8 code point.
  */
size_t countCodePoints(const std::string& str);

/** @brief Returns true if @a str ends with @a cmp.
  * @note Composed and decomposed versions of the same characters are treated
  *     as different characters (the decomposed character is typically "the
  *     "lesser" one).
  */
bool endsWith(const std::string& str,
              const std::string& cmp,
              FindFlags_t flags = FindFlags::DEFAULTS);

/** @brief Returns a copy of @a str where control character etc. have been
  *     escaped.
  *
  * When escaping with backslashes the function does not use octal codes,
  * not even \\0 for value 0 as these are too easy to mis-interprete.
  */
std::string escape(const std::string& str,
                   EscapeType_t type = EscapeType::BACKSLASH);

/** @brief Returns the first substring in @a str that matches @a cmp.
  * @note Composed and decomposed versions of the same characters are treated
  *     as different characters (the decomposed character is typically "the
  *     "lesser" one).
  */
StringIteratorPair findFirst(
        std::string& str,
        const std::string& cmp,
        FindFlags_t flags = FindFlags::DEFAULTS);

/** @brief Returns the first substring in @a str that matches @a cmp.
  * @note Composed and decomposed versions of the same characters are treated
  *     as different characters (the decomposed character is typically "the
  *     "lesser" one).
  */
StringConstIteratorPair findFirst(
        const std::string& str,
        const std::string& cmp,
        FindFlags_t flags = FindFlags::DEFAULTS);

/** @brief Returns the first substring in the range from @a first to @a last
  *     that matches @a cmp.
  * @note Composed and decomposed versions of the same characters are treated
  *     as different characters (the decomposed character is typically "the
  *     "lesser" one).
  */
StringIteratorPair findFirst(
        std::string::iterator first,
        std::string::iterator last,
        const std::string& cmp,
        FindFlags_t flags = FindFlags::DEFAULTS);

/** @brief Returns the first substring in the range from @a first to @a last
  *     that matches @a cmp.
  * @note Composed and decomposed versions of the same characters are treated
  *     as different characters (the decomposed character is typically "the
  *     "lesser" one).
  */
StringConstIteratorPair findFirst(
        std::string::const_iterator first,
        std::string::const_iterator last,
        const std::string& cmp,
        FindFlags_t flags = FindFlags::DEFAULTS);

/** @brief Returns the first substring in @a str that constitutes a newline.
  *
  * The following characters are treated as newline characters:
  *   - \\n Unix
  *   - \\r Old MacOS
  *   - \\r\\n Windows
  *   - \\f Form feed
  *   - \\v Vertical tab
  *   - NEXT LINE (code point 133)
  *   - LINE SEPARATOR (code point 8232)
  *   - PARAGRAPH SEPARATOR (code point 8233)
  */
StringIteratorPair findFirstNewline(std::string& str);

/** @brief Returns the first substring in @a str that constitutes a newline.
  *
  * The following characters are treated as newline characters:
  *   - \\n Unix
  *   - \\r Old MacOS
  *   - \\r\\n Windows
  *   - \\f Form feed
  *   - \\v Vertical tab
  *   - NEXT LINE (code point 133)
  *   - LINE SEPARATOR (code point 8232)
  *   - PARAGRAPH SEPARATOR (code point 8233)
  */
StringConstIteratorPair findFirstNewline(const std::string& str);

/** @brief Returns the first substring in the range from @a first to @a last
  *     that constitutes a newline.
  *
  * The following characters are treated as newline characters:
  *   - \\n Unix
  *   - \\r Old MacOS
  *   - \\r\\n Windows
  *   - \\f Form feed
  *   - \\v Vertical tab
  *   - NEXT LINE (code point 133)
  *   - LINE SEPARATOR (code point 8232)
  *   - PARAGRAPH SEPARATOR (code point 8233)
  */
StringIteratorPair findFirstNewline(std::string::iterator first,
                                    std::string::iterator last);

/** @brief Returns the first substring in the range from @a first to @a last
  *     that constitutes a newline.
  *
  * The following characters are treated as newline characters:
  *   - \\n Unix
  *   - \\r Old MacOS
  *   - \\r\\n Windows
  *   - \\f Form feed
  *   - \\v Vertical tab
  *   - NEXT LINE (code point 133)
  *   - LINE SEPARATOR (code point 8232)
  *   - PARAGRAPH SEPARATOR (code point 8233)
  */
StringConstIteratorPair findFirstNewline(
        std::string::const_iterator first,
        std::string::const_iterator last);

/** @brief Returns the last substring in @a str that matches @a cmp.
  * @note Composed and decomposed versions of the same characters are treated
  *     as different characters (the decomposed character is typically "the
  *     "lesser" one).
  */
StringIteratorPair findLast(
        std::string& str,
        const std::string& cmp,
        FindFlags_t flags = FindFlags::DEFAULTS);

/** @brief Returns the last substring in @a str that matches @a cmp.
  * @note Composed and decomposed versions of the same characters are treated
  *     as different characters (the decomposed character is typically "the
  *     "lesser" one).
  */
StringConstIteratorPair findLast(
        const std::string& str,
        const std::string& cmp,
        FindFlags_t flags = FindFlags::DEFAULTS);

/** @brief Returns the last substring in the range from @a first to @a last
  *     that matches @a cmp.
  * @note Composed and decomposed versions of the same characters are treated
  *     as different characters (the decomposed character is typically "the
  *     "lesser" one).
  */
StringIteratorPair findLast(
      std::string::iterator first,
      std::string::iterator last,
      const std::string& cmp,
      FindFlags_t flags = FindFlags::DEFAULTS);

/** @brief Returns the last substring in the range from @a first to @a last
  *     that matches @a cmp.
  * @note Composed and decomposed versions of the same characters are treated
  *     as different characters (the decomposed character is typically "the
  *     "lesser" one).
  */
StringConstIteratorPair findLast(
      std::string::const_iterator first,
      std::string::const_iterator last,
      const std::string& cmp,
      FindFlags_t flags = FindFlags::DEFAULTS);

/** @brief Returns the last substring in @a str that constitutes a newline.
  *
  * The following characters are treated as newline characters:
  *   - \\n Unix
  *   - \\r Old MacOS
  *   - \\r\\n Windows
  *   - \\f Form feed
  *   - \\v Vertical tab
  *   - NEXT LINE (code point 133)
  *   - LINE SEPARATOR (code point 8232)
  *   - PARAGRAPH SEPARATOR (code point 8233)
  */
StringIteratorPair findLastNewline(std::string& str);

/** @brief Returns the last substring in @a str that constitutes a newline.
  *
  * The following characters are treated as newline characters:
  *   - \\n Unix
  *   - \\r Old MacOS
  *   - \\r\\n Windows
  *   - \\f Form feed
  *   - \\v Vertical tab
  *   - NEXT LINE (code point 133)
  *   - LINE SEPARATOR (code point 8232)
  *   - PARAGRAPH SEPARATOR (code point 8233)
  */
StringConstIteratorPair findLastNewline(const std::string& str);

/** @brief Returns the first substring in the range from @a first to @a last
  *     that constitutes a newline.
  *
  * The following characters are treated as newline characters:
  *   - \\n Unix
  *   - \\r Old MacOS
  *   - \\r\\n Windows
  *   - \\f Form feed
  *   - \\v Vertical tab
  *   - NEXT LINE (code point 133)
  *   - LINE SEPARATOR (code point 8232)
  *   - PARAGRAPH SEPARATOR (code point 8233)
  */
StringIteratorPair findLastNewline(std::string::iterator first,
                                   std::string::iterator last);

/** @brief Returns the first substring in the range from @a first to @a last
  *     that constitutes a newline.
  *
  * The following characters are treated as newline characters:
  *   - \\n Unix
  *   - \\r Old MacOS
  *   - \\r\\n Windows
  *   - \\f Form feed
  *   - \\v Vertical tab
  *   - NEXT LINE (code point 133)
  *   - LINE SEPARATOR (code point 8232)
  *   - PARAGRAPH SEPARATOR (code point 8233)
  */
StringConstIteratorPair findLastNewline(std::string::const_iterator first,
                                        std::string::const_iterator last);

/** @brief Inserts string @a sub into @a str at position @a pos.
  *
  * @param pos The insert position in complete characters (i.e. not bytes, not
  *     even code points if the string has decomposed characters) from the
  *     start of the string. If @a pos is negative it's from the end of the
  *     string instead.
  * @throw std::logic_error if @a str isn't a valid UTF-8 string.
  */
std::string insert(const std::string& str,
                   ptrdiff_t pos,
                   const std::string& sub);

/** @brief Inserts character @a chr into @a str at position @a pos.
  *
  * @param pos The insert position in complete characters (i.e. not bytes, not
  *     even code points if the string has decomposed characters) from the
  *     start of the string. If @a pos is negative it's from the end of the
  *     string instead.
  * @throw std::logic_error if @a str isn't a valid UTF-8 string.
  */
std::string insert(const std::string& str, ptrdiff_t pos, uint32_t chr);

/** @brief Returns true if all characters in @a str are either
  *     letters or numbers.
  * @throw std::logic_error if str contains an invalid UTF-8 code point.
  */
bool isAlphaNumeric(const std::string& str);

/** @brief Returns true if all characters in the range from @a first
  *     to @a last are either letters or numbers.
  * @throw std::logic_error if str contains an invalid UTF-8 code point.
  */
bool isAlphaNumeric(std::string::iterator first,
                    std::string::iterator last);

/** @brief Returns true if all characters in the range from @a first
  *     to @a last are either letters or numbers.
  * @throw std::logic_error if str contains an invalid UTF-8 code point.
  */
bool isAlphaNumeric(std::string::const_iterator first,
                    std::string::const_iterator last);

/** @brief Returns true if all characters in @a str are valid UTF-8.
  */
bool isValidUtf8(const std::string& str);

/** @brief Returns the concatenation of the strings in @a strings delimited
  * by @a delimiter.
  */
std::string join(const std::vector<std::string>& strings,
                 std::string delimiter = std::string());

/** @brief Returns a lower case copy of @a str.
  */
std::string lower(const std::string& str);

/** @brief Returns an iterator to the start of character number @a n
  *     starting at @a first.
  */
std::string::iterator nextCharacter(std::string::iterator& first,
                                    std::string::iterator& last,
                                    size_t n = 1);

/** @brief Returns an iterator to the start of character number @a n
  *     starting at @a first.
  */
std::string::const_iterator nextCharacter(std::string::const_iterator& first,
                                          std::string::const_iterator& last,
                                          size_t n = 1);

/** @brief Returns an iterator to the start of character number @a n
  *     from the start of string @a str.
  * @param n The number of complete characters (i.e. not bytes, not
  *     even code points if the string has decomposed characters) from the
  *     start of the string. If @a pos is negative it's from the end of the
  *     string instead.
  */
std::string::iterator nthCharacter(std::string& str, ptrdiff_t n);

/** @brief Returns an iterator to the start of character number @a n
  *     from the start of string @a str.
  * @param n The number of complete characters (i.e. not bytes, not
  *     even code points if the string has decomposed characters) from the
  *     start of the string. If @a pos is negative it's from the end of the
  *     string instead.
  */
std::string::const_iterator nthCharacter(const std::string& str,
                                         ptrdiff_t n);

/** @brief Returns an iterator to the start of character number @a n
  *     counting backwards from @a last.
  */
std::string::iterator prevCharacter(std::string::iterator& first,
                                    std::string::iterator& last,
                                    size_t n = 1);

/** @brief Returns an iterator to the start of character number @a n
  *     counting backwards from @a last.
  */
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
                    ptrdiff_t maxReplacements = 0,
                    FindFlags_t flags = FindFlags::DEFAULTS);

std::string replace(const std::string& str,
                    ptrdiff_t start,
                    ptrdiff_t end,
                    const std::string& repl);

/** @brief Returns a copy of @a str with instances of @a from replaced
  *      with @a to.
  *
  * @param fromChar The character to replace
  * @param toChar The replacement
  * @param maxReplacement The maximum number of replacements that will be
  *     performed. All  instances of @a from are replaced if the value is 0.
  *     If it is negative at most abs(maxReplacements) will be made, starting
  *     at the end of the string.
  */
std::string replaceCodePoint(const std::string& s,
                             uint32_t from,
                             uint32_t to,
                             ptrdiff_t maxReplacements = 0);

std::string replaceInvalidUtf8(const std::string& str, uint32_t chr = '?');

std::string& replaceInvalidUtf8InPlace(std::string& str, char chr = '?');

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
std::string toUtf8(uint32_t chr);

/** @brief Returns an UTF-8 encoded string equivalent to @a str.
  *
  *  @param str The string to convert from.
  *  @param encoding The encoding of @a str.
  *  @throws logic_error if str contains any characters that aren't encoded
  *     according to @a encoding, or if @a encoding isn't an 8-bit encoding.
  */
std::string toUtf8(const std::string& str, Encoding_t encoding);

/** @brief Returns an UTF-8 encoded string equivalent to @a str.
  *
  *  @param str The string to convert from.
  *  @param encoding The encoding of @a str.
  *  @throws logic_error if str contains any characters that aren't encoded
  *     according to @a encoding, or if @a encoding isn't a 16-bit encoding.
  */
std::string toUtf8(const std::wstring& str,
                   Encoding_t encoding = Encoding::UTF_16);

std::string trim(const std::string& str);

std::string trim(const std::string& str,
                 std::function<bool(uint32_t)> predicate);

std::string trimEnd(const std::string& str);

std::string trimEnd(const std::string& str,
                    std::function<bool(uint32_t)> predicate);

std::string trimStart(const std::string& str);

std::string trimStart(const std::string& str,
                      std::function<bool(uint32_t)> predicate);

/** @brief Returns a copy of @a str where all escape sequences have been
  *     translated to the characters they represent.
  * @throws logic_error if @a str contains an invalid escape sequence.
  */
std::string unescape(const std::string& str,
                     EscapeType_t type = EscapeType::BACKSLASH);

std::string upper(const std::string& str);

}}
