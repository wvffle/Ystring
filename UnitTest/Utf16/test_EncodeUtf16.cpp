//****************************************************************************
// Copyright © 2013 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2013-05-13
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#include "../../Ystring/Utf16/EncodeUtf16.hpp"

#include <iterator>
#include <JEBTest/JEBTest.hpp>

namespace
{

using namespace Ystring;
using namespace Ystring::Utf16;

void test_AddUtf16LE()
{
    std::wstring s;
    addUtf16LE(std::back_inserter(s), (uint32_t)'a');
    JT_EQUAL(s.size(), 1);
    JT_EQUAL(s[0], 'a');
    s.clear();
    addUtf16LE(std::back_inserter(s), 0x10001ul);
    JT_EQUAL(s.size(), 2);
    JT_EQUAL(s[0], 0xD800);
    JT_EQUAL(s[1], 0xDC01);
}

void test_EncodeUtf16()
{
    std::string s(8, ' ');
    auto it = s.begin();
    JT_ASSERT(encodeUtf16(it, s.end(), 'A'));
    JT_EQUAL(std::distance(s.begin(), it), 2);
    JT_EQUAL(s[0], 'A');
    JT_EQUAL(s[1], '\0');
    it = s.begin();
    JT_ASSERT(encodeUtf16BE(it, s.end(), 'A'));
    JT_EQUAL(std::distance(s.begin(), it), 2);
    JT_EQUAL(s[0], '\0');
    JT_EQUAL(s[1], 'A');
    it = s.begin();
    JT_ASSERT(encodeUtf16LE(it, s.end(), 'A'));
    JT_EQUAL(std::distance(s.begin(), it), 2);
    JT_EQUAL(s[0], 'A');
    JT_EQUAL(s[1], '\0');
    JT_ASSERT(encodeUtf16(it, s.end(), 0x10000));
    JT_EQUAL(std::distance(s.begin(), it), 6);
    JT_EQUAL(s[2], 0x00);
    JT_EQUAL((uint8_t)s[3], 0xD8);
    JT_EQUAL(s[4], 0x00);
    JT_EQUAL((uint8_t)s[5], 0xDC);
}

void test_EncodeWUtf16()
{
    std::wstring s(8, ' ');
    auto it = s.begin();
    JT_ASSERT(encodeUtf16(it, s.end(), 'A'));
    JT_EQUAL(std::distance(s.begin(), it), 1);
    JT_EQUAL(s[0], 'A');
    it = s.begin();
    JT_ASSERT(encodeUtf16BE(it, s.end(), 'A'));
    JT_EQUAL(std::distance(s.begin(), it), 1);
    JT_EQUAL(s[0], 'A' << 8);
    it = s.begin();
    JT_ASSERT(encodeUtf16LE(it, s.end(), 'A'));
    JT_EQUAL(std::distance(s.begin(), it), 1);
    JT_EQUAL(s[0], 'A');
    JT_ASSERT(encodeUtf16(it, s.end(), 0x10000));
    JT_EQUAL(std::distance(s.begin(), it), 3);
    JT_EQUAL(s[1], 0xD800);
    JT_EQUAL(s[2], 0xDC00);
}

JT_SUBTEST("Utf16",
           test_AddUtf16LE,
           test_EncodeUtf16,
           test_EncodeWUtf16);
}
