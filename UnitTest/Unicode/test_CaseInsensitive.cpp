//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-06-02
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#include "Ystring/Unicode/CaseInsensitive.hpp"
#include "Ystring/Unicode/UnicodeChars.hpp"

#include <JEBTest/JEBTest.hpp>

namespace {
    using namespace Ystring::Unicode;

    static void test_equal()
    {
        CaseInsensitiveEqual op;

        JT_ASSERT(op((uint32_t) 100, (uint32_t) 100));
        JT_ASSERT(op('a', 'a'));
        JT_ASSERT(!op('a', 'b'));
        JT_ASSERT(op('a', 'A'));
        JT_ASSERT(op('*', '*'));
    }

    JT_SUBTEST("Unicode", test_equal);
}
