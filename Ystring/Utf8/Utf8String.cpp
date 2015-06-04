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

using Generic::makeEncodedRange;
using Utilities::makeRange;

bool endsWith(const std::string& str,
              const std::string& cmp,
              FindFlags_t flags)
{
    return Generic::endsWith(
            makeEncodedRange(makeRange(str), Utf8Encoding()),
            makeEncodedRange(makeRange(cmp), Utf8Encoding()),
            flags);
}

std::pair<std::string::iterator, std::string::iterator> find(
        std::string& str,
        const std::string& cmp,
        FindFlags_t flags)
{
    return Generic::find(
            makeEncodedRange(makeRange(str), Utf8Encoding()),
            makeEncodedRange(makeRange(cmp), Utf8Encoding()),
            flags).getRange();
}

std::pair<std::string::const_iterator, std::string::const_iterator> find(
        const std::string& str,
        const std::string& cmp,
        FindFlags_t flags)
{
    return Generic::find(
            makeEncodedRange(makeRange(str), Utf8Encoding()),
            makeEncodedRange(makeRange(cmp), Utf8Encoding()),
            flags).getRange();
}

std::pair<std::string::iterator, std::string::iterator> find(
      std::pair<std::string::iterator, std::string::iterator> str,
      const std::string& cmp,
      FindFlags_t flags)
{
    return Generic::find(
            makeEncodedRange(makeRange(str), Utf8Encoding()),
            makeEncodedRange(makeRange(cmp), Utf8Encoding()),
            flags).getRange();
}

std::pair<std::string::const_iterator, std::string::const_iterator> find(
      std::pair<std::string::const_iterator, std::string::const_iterator> str,
      const std::string& cmp,
      FindFlags_t flags)
{
    return Generic::find(
            makeEncodedRange(makeRange(str), Utf8Encoding()),
            makeEncodedRange(makeRange(cmp), Utf8Encoding()),
            flags).getRange();
}

bool startsWith(const std::string& str,
                const std::string& cmp,
                FindFlags_t flags)
{
    return Generic::startsWith(
            makeEncodedRange(makeRange(str), Utf8Encoding()),
            makeEncodedRange(makeRange(cmp), Utf8Encoding()),
            flags);
}

}}
