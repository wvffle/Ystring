//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-06-02.
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#include "Ystring/Unicode/CaseInsensitive.hpp"
#include "Ystring/Unicode/UnicodeChars.hpp"

#include "Ytest/Ytest.hpp"

namespace {
    using namespace Ystring::Unicode;

    static void test_equal()
    {
        CaseInsensitiveEqual op;

        Y_ASSERT(op((char32_t) 100, (char32_t) 100));
        Y_ASSERT(op('a', 'a'));
        Y_ASSERT(!op('a', 'b'));
        Y_ASSERT(op('a', 'A'));
        Y_ASSERT(op('*', '*'));
    }

    Y_SUBTEST("Unicode", test_equal);
}
