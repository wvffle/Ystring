//****************************************************************************
// Copyright © 2013 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2013-05-13
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#include "../../Ystring/Utf16/DecodeUtf16.hpp"

#include <iterator>
#include <JEBTest/JEBTest.hpp>

namespace
{

using namespace Ystring;
using namespace Ystring::Utf16;

inline void testNextUtf16LEChar(const char*& it, const char* end, uint32_t expected)
{
    uint32_t c;
    JT_EQUAL(nextUtf16LECodePoint(c, it, end), DecoderResult::OK);
    JT_EQUAL(c, expected);
}

inline void testNextUtf16BEChar(const char*& it, const char* end, uint32_t expected)
{
    uint32_t c;
    JT_EQUAL(nextUtf16BECodePoint(c, it, end), DecoderResult::OK);
    JT_EQUAL(c, expected);
}

void test_NextUtf16LECharacter()
{
    uint16_t s[] = {'N', 'a', 't', 0xD7FF, 0xD800, 0xDC00, 0xDBFF, 0xDFFF, 0xE000};

    auto it = (const char*)std::begin(s);
    auto end = (const char*)std::end(s);
    JT_CALL(testNextUtf16LEChar(it, end, 'N'));
    JT_CALL(testNextUtf16LEChar(it, end, 'a'));
    JT_CALL(testNextUtf16LEChar(it, end, 't'));
    JT_CALL(testNextUtf16LEChar(it, end, 0xD7FF));
    JT_CALL(testNextUtf16LEChar(it, end, 0x10000));
    JT_CALL(testNextUtf16LEChar(it, end, 0x10FFFF));
    JT_CALL(testNextUtf16LEChar(it, end, 0xE000));
    JT_ASSERT(it == end);
}

void test_NextUtf16BECharacter()
{
    unsigned char s[] = {0, 'N',
                         0, 'a',
                         0, 't',
                         0xD7, 0xFF,
                         0xD8, 0x00, 0xDC, 0x00,
                         0xDB, 0xFF, 0xDF, 0xFF,
                         0xE0, 0x00};
    auto it = (const char*)std::begin(s);
    auto end = (const char*)std::end(s);
    JT_CALL(testNextUtf16BEChar(it, end, 'N'));
    JT_CALL(testNextUtf16BEChar(it, end, 'a'));
    JT_CALL(testNextUtf16BEChar(it, end, 't'));
    JT_CALL(testNextUtf16BEChar(it, end, 0xD7FF));
    JT_CALL(testNextUtf16BEChar(it, end, 0x10000));
    JT_CALL(testNextUtf16BEChar(it, end, 0x10FFFF));
    JT_CALL(testNextUtf16BEChar(it, end, 0xE000));
    JT_ASSERT(it == end);
}

template <typename FwdIt>
inline void testPrevUtf16LEChar(FwdIt begin, FwdIt& it, uint32_t expected)
{
    uint32_t c;
    JT_EQUAL(prevUtf16LECodePoint(c, begin, it), DecoderResult::OK);
    JT_EQUAL(c, expected);
}

void test_PrevUtf16LECharacter()
{
    uint16_t s[] = {'N', 'a', 't', 0xD7FF, 0xD800, 0xDC00, 0xDBFF, 0xDFFF, 0xE000};

    auto begin = std::begin(s);
    auto it = std::end(s);
    JT_CALL(testPrevUtf16LEChar(begin, it, 0xE000));
    JT_CALL(testPrevUtf16LEChar(begin, it, 0x10FFFF));
    JT_CALL(testPrevUtf16LEChar(begin, it, 0x10000));
    JT_CALL(testPrevUtf16LEChar(begin, it, 0xD7FF));
    JT_CALL(testPrevUtf16LEChar(begin, it, 't'));
    JT_CALL(testPrevUtf16LEChar(begin, it, 'a'));
    JT_CALL(testPrevUtf16LEChar(begin, it, 'N'));
    JT_ASSERT(it == begin);
}

JT_SUBTEST("Utf16",
           test_NextUtf16LECharacter,
           test_NextUtf16BECharacter,
           test_PrevUtf16LECharacter);
}
