//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-07-27
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#include "Iso8859_1.hpp"

namespace Ystring { namespace Encodings
{
    CodePage makeIso8859_1()
    {
        return CodePage(Encoding::ISO_8859_1);
    }
}}
