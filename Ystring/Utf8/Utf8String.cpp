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

using Generic::makeEncodedRange;
using Utilities::makeRange;
using Utilities::fromRange;

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

std::string join(const std::vector<std::string>& strings,
                 std::string delimiter)
{
    return delimiter.empty() ?
           Generic::join<std::string>(begin(strings), end(strings)) :
           Generic::join<std::string>(begin(strings), end(strings),
                                      Utilities::makeRange(delimiter));
}

std::string lower(const std::string& str)
{
    return Generic::lower<std::string>(makeRange(str), Utf8Encoding());
}

std::vector<std::string> split(
        const std::string& str,
        size_t maxParts,
        SplitFlags_t flags)
{
    return Generic::split<std::string>(
            Utilities::makeRange(str), Utf8Encoding(),
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
            Utilities::makeRange(str),
            Utf8Encoding(),
            Unicode::isWhitespace));
}

std::string trim(const std::string& str,
                 std::function<bool(uint32_t)> predicate)
{
    return fromRange<std::string>(Generic::trim(
            Utilities::makeRange(str),
            Utf8Encoding(),
            predicate));
}

std::string trimEnd(const std::string& str)
{
    return fromRange<std::string>(Generic::trimEnd(
            Utilities::makeRange(str),
            Utf8Encoding(),
            Unicode::isWhitespace));
}

std::string trimEnd(const std::string& str,
                    std::function<bool(uint32_t)> predicate)
{
    return fromRange<std::string>(Generic::trimEnd(
            Utilities::makeRange(str),
            Utf8Encoding(),
            predicate));
}

std::string trimStart(const std::string& str)
{
    return fromRange<std::string>(Generic::trimStart(
            Utilities::makeRange(str),
            Utf8Encoding(),
            Unicode::isWhitespace));
}


std::string trimStart(const std::string& str,
                      std::function<bool(uint32_t)> predicate)
{
    return fromRange<std::string>(Generic::trimStart(
            Utilities::makeRange(str),
            Utf8Encoding(),
            predicate));
}

std::string upper(const std::string& str)
{
    return Generic::upper<std::string>(makeRange(str), Utf8Encoding());
}

}}
