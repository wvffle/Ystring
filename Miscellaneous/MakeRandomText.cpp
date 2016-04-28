//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-09-04.
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#include <iostream>
#include <vector>
#include "../Ystring/Utf8.hpp"
#include "Random.hpp"

using namespace Ystring;

typedef Ydebug::RandomIntGenerator<char32_t> RandomCodePointGenerator;

const char32_t ASCII_MAX = 126 + 2 - 32;
const char32_t LATIN1_MAX = 255 + 2 - 64;
const char32_t LETTER_MAX = 0x2FF + 2 - 64;

char32_t getCharValue(char32_t value)
{
    value %= LETTER_MAX;
    if (value == 0)
        return '\t';
    if (value == 1)
        return '\n';
    if (value <= ASCII_MAX)
        return (value - 2) + 32;
    return (value - 95) + 160;
}

char32_t makeChar(RandomCodePointGenerator& rcpg)
{
    return getCharValue(rcpg.generate());
}

std::string createString(size_t length, RandomCodePointGenerator& rcpg)
{
    std::string s;
    for (size_t i = 0; i < length; ++i)
        Utf8::append(s, getCharValue(rcpg.generate()));
    return s;
}

std::string createAsciiString(size_t length)
{
    RandomCodePointGenerator rcpg(0, ASCII_MAX);
    return createString(length, rcpg);
}

std::string createLatin1String(size_t length)
{
    RandomCodePointGenerator rcpg(0, LATIN1_MAX);
    return createString(length, rcpg);
}

std::string createString(size_t length)
{
    RandomCodePointGenerator rcpg(0, LETTER_MAX);
    return createString(length, rcpg);
}

int main(int argc, char* argv[])
{
    std::cout << createString(10000) << "\n";
    return 0;
}
