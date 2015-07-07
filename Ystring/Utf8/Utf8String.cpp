//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-05-31
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#include "Utf8String.hpp"

#include "Utf8Encoding.hpp"
#include "../Generic/GenericString.hpp"

namespace Ystring { namespace Utf8 {

using Generic::makeStringReference;
using Generic::makeRange;
using Generic::fromRange;

std::string& append(std::string& str, uint32_t chr)
{
    append(makeStringReference(str), chr, Utf8Encoding());
    return str;
}

int32_t caseInsensitiveCompare(const std::string& str, const std::string& cmp)
{
    return Generic::caseInsensitiveCompare(makeRange(str),
                                           makeRange(cmp),
                                           Utf8Encoding());
}

bool caseInsensitiveEqual(const std::string& str, const std::string& cmp)
{
    return Generic::caseInsensitiveEqual(makeRange(str),
                                         makeRange(cmp),
                                         Utf8Encoding());
}

bool caseInsensitiveLess(const std::string& str, const std::string& cmp)
{
    return Generic::caseInsensitiveLess(makeRange(str),
                                        makeRange(cmp),
                                        Utf8Encoding());
}

bool contains(const std::string& str, uint32_t chr)
{
    return Generic::contains(makeRange(str), chr, Utf8Encoding());
}

size_t countCharacters(const std::string& str)
{
    return Generic::countCharacters(makeRange(str), Utf8Encoding());
}

size_t countCodePoints(const std::string& str)
{
    return Generic::countCodePoints(makeRange(str), Utf8Encoding());
}

bool endsWith(const std::string& str,
              const std::string& cmp,
              FindFlags_t flags)
{
    return Generic::endsWith(
            makeRange(str),
            makeRange(cmp),
            Utf8Encoding(),
            flags);
}

StringIteratorPair findFirst(
        std::string& str,
        const std::string& cmp,
        FindFlags_t flags)
{
    return Generic::findFirst(makeRange(str), makeRange(cmp), Utf8Encoding(),
                              flags);
}

StringConstIteratorPair findFirst(
        const std::string& str,
        const std::string& cmp,
        FindFlags_t flags)
{
    return Generic::findFirst(makeRange(str), makeRange(cmp), Utf8Encoding(),
                              flags);
}

StringIteratorPair findFirst(
        std::string::iterator first,
        std::string::iterator last,
        const std::string& cmp,
        FindFlags_t flags)
{
    return Generic::findFirst(makeRange(first, last), makeRange(cmp),
                              Utf8Encoding(), flags);
}

StringConstIteratorPair findFirst(
        std::string::const_iterator first,
        std::string::const_iterator last,
        const std::string& cmp,
        FindFlags_t flags)
{
    return Generic::findFirst(makeRange(first, last), makeRange(cmp),
                              Utf8Encoding(), flags);
}

StringIteratorPair findFirstNewline(std::string& str)
{
    return Generic::findFirstNewline(makeRange(str), Utf8Encoding());
}

StringConstIteratorPair findFirstNewline(const std::string& str)
{
    return Generic::findFirstNewline(makeRange(str), Utf8Encoding());
}

StringIteratorPair findFirstNewline(
        std::string::iterator first,
        std::string::iterator last)
{
    return Generic::findFirstNewline(makeRange(first, last), Utf8Encoding());
}

StringConstIteratorPair findFirstNewline(
        std::string::const_iterator first,
        std::string::const_iterator last)
{
    return Generic::findFirstNewline(makeRange(first, last), Utf8Encoding());
}

StringIteratorPair findLast(
        std::string& str,
        const std::string& cmp,
        FindFlags_t flags)
{
    return Generic::findLast(makeRange(str), makeRange(cmp), Utf8Encoding(),
                             flags);
}

StringConstIteratorPair findLast(
        const std::string& str,
        const std::string& cmp,
        FindFlags_t flags)
{
    return Generic::findLast(makeRange(str), makeRange(cmp), Utf8Encoding(),
                             flags);
}

StringIteratorPair findLast(
        std::string::iterator first,
        std::string::iterator last,
        const std::string& cmp,
        FindFlags_t flags)
{
    return Generic::findLast(makeRange(first, last), makeRange(cmp), Utf8Encoding(),
                            flags);
}

StringConstIteratorPair findLast(
        std::string::const_iterator first,
        std::string::const_iterator last,
        const std::string& cmp,
        FindFlags_t flags)
{
    return Generic::findLast(makeRange(first, last), makeRange(cmp),
                             Utf8Encoding(), flags);
}

StringIteratorPair findLastNewline(std::string& str)
{
    return Generic::findLastNewline(makeRange(str), Utf8Encoding());
}

StringConstIteratorPair findLastNewline(const std::string& str)
{
    return Generic::findLastNewline(makeRange(str), Utf8Encoding());
}

StringIteratorPair findLastNewline(
        std::string::iterator first,
        std::string::iterator last)
{
    return Generic::findLastNewline(makeRange(first, last), Utf8Encoding());
}

StringConstIteratorPair findLastNewline(
        std::string::const_iterator first,
        std::string::const_iterator last)
{
    return Generic::findLastNewline(makeRange(first, last), Utf8Encoding());
}

std::string insert(const std::string& str, ptrdiff_t pos,
                   const std::string& sub)
{
    return Generic::insert<std::string>(makeRange(str), pos, makeRange(sub),
                                        Utf8Encoding());
}

std::string insert(const std::string& str, ptrdiff_t pos, uint32_t chr)
{
    return Generic::insert<std::string>(makeRange(str), pos, chr,
                                        Utf8Encoding());
}

bool isAlphaNumeric(const std::string& str)
{
    return isAlphaNumeric(makeRange(str), Utf8Encoding());
}

bool isAlphaNumeric(std::string::iterator first,
                    std::string::iterator last)
{
    return isAlphaNumeric(makeRange(first, last), Utf8Encoding());
}

bool isAlphaNumeric(std::string::const_iterator first,
                    std::string::const_iterator last)
{
    return isAlphaNumeric(makeRange(first, last), Utf8Encoding());
}

bool isValidUtf8(const std::string& str)
{
    return isValidUtf8(begin(str), end(str));
}

std::string join(const std::vector<std::string>& strings,
                 std::string delimiter)
{
    return delimiter.empty() ?
           Generic::join<std::string>(begin(strings), end(strings)) :
           Generic::join<std::string>(begin(strings), end(strings),
                                      makeRange(delimiter));
}

std::string lower(const std::string& str)
{
    return Generic::lower<std::string>(makeRange(str), Utf8Encoding());
}

std::string::iterator nextCharacter(std::string::iterator& first,
                                    std::string::iterator& last,
                                    size_t n)
{
    return Generic::nextCharacter(makeRange(first, last), n ,
                                  Utf8Encoding());
}

std::string::const_iterator nextCharacter(std::string::const_iterator& first,
                                          std::string::const_iterator& last,
                                          size_t n)
{
    return Generic::nextCharacter(makeRange(first, last), n,
                                  Utf8Encoding());
}

std::string::iterator nthCharacter(std::string& str, ptrdiff_t n)
{
    return Generic::nthCharacter(makeRange(str), n, Utf8Encoding());
}

std::string::const_iterator nthCharacter(const std::string& str,
                                         ptrdiff_t n)
{
    return Generic::nthCharacter(makeRange(str), n, Utf8Encoding());
}

std::string::iterator prevCharacter(std::string::iterator& first,
                                    std::string::iterator& last,
                                    size_t n)
{
    return Generic::prevCharacter(makeRange(first, last), n ,
                                  Utf8Encoding());
}

std::string::const_iterator prevCharacter(std::string::const_iterator& first,
                                          std::string::const_iterator& last,
                                          size_t n)
{
    return Generic::prevCharacter(makeRange(first, last), n,
                                  Utf8Encoding());
}

std::string replace(const std::string& str,
                    const std::string& cmp,
                    const std::string& repl,
                    size_t maxReplacements,
                    FindFlags_t flags)
{
    return Generic::replace<std::string>(makeRange(str), makeRange(cmp),
                                         makeRange(repl), Utf8Encoding(),
                                         maxReplacements, flags);
}

std::string replace(const std::string& str,
                    ptrdiff_t start,
                    ptrdiff_t end,
                    const std::string& repl)
{
    return Generic::replace<std::string>(makeRange(str), start, end,
                                         makeRange(repl), Utf8Encoding());
}

std::string reverse(const std::string& str)
{
    return Generic::reverse<std::string>(makeRange(str), Utf8Encoding());
}

std::vector<std::string> split(
        const std::string& str,
        ptrdiff_t maxParts,
        SplitFlags_t flags)
{
    return Generic::split<std::string>(
            makeRange(str), Utf8Encoding(),
            maxParts, flags);
}

std::vector<std::string> split(
        const std::string& str,
        const std::string& sep,
        ptrdiff_t maxParts,
        SplitFlags_t flags)
{
  return Generic::split<std::string>(
          makeRange(str), makeRange(sep), Utf8Encoding(), maxParts, flags);
}

std::vector<std::string> splitIf(
        const std::string& str,
        std::function<bool(uint32_t)> predicate,
        ptrdiff_t maxParts,
        SplitFlags_t flags)
{
    return Generic::splitIf<std::string>(
            makeRange(str), Utf8Encoding(), predicate, maxParts, flags);
}

std::vector<std::string> splitLines(
        const std::string& str,
        ptrdiff_t maxParts,
        SplitFlags_t flags)
{
    return Generic::splitLines<std::string>(makeRange(str), Utf8Encoding(),
                                            maxParts, flags);
}

bool startsWith(const std::string& str,
                const std::string& cmp,
                FindFlags_t flags)
{
    return Generic::startsWith(makeRange(str), makeRange(cmp),
                               Utf8Encoding(), flags);
}

std::string substring(const std::string& str,
                      ptrdiff_t start,
                      ptrdiff_t end)
{
    return Generic::substring<std::string>(makeRange(str), start, end,
                                           Utf8Encoding());
}

std::string title(const std::string& str)
{
    return Generic::title<std::string>(makeRange(str), Utf8Encoding());
}

std::string trim(const std::string& str)
{
    return fromRange<std::string>(Generic::trim(
            makeRange(str),
            Utf8Encoding(),
            Unicode::isWhitespace));
}

std::string trim(const std::string& str,
                 std::function<bool(uint32_t)> predicate)
{
    return fromRange<std::string>(Generic::trim(
            makeRange(str),
            Utf8Encoding(),
            predicate));
}

std::string trimEnd(const std::string& str)
{
    return fromRange<std::string>(Generic::trimEnd(
            makeRange(str),
            Utf8Encoding(),
            Unicode::isWhitespace));
}

std::string trimEnd(const std::string& str,
                    std::function<bool(uint32_t)> predicate)
{
    return fromRange<std::string>(Generic::trimEnd(
            makeRange(str),
            Utf8Encoding(),
            predicate));
}

std::string trimStart(const std::string& str)
{
    return fromRange<std::string>(Generic::trimStart(
            makeRange(str),
            Utf8Encoding(),
            Unicode::isWhitespace));
}


std::string trimStart(const std::string& str,
                      std::function<bool(uint32_t)> predicate)
{
    return fromRange<std::string>(Generic::trimStart(
            makeRange(str),
            Utf8Encoding(),
            predicate));
}

std::string upper(const std::string& str)
{
    return Generic::upper<std::string>(makeRange(str), Utf8Encoding());
}

}}
