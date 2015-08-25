//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-06-02
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#include "../../Ystring/Unicode/CharMap.hpp"

#include <type_traits>
#include "../Ytest/Ytest.hpp"

namespace {

    using namespace Ystring::Unicode;

    CompactCharMapping CompactLowerCaseMappings[] =
    {
        {0x000040, 0x00000020, 0x07FFFFFE, 0xF8000001},
        {0x0000C0, 0x00000020, 0x7F7FFFFF, 0x80800000},
        {0x000160, 0x00000001, 0x2A555555, 0xD4AAAAAA},
        {0x000200, 0x00000001, 0x55555555, 0xAAAAAAAA}
    };

    CharMapping LowerCaseMappings[] =
    {
        {0x000178, 0x0000FF},
        {0x000220, 0x00019E}
    };

    static void test_Get()
    {
        CharMap map(
                CompactLowerCaseMappings,
                std::extent<decltype(CompactLowerCaseMappings), 0>::value,
                LowerCaseMappings,
                std::extent<decltype(LowerCaseMappings), 0>::value);
        Y_EQUAL(map.get('G'), 'g');
        Y_EQUAL(map.get('g'), 'g');
        Y_EQUAL(map.get('-'), '-');
        Y_EQUAL(map.get(0xC0), 0xE0);
        Y_EQUAL(map.get(0xE3), 0xE3);
        Y_EQUAL(map.get(0xFF), 0xFF);
        Y_EQUAL(map.get(0x178), 0xFF);
        Y_EQUAL(map.get(0x200), 0x201);
        Y_EQUAL(map.get(0x220), 0x19E);
    }

    Y_SUBTEST("Unicode", test_Get);

}
