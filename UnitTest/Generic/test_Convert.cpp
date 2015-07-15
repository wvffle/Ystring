//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 12.07.15
//
// This file is distributed under the BSD License.
// License text is included with the source distribution.
//****************************************************************************

#include "../../Ystring/Generic/GenericString.hpp"
#include "../../Ystring/Unicode/UnicodeChars.hpp"
#include "../../Ystring/Utf8/Utf8Chars.hpp"
#include "../../Ystring/Utf8/Utf8Encoding.hpp"
#include "../../Ystring/Utf32/DecodeUtf32.hpp"
#include <JEBTest/JEBTest.hpp>
#include <Ystring/Utf32/Utf32Encoding.hpp>

namespace {

using namespace Ystring;
using namespace Ystring::Unicode;

void test_convert_Utf32_Utf8()
{
    uint32_t strU32[] = {65, 66, LATIN_CAPITAL_A_WITH_RING_ABOVE, 0x1F000, 0};
    JT_EQUAL(Generic::convert<std::string>(Generic::makeRange(strU32),
                                           Utf32::Utf32Encoding(),
                                           Utf8::Utf8Encoding()),
             "AB" UTF8_LATIN_CAPITAL_A_WITH_RING_ABOVE "\xF0\x9F\x80\x80");
}

JT_SUBTEST("Generic", test_convert_Utf32_Utf8);

}
