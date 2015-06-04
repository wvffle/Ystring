//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-05-31
//
// This file is distributed under the BSD License.
// License text is included with the source distribution.
//****************************************************************************
#include "Utf8String.hpp"

#include "Utf8Encoding.hpp"
#include "../Generic/GenericString.hpp"

namespace Ystring { namespace Utf8 {

std::pair<std::string::const_iterator, std::string::const_iterator>
    find(const std::string& str,
         const std::string& cmp,
         FindFlags_t flags)
{
    return Generic::find(
            Generic::makeEncodedRange(Utilities::makeRange(str),
                                      Utf8Encoding()),
            Generic::makeEncodedRange(Utilities::makeRange(cmp),
                                      Utf8Encoding()),
            flags).getRange();
}

}}
