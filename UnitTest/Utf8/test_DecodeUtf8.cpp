//****************************************************************************
// Copyright © 2013 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2013-05-13
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#include "../../Ystring/Utf8/DecodeUtf8.hpp"
#include "../../Ystring/Utf8/EncodeUtf8.hpp"

#include <JEBTest/JEBTest.hpp>

namespace {

using namespace Ystring;
using namespace Ystring::Utf8;

void testNextOk(const std::string& s, uint32_t expected)
{
    uint32_t c;
    auto it = s.cbegin();
    JT_EQUAL(nextUtf8CodePoint(c, it, s.cend()), DecoderResult::OK);
    JT_ASSERT(it == s.cend());
    JT_EQUAL(c, expected);
}

void testNextOk(const std::string& s, uint32_t expected, size_t length)
{
    uint32_t c;
    auto it = s.cbegin();
    JT_EQUAL(nextUtf8CodePoint(c, it, s.cend()), DecoderResult::OK);
    JT_ASSERT(it == s.begin() + length);
    JT_EQUAL(c, expected);
}

void testNextNotOk(const std::string& s, int expected)
{
    uint32_t c;
    auto it = s.cbegin();
    JT_EQUAL(nextUtf8CodePoint(c, it, s.cend()), expected);
    JT_ASSERT(it == s.cbegin());
}

void test_nextChar()
{
    JT_CALL(testNextOk("\x01", 0x01));
    JT_CALL(testNextOk("A", 'A'));
    JT_CALL(testNextOk("\x7F", 0x7F));
    JT_CALL(testNextOk("\xC2\x80", 0x80));
    JT_CALL(testNextOk("\xDF\xBF", 0x7FF));
    JT_CALL(testNextOk("\xFB\xBF\xBF\xBF\xBF", 0x3FFFFFF));
    JT_CALL(testNextOk("\xFD\x80\x80\x80\x80\x80", 0x40000000));
    JT_CALL(testNextOk("\xFC\x80\x80\x80\x80\x80", 0));
    JT_CALL(testNextOk("\xFD\xBF\xBF\xBF\xBF\xBF", 0x7FFFFFFF));
    JT_CALL(testNextOk("\xF4\x80\x80\x80\x80", 0x100000, 4));
    JT_CALL(testNextOk("\xD0\x80\x80", 0x400, 2));
    JT_CALL(testNextNotOk("", DecoderResult::END_OF_STRING));
    JT_CALL(testNextNotOk("\xC8", DecoderResult::INCOMPLETE));
    JT_CALL(testNextNotOk("\x80", DecoderResult::INVALID));
    JT_CALL(testNextNotOk("\x80" "A", DecoderResult::INVALID));
    JT_CALL(testNextNotOk("\xF1\x80\x80", DecoderResult::INCOMPLETE));
    JT_CALL(testNextNotOk("\xF1\x80\x80" "A", DecoderResult::INCOMPLETE));
    JT_CALL(testNextNotOk("\xFE\x80\x80\x80\x80\x80\x80", DecoderResult::INVALID));
    JT_CALL(testNextNotOk("\xFF\x80\x80\x80\x80\x80\x80\x80", DecoderResult::INVALID));
}

void testPrevNotOk(const std::string& s, unsigned expected)
{
    uint32_t c;
    auto it = s.cend();
    JT_EQUAL(prevUtf8CodePoint(c, s.cbegin(), it), expected);
    JT_ASSERT(it == s.cend());
}

void testPrevOk(const std::string& s, uint32_t expected)
{
    uint32_t c;
    auto it = s.cend();
    JT_EQUAL(prevUtf8CodePoint(c, s.cbegin(), it), DecoderResult::OK);
    JT_ASSERT(it == s.cbegin());
    JT_EQUAL(c, expected);
}

void test_prevChar()
{
    JT_CALL(testPrevOk("\xC0\xBF", 0x3F));
    JT_CALL(testPrevOk("\x01", 0x01));
    JT_CALL(testPrevOk("A", 'A'));
    JT_CALL(testPrevOk("\x7F", 0x7F));
    JT_CALL(testPrevOk("\xC2\x80", 0x80));
    JT_CALL(testPrevOk("\xDF\xBF", 0x7FF));
    JT_CALL(testPrevOk("\xFB\xBF\xBF\xBF\xBF", 0x3FFFFFF));
    JT_CALL(testPrevOk("\xFD\x80\x80\x80\x80\x80", 0x40000000));
    JT_CALL(testPrevOk("\xFC\x80\x80\x80\x80\x80", 0));
    JT_CALL(testPrevOk("\xFD\xBF\xBF\xBF\xBF\xBF", 0x7FFFFFFF));
    JT_CALL(testPrevNotOk("", DecoderResult::END_OF_STRING));
    JT_CALL(testPrevNotOk("\x80", DecoderResult::INVALID));
    JT_CALL(testPrevNotOk("A\x80", DecoderResult::INVALID));
    JT_CALL(testPrevNotOk("\xF1\x80\x80", DecoderResult::INCOMPLETE));
    JT_CALL(testPrevNotOk("\xF1\x80\x80\x80\x80", DecoderResult::INVALID));
    JT_CALL(testPrevNotOk("\xFF\x80\x80\x80\x80\x80\x80\x80", DecoderResult::INVALID));
    JT_CALL(testPrevNotOk("\xFE\x80\x80\x80\x80\x80\x80", DecoderResult::INVALID));
}

JT_SUBTEST("Utf8",
           test_nextChar,
           test_prevChar);
}
