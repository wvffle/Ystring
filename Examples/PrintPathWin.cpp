//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-08-25.
//
// This file is distributed under the BSD License.
// License text is included with the source distribution.
//****************************************************************************
#include <iostream>
#include <Ystring/Utf8.hpp>

using namespace Ystring::Utf8;

int main(int argc, char* argv[])
{
    if (argc != 2)
        return 1;
    std::cout << join(split(argv[1], ";"), "\n") << "\n";
}
