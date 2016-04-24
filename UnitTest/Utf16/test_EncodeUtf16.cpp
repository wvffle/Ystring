//****************************************************************************
// Copyright © 2013 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2013-05-13.
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#include "../../Ystring/Encodings/EncodeUtf16.hpp"

#include <iterator>
#include "../Ytest/Ytest.hpp"

namespace
{
    using namespace Ystring;
    using namespace Ystring::Encodings;

    void test_AddUtf16LE()
    {
        std::wstring s;
        addUtf16LE(std::back_inserter(s), (char32_t)'a');
        Y_EQUAL(s.size(), 1);
        Y_EQUAL(s[0], 'a');
        s.clear();
        addUtf16LE(std::back_inserter(s), 0x10001ul);
        Y_EQUAL(s.size(), 2);
        Y_EQUAL(s[0], 0xD800);
        Y_EQUAL(s[1], 0xDC01);
    }

    void test_EncodeUtf16()
    {
        std::string s(8, ' ');
        auto it = s.begin();
        Y_ASSERT(encodeUtf16(it, s.end(), 'A'));
        Y_EQUAL(std::distance(s.begin(), it), 2);
        Y_EQUAL(s[0], 'A');
        Y_EQUAL(s[1], '\0');
        it = s.begin();
        Y_ASSERT(encodeUtf16BE(it, s.end(), 'A'));
        Y_EQUAL(std::distance(s.begin(), it), 2);
        Y_EQUAL(s[0], '\0');
        Y_EQUAL(s[1], 'A');
        it = s.begin();
        Y_ASSERT(encodeUtf16LE(it, s.end(), 'A'));
        Y_EQUAL(std::distance(s.begin(), it), 2);
        Y_EQUAL(s[0], 'A');
        Y_EQUAL(s[1], '\0');
        Y_ASSERT(encodeUtf16(it, s.end(), 0x10000));
        Y_EQUAL(std::distance(s.begin(), it), 6);
        Y_EQUAL(s[2], 0x00);
        Y_EQUAL((uint8_t)s[3], 0xD8);
        Y_EQUAL(s[4], 0x00);
        Y_EQUAL((uint8_t)s[5], 0xDC);
    }

    void test_EncodeWUtf16()
    {
        std::wstring s(8, ' ');
        auto it = s.begin();
        Y_ASSERT(encodeUtf16(it, s.end(), 'A'));
        Y_EQUAL(std::distance(s.begin(), it), 1);
        Y_EQUAL(s[0], 'A');
        it = s.begin();
        Y_ASSERT(encodeUtf16BE(it, s.end(), 'A'));
        Y_EQUAL(std::distance(s.begin(), it), 1);
        Y_EQUAL(s[0], 'A' << 8);
        it = s.begin();
        Y_ASSERT(encodeUtf16LE(it, s.end(), 'A'));
        Y_EQUAL(std::distance(s.begin(), it), 1);
        Y_EQUAL(s[0], 'A');
        Y_ASSERT(encodeUtf16(it, s.end(), 0x10000));
        Y_EQUAL(std::distance(s.begin(), it), 3);
        Y_EQUAL(s[1], 0xD800);
        Y_EQUAL(s[2], 0xDC00);
    }

    Y_SUBTEST("Utf16",
              test_AddUtf16LE,
              test_EncodeUtf16,
              test_EncodeWUtf16);
}
