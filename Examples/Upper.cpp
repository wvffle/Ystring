//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-07-25
//
// This file is distributed under the BSD License.
// License text is included with the source distribution.
//****************************************************************************
#include <iostream>
#include <Ystring/Utf8.hpp>

int main()
{
    std::string s = u8"Köztársaság";
    std::cout << s << " -> " << Ystring::Utf8::upper(s) << "\n";
}
