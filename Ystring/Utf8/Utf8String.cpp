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
#include "../Unicode/UnicodePredicates.hpp"

namespace Ystring { namespace Utf8 {

using Generic::makeStringReference;
using Utilities::makeRange;
using Utilities::fromRange;

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

std::pair<std::string::iterator, std::string::iterator> find(
        std::string& str,
        const std::string& cmp,
        FindFlags_t flags)
{
    return Generic::find(
            makeRange(str), makeRange(cmp), Utf8Encoding(),
            flags);
}

std::pair<std::string::const_iterator, std::string::const_iterator> find(
        const std::string& str,
        const std::string& cmp,
        FindFlags_t flags)
{
    return Generic::find(makeRange(str), makeRange(cmp), Utf8Encoding(),
                         flags);
}

std::pair<std::string::iterator, std::string::iterator> find(
      std::pair<std::string::iterator, std::string::iterator> str,
      const std::string& cmp,
      FindFlags_t flags)
{
    return Generic::find(makeRange(str), makeRange(cmp), Utf8Encoding(),
                         flags);
}

std::pair<std::string::const_iterator, std::string::const_iterator> find(
      std::pair<std::string::const_iterator, std::string::const_iterator> str,
      const std::string& cmp,
      FindFlags_t flags)
{
    return Generic::find(makeRange(str), makeRange(cmp), Utf8Encoding(),
                         flags);
}

std::string insert(const std::string& str, int pos,
                   const std::string& sub)
{
    return Generic::insert<std::string>(makeRange(str), pos, makeRange(sub),
                                        Utf8Encoding());
//    auto it = nthCharacter(str, pos);
//    std::string result(begin(str), it);
//    result.append(sub);
//    result.append(it, end(str));
//    return result;
}

//std::string insert(const std::string& str, int pos, uint32_t chr)
//{
//    auto it = nthCharacter(str, pos);
//    std::string result(begin(str), it);
//    append(result, chr);
//    result.append(it, end(str));
//    return result;
//}

//std::string& insertInPlace(std::string& str, int pos,
//                           const std::string& sub)
//{
//    str.insert(nthCharacter(str, pos), begin(sub), end(sub));
//    return str;
//}

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

std::string reverse(const std::string& str)
{
    return Generic::reverse<std::string>(makeRange(str), Utf8Encoding());
}

std::vector<std::string> split(
        const std::string& str,
        int maxParts,
        SplitFlags_t flags)
{
    return Generic::split<std::string>(
            makeRange(str), Utf8Encoding(),
            maxParts, flags);
}

std::vector<std::string> split(
        const std::string& str,
        const std::string& sep,
        size_t maxParts,
        SplitFlags_t flags)
{
  return Generic::split<std::string>(
          makeRange(str), makeRange(sep), Utf8Encoding(), maxParts, flags);
}

std::vector<std::string> splitIf(
        const std::string& str,
        std::function<bool(uint32_t)> predicate,
        size_t maxParts,
        SplitFlags_t flags)
{
    return Generic::splitIf<std::string>(
            makeRange(str), Utf8Encoding(), predicate, maxParts, flags);
}

std::vector<std::string> splitLines(
        const std::string& str,
        size_t maxParts,
        SplitFlags_t flags)
{
    return Generic::splitLines<std::string>(makeRange(str), Utf8Encoding(),
                                            maxParts, flags);
}

bool startsWith(const std::string& str,
                const std::string& cmp,
                FindFlags_t flags)
{
    return Generic::startsWith(makeRange(str), makeRange(cmp), Utf8Encoding(),
                               flags);
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
