//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-05-31
//
// This file is distributed under the BSD License.
// License text is included with the source distribution.
//****************************************************************************
#pragna once

#include <string>
#include "../FindFlags.hpp"

namespace Ystring { namespace Utf8 {

std::pair<std::string::const_iterator, std::string::const_iterator>
    find(const std::string& str,
         const std::string& cmp,
         FindFlags_t flags = FindFlags::DEFAULTS);

}}
