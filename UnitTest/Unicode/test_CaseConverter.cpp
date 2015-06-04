//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-06-02
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#include "Ystring/Unicode/CaseConverter.hpp"
#include "Ystring/Unicode/UnicodeChars.hpp"

#include <JEBTest/JEBTest.hpp>

namespace {

    using namespace Ystring::Unicode;

    static void test_upperCase() {
        JT_EQUAL(upper('A'), 'A');
        JT_EQUAL(upper('a'), 'A');
        JT_EQUAL(upper('Z'), 'Z');
        JT_EQUAL(upper('z'), 'Z');
        JT_EQUAL(upper(':'), ':');
        JT_EQUAL(upper(','), ',');

        JT_EQUAL(upper(0x00E0), 0x00C0);
        JT_EQUAL(upper(0x00E5), 0x00C5);
        JT_EQUAL(upper(0x00F8), 0x00D8);

        JT_EQUAL(upper(0x00FF), 0x0178);

        JT_EQUAL(upper(0x0106), 0x0106);
        JT_EQUAL(upper(0x0107), 0x0106);

        JT_EQUAL(upper(0x0174), 0x0174);
        JT_EQUAL(upper(0x0175), 0x0174);

        JT_EQUAL(upper(0x01C4), 0x01C4);
        JT_EQUAL(upper(0x01C5), 0x01C4);
        JT_EQUAL(upper(0x01C6), 0x01C4);
    }

    static void test_lowerCase()
    {
        JT_EQUAL(lower('A'), 'a');
        JT_EQUAL(lower('a'), 'a');
        JT_EQUAL(lower('Z'), 'z');
        JT_EQUAL(lower('z'), 'z');
        JT_EQUAL(lower(':'), ':');
        JT_EQUAL(lower(','), ',');

        JT_EQUAL(lower(0x00C0), 0x00E0);
        JT_EQUAL(lower(0x00C5), 0x00E5);
        JT_EQUAL(lower(0x00D8), 0x00F8);
        JT_EQUAL(lower(0x0178), 0x00FF);

        JT_EQUAL(lower(0x01C4), 0x01C6);
        JT_EQUAL(lower(0x01C5), 0x01C6);
        JT_EQUAL(lower(0x01C6), 0x01C6);
    }

    static void test_titleCase()
    {
        JT_EQUAL(title('A'), 'A');
        JT_EQUAL(title('a'), 'A');
        JT_EQUAL(title('Z'), 'Z');
        JT_EQUAL(title('z'), 'Z');
        JT_EQUAL(title(':'), ':');
        JT_EQUAL(title(','), ',');

        JT_EQUAL(title(0x00E0), 0x00C0);
        JT_EQUAL(title(0x00E5), 0x00C5);
        JT_EQUAL(title(0x00F8), 0x00D8);

        JT_EQUAL(title(0x00FF), 0x0178);

        JT_EQUAL(title(0x0106), 0x0106);
        JT_EQUAL(title(0x0107), 0x0106);

        JT_EQUAL(title(0x0174), 0x0174);
        JT_EQUAL(title(0x0175), 0x0174);

        JT_EQUAL(title(0x01C4), 0x01C5);
        JT_EQUAL(title(0x01C5), 0x01C5);
        JT_EQUAL(title(0x01C6), 0x01C5);
    }

    JT_SUBTEST("Unicode", test_upperCase, test_lowerCase, test_titleCase);

}
