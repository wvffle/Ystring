//****************************************************************************
// Copyright © 2013 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2013-05-13
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#include "../../Ystring/Utf8/EncodeUtf8.hpp"

#include <JEBTest/JEBTest.hpp>

namespace {

using namespace Ystring;
using namespace Ystring::Utf8;

void test_encode()
{
    std::string s(8, ' ');
    std::string::iterator it;
    it = s.begin();
    JT_ASSERT(encodeUtf8(it, s.end(), 'A'));
    JT_EQUAL(std::distance(s.begin(), it), 1);
    JT_EQUAL(s[0], 'A');
    JT_ASSERT(encodeUtf8(it, s.end(), 0xFFF));
    JT_EQUAL((uint8_t)s[1], 0xE0);
    JT_EQUAL((uint8_t)s[2], 0xBF);
    JT_EQUAL((uint8_t)s[3], 0xBF);
}

JT_SUBTEST("Utf8",
           test_encode);
}
