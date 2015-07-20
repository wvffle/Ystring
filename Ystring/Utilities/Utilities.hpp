//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 20.07.15
//
// This file is distributed under the BSD License.
// License text is included with the source distribution.
//****************************************************************************
#pragma once

namespace Ystring { namespace Utilities {

template <typename Char>
Char toCharDigit(Char c)
{
    return c + (c < 0xA ? '0' : 'A' - 10);
}

}}
