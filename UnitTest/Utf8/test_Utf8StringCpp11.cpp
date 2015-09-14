//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-07-29
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#include "../../Ystring/Utf8.hpp"
#include "../Ytest/Ytest.hpp"

namespace
{
    using namespace Ystring;

    void test_toUtf8_fromUtf16_u16string()
    {
        Y_EQUAL(Utf8::toUtf8(u"A\U00010001<"),
                "A\xF0\x90\x80\x81<");
    }

    void test_toUtf8_fromUtf32_u32string()
    {
        Y_EQUAL(Utf8::toUtf8(U"A\U00010001<"),
                "A\xF0\x90\x80\x81<");
    }

    Y_SUBTEST("Utf8",
              test_toUtf8_fromUtf16_u16string,
              test_toUtf8_fromUtf32_u32string);
}
