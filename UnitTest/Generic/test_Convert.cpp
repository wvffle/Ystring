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
#include "../../Ystring/Utf16/Utf16Encoding.hpp"
#include "../../Ystring/Utf32/Utf32Encoding.hpp"
#include <list>
#include <JEBTest/JEBTest.hpp>

namespace {

using namespace Ystring;
using namespace Ystring::Unicode;

void test_convert_Utf16_to_Utf32()
{
    uint16_t strU16[] = {0xDB01, 0xDF01, 0x1000};
    uint32_t expected[] = {0xD0701, 0x1000};
    JT_EQUAL_RANGES(Generic::convert<std::list<uint32_t>>(
                    Generic::makeRange(strU16),
                    Utf16::Utf16Encoding(),
                    Utf32::Utf32Encoding()),
            expected);
}

void test_convert_Utf32_to_Utf8()
{
    uint32_t strU32[] = {65, 66, LATIN_CAPITAL_A_WITH_RING_ABOVE, 0x1F000, 0};
    JT_EQUAL(Generic::convert<std::string>(Generic::makeRange(strU32),
                                           Utf32::Utf32Encoding(),
                                           Utf8::Utf8Encoding()),
             "AB" UTF8_LATIN_CAPITAL_A_WITH_RING_ABOVE "\xF0\x9F\x80\x80");
}

// TODO: test from UTF-32 as char
// TODO: test to UTF-32 as char
// TODO: test from UTF-16 as char
// TODO: test to UTF-16 as char
// TODO: test from UTF-32BE
// TODO: test to UTF-32BE
// TODO: test from UTF-32LE
// TODO: test to UTF-32LE
// TODO: test from UTF-16BE
// TODO: test to UTF-16BE
// TODO: test from UTF-16LE
// TODO: test to UTF-16LE

JT_SUBTEST("Generic",
           test_convert_Utf16_to_Utf32,
           test_convert_Utf32_to_Utf8);

}
