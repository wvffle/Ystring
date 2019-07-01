//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-06-02.
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#include "Ystring/Unicode/CharClass.hpp"
#include "Ystring/Unicode/UnicodeChars.hpp"
#include "Ytest/Ytest.hpp"

namespace {

using namespace Ystring::Unicode;

void test_charClass()
{
    Y_EQUAL(getCharClass('\0'), CharClass::CONTROL);
    Y_EQUAL(getCharClass(' '), CharClass::SPACE_SEPARATOR);
    Y_EQUAL(getCharClass('('), CharClass::OPEN_PUNCTUATION);
    Y_EQUAL(getCharClass(')'), CharClass::CLOSE_PUNCTUATION);
    Y_EQUAL(getCharClass('-'), CharClass::DASH_PUNCTUATION);
    Y_EQUAL(getCharClass('0'), CharClass::DECIMAL_NUMBER);
    Y_EQUAL(getCharClass('A'), CharClass::UPPERCASE_LETTER);
    Y_EQUAL(getCharClass('q'), CharClass::LOWERCASE_LETTER);
    Y_EQUAL(getCharClass(LATIN_CAPITAL_AE), CharClass::UPPERCASE_LETTER);
    Y_EQUAL(getCharClass(MULTIPLICATION_SIGN), CharClass::MATH_SYMBOL);
}

Y_SUBTEST("Unicode", test_charClass);

}
