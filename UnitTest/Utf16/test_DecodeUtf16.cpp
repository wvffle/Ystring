//****************************************************************************
// Copyright © 2013 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2013-05-13
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#include "../../Ystring/Utf16/DecodeUtf16.hpp"

#include <iterator>
#include "../Ytest/Ytest.hpp"

namespace
{
    using namespace Ystring;
    using namespace Ystring::Utf16;

    inline void testNextUtf16LEChar(const char*& it, const char* end,
                                    uint32_t expected)
    {
        uint32_t c;
        Y_EQUAL(nextUtf16LECodePoint(c, it, end), DecoderResult::OK);
        Y_EQUAL(c, expected);
    }

    inline void testNextUtf16BEChar(const char*& it, const char* end,
                                    uint32_t expected)
    {
        uint32_t c;
        Y_EQUAL(nextUtf16BECodePoint(c, it, end), DecoderResult::OK);
        Y_EQUAL(c, expected);
    }

    void test_NextUtf16LECharacter()
    {
        uint16_t s[] = {'N', 'a', 't', 0xD7FF, 0xD800, 0xDC00, 0xDBFF,
                        0xDFFF, 0xE000};

        auto it = (const char*)std::begin(s);
        auto end = (const char*)std::end(s);
        Y_CALL(testNextUtf16LEChar(it, end, 'N'));
        Y_CALL(testNextUtf16LEChar(it, end, 'a'));
        Y_CALL(testNextUtf16LEChar(it, end, 't'));
        Y_CALL(testNextUtf16LEChar(it, end, 0xD7FF));
        Y_CALL(testNextUtf16LEChar(it, end, 0x10000));
        Y_CALL(testNextUtf16LEChar(it, end, 0x10FFFF));
        Y_CALL(testNextUtf16LEChar(it, end, 0xE000));
        Y_ASSERT(it == end);
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
        Y_CALL(testNextUtf16BEChar(it, end, 'N'));
        Y_CALL(testNextUtf16BEChar(it, end, 'a'));
        Y_CALL(testNextUtf16BEChar(it, end, 't'));
        Y_CALL(testNextUtf16BEChar(it, end, 0xD7FF));
        Y_CALL(testNextUtf16BEChar(it, end, 0x10000));
        Y_CALL(testNextUtf16BEChar(it, end, 0x10FFFF));
        Y_CALL(testNextUtf16BEChar(it, end, 0xE000));
        Y_ASSERT(it == end);
    }

    template <typename FwdIt>
    inline void testPrevUtf16LEChar(FwdIt begin, FwdIt& it, uint32_t expected)
    {
        uint32_t c;
        Y_EQUAL(prevUtf16LECodePoint(c, begin, it), DecoderResult::OK);
        Y_EQUAL(c, expected);
    }

    void test_PrevUtf16LECharacter()
    {
        uint16_t s[] = {'N', 'a', 't', 0xD7FF, 0xD800, 0xDC00, 0xDBFF,
                        0xDFFF, 0xE000};

        auto begin = std::begin(s);
        auto it = std::end(s);
        Y_CALL(testPrevUtf16LEChar(begin, it, 0xE000));
        Y_CALL(testPrevUtf16LEChar(begin, it, 0x10FFFF));
        Y_CALL(testPrevUtf16LEChar(begin, it, 0x10000));
        Y_CALL(testPrevUtf16LEChar(begin, it, 0xD7FF));
        Y_CALL(testPrevUtf16LEChar(begin, it, 't'));
        Y_CALL(testPrevUtf16LEChar(begin, it, 'a'));
        Y_CALL(testPrevUtf16LEChar(begin, it, 'N'));
        Y_ASSERT(it == begin);
    }

    Y_SUBTEST("Utf16",
              test_NextUtf16LECharacter,
              test_NextUtf16BECharacter,
              test_PrevUtf16LECharacter);
}
