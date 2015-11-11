//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-11-03
//
// This file is distributed under the BSD License.
// License text is included with the source distribution.
//****************************************************************************
#include "../../Ystring/Conversion/Converter.hpp"
#include "../Ytest/Ytest.hpp"

using namespace Ystring;

namespace {

    void test_Utf8_to_Utf16()
    {
        Conversion::Converter converter(Encoding::UTF_8, Encoding::UTF_16);
        std::string s8 = "ABCD";
        std::u16string s16;
        converter.convert(s8.data(), s8.size(), s16);
        Y_EQUAL(s16, u"ABCD");
    }

    Y_SUBTEST("Conversion", test_Utf8_to_Utf16);
}
