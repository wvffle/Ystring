//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-07-12.
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************

#include "../../Ystring/CodePage/CodePageEncoding.hpp"
#include "../../Ystring/Generic/GenericString.hpp"
#include "../../Ystring/Utf8/Utf8Chars.hpp"
#include "../../Ystring/Utf8/Utf8Encoding.hpp"
#include "../../Ystring/Utf16/Utf16Encoding.hpp"
#include "../../Ystring/Utf32/Utf32Encoding.hpp"
#include <list>
#include "../Ytest/Ytest.hpp"

namespace {

using namespace Ystring;
using namespace Ystring::Unicode;
using Ystring::Utilities::bigU32;
using Ystring::Utilities::littleU32;
using Ystring::Generic::convert;
using Ystring::Generic::makeRange;
using Ystring::Generic::makeArrayRange;

void test_Cp437_to_Utf32()
{
    char str[] = "\x01" "1A" "\x7F\xD0\xF0";
    uint32_t expected[] = {0x263A, '1', 'A', 0x2302, 0x2568, 0x2261};
    Y_EQUAL_RANGES(
            convert<std::vector<uint32_t>>(
                    makeArrayRange(str),
                    CodePage::Ibm437Encoding(),
                    Utf32::Utf32Encoding()),
            expected);
}

void test_Utf8_to_Utf32BE_as_char()
{
    char str[] = "A\xF0\x9F\x80\x80";
    uint8_t expected[] = {0, 0, 0, 65, 0, 1, 0xF0, 0};
    Y_EQUAL_RANGES(
            convert<std::vector<uint8_t>>(
                    makeArrayRange(str),
                    Utf8::Utf8Encoding(),
                    Utf32::Utf32BEEncoding()),
            expected);
}

void test_Utf8_to_Utf32LE_as_char()
{
    char str[] = "A\xF0\x9F\x80\x80";
    uint8_t expected[] = {65, 0, 0, 0, 0, 0xF0, 1, 0};
    Y_EQUAL_RANGES(
            convert<std::vector<uint8_t>>(
                    makeArrayRange(str),
                    Utf8::Utf8Encoding(),
                    Utf32::Utf32LEEncoding()),
            expected);
}

void test_Utf8_to_Utf16BE_as_char()
{
    char str[] = "A\xF0\x90\x80\x81";
    uint8_t expected[] = {0, 65, 0xD8, 0, 0xDC, 1};
    Y_EQUAL_RANGES(
            convert<std::vector<uint8_t>>(
                    makeArrayRange(str),
                    Utf8::Utf8Encoding(),
                    Utf16::Utf16BEEncoding()),
            expected);
}

void test_Utf8_to_Utf16LE_as_char()
{
    char str[] = "A\xF0\x90\x80\x81";
    uint8_t expected[] = {65, 0, 0, 0xD8, 1, 0xDC};
    Y_EQUAL_RANGES(convert<std::vector<uint8_t>>(
                   makeArrayRange(str),
                   Utf8::Utf8Encoding(),
                   Utf16::Utf16LEEncoding()),
            expected);
}

void test_Utf16_to_Utf32()
{
    uint16_t strU16[] = {0xDB01, 0xDF01, 0x1000};
    uint32_t expected[] = {0xD0701, 0x1000};
    Y_EQUAL_RANGES(convert<std::list<uint32_t>>(
                   makeArrayRange(strU16),
                   Utf16::Utf16Encoding(),
                   Utf32::Utf32Encoding()),
            expected);
}

void test_Utf16BE_as_char_to_Utf16()
{
    uint8_t str[] = {0, 65, 0xD8, 0, 0xDC, 1};
    uint16_t expected[] = {'A', 0xD800, 0xDC01};
    Y_EQUAL_RANGES(convert<std::vector<uint32_t>>(
                   makeArrayRange(str),
                   Utf16::Utf16BEEncoding(),
                   Utf16::Utf16Encoding()),
            expected);
}

void test_Utf16LE_as_char_to_Utf16()
{
    uint8_t str[] = {65, 0, 0, 0xD8, 1, 0xDC};
    uint16_t expected[] = {'A', 0xD800, 0xDC01};
    Y_EQUAL_RANGES(convert<std::wstring>(
                   makeArrayRange(str),
                   Utf16::Utf16LEEncoding(),
                   Utf16::Utf16Encoding()),
            expected);
}

void test_Utf32_to_Utf8()
{
    uint32_t strU32[] = {65, 66, LATIN_CAPITAL_A_WITH_RING_ABOVE, 0x1F000, 0};
    Y_EQUAL(convert<std::string>(makeArrayRange(strU32),
                                 Utf32::Utf32Encoding(),
                                 Utf8::Utf8Encoding()),
             "AB" UTF8_LATIN_CAPITAL_A_WITH_RING_ABOVE "\xF0\x9F\x80\x80");
}

void test_Utf32BE_to_Utf8()
{
    uint32_t strU32[] = {bigU32(0, 0, 0, 65), bigU32(0, 1, 0xF0, 0)};
    Y_EQUAL(convert<std::string>(makeArrayRange(strU32),
                                 Utf32::Utf32BEEncoding(),
                                 Utf8::Utf8Encoding()),
             "A\xF0\x9F\x80\x80");
}

void test_Utf32LE_to_Utf8()
{
    uint32_t strU32[] = {littleU32(0, 0, 0, 65), littleU32(0, 1, 0xF0, 0)};
    Y_EQUAL(convert<std::string>(makeArrayRange(strU32),
                                 Utf32::Utf32LEEncoding(),
                                 Utf8::Utf8Encoding()),
             "A\xF0\x9F\x80\x80");
}

void test_Utf32BE_as_char_to_Utf32()
{
    char str[] = {0, 0, 0, 65, 0, 1, 0, 1, 0};
    uint32_t expected[] = {'A', 0x10001};
    Y_EQUAL_RANGES(convert<std::vector<uint32_t>>(
                    makeArrayRange(str),
                    Utf32::Utf32BEEncoding(),
                    Utf32::Utf32Encoding()),
            expected);
}

void test_Utf32LE_as_char_to_Utf32()
{
    char str[] = {65, 0, 0, 0, 1, 0, 1, 0, 0};
    uint32_t expected[] = {'A', 0x10001};
    Y_EQUAL_RANGES(convert<std::vector<uint32_t>>(
                   makeArrayRange(str),
                   Utf32::Utf32LEEncoding(),
                   Utf32::Utf32Encoding()),
            expected);
}

Y_SUBTEST("Generic",
          test_Cp437_to_Utf32,
          test_Utf8_to_Utf32BE_as_char,
          test_Utf8_to_Utf32LE_as_char,
          test_Utf8_to_Utf16BE_as_char,
          test_Utf8_to_Utf16LE_as_char,
          test_Utf16_to_Utf32,
          test_Utf16BE_as_char_to_Utf16,
          test_Utf16LE_as_char_to_Utf16,
          test_Utf32_to_Utf8,
          test_Utf32BE_to_Utf8,
          test_Utf32LE_to_Utf8,
          test_Utf32BE_as_char_to_Utf32,
          test_Utf32LE_as_char_to_Utf32);
}
