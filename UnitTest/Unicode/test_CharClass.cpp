//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-06-02
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#include "../../Ystring/Unicode/CharClass.hpp"
#include "../../Ystring/Unicode/UnicodeChars.hpp"
#include <JEBTest/JEBTest.hpp>

namespace {

using namespace Ystring::Unicode;

void test_charClass()
{
    JT_EQUAL(getCharClass('\0'), CharClass::CONTROL);
    JT_EQUAL(getCharClass(' '), CharClass::SPACE_SEPARATOR);
    JT_EQUAL(getCharClass('('), CharClass::OPEN_PUNCTUATION);
    JT_EQUAL(getCharClass(')'), CharClass::CLOSE_PUNCTUATION);
    JT_EQUAL(getCharClass('-'), CharClass::DASH_PUNCTUATION);
    JT_EQUAL(getCharClass('0'), CharClass::DECIMAL_NUMBER);
    JT_EQUAL(getCharClass('A'), CharClass::UPPERCASE_LETTER);
    JT_EQUAL(getCharClass('q'), CharClass::LOWERCASE_LETTER);
    JT_EQUAL(getCharClass(LATIN_CAPITAL_AE), CharClass::UPPERCASE_LETTER);
    JT_EQUAL(getCharClass(MULTIPLICATION_SIGN), CharClass::MATH_SYMBOL);
}

JT_SUBTEST("Unicode", test_charClass);

}
