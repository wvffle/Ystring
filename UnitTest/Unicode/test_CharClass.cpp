#include "Ystring/Unicode/CharClass.hpp"
#include "Ystring/Unicode/UnicodeChars.hpp"
#include <JEBTest/JEBTest.hpp>

namespace {

using namespace Ystring::Unicode;

void test_charClass()
{
    JT_EQUAL(charClass('\0'), CharClass::CONTROL);
    JT_EQUAL(charClass(' '), CharClass::SPACE_SEPARATOR);
    JT_EQUAL(charClass('('), CharClass::OPEN_PUNCTUATION);
    JT_EQUAL(charClass(')'), CharClass::CLOSE_PUNCTUATION);
    JT_EQUAL(charClass('-'), CharClass::DASH_PUNCTUATION);
    JT_EQUAL(charClass('0'), CharClass::DECIMAL_NUMBER);
    JT_EQUAL(charClass('A'), CharClass::UPPERCASE_LETTER);
    JT_EQUAL(charClass('q'), CharClass::LOWERCASE_LETTER);
    JT_EQUAL(charClass(LATIN_CAPITAL_AE), CharClass::UPPERCASE_LETTER);
    JT_EQUAL(charClass(MULTIPLICATION_SIGN), CharClass::MATH_SYMBOL);
}

JT_SUBTEST("Unicode", test_charClass);

}
