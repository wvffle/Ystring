//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-06-02.
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#include "../../src/Ystring/Unicode/CaseConverter.hpp"
#include "../../include/Ystring/Unicode/UnicodeChars.hpp"

#include "../Ytest/Ytest.hpp"

namespace {

    using namespace Ystring::Unicode;

    static void test_upperCase() {
        Y_EQUAL(upper('A'), 'A');
        Y_EQUAL(upper('a'), 'A');
        Y_EQUAL(upper('Z'), 'Z');
        Y_EQUAL(upper('z'), 'Z');
        Y_EQUAL(upper(':'), ':');
        Y_EQUAL(upper(','), ',');

        Y_EQUAL(upper(0x00E0), 0x00C0);
        Y_EQUAL(upper(0x00E5), 0x00C5);
        Y_EQUAL(upper(0x00F8), 0x00D8);

        Y_EQUAL(upper(0x00FF), 0x0178);

        Y_EQUAL(upper(0x0106), 0x0106);
        Y_EQUAL(upper(0x0107), 0x0106);

        Y_EQUAL(upper(0x0174), 0x0174);
        Y_EQUAL(upper(0x0175), 0x0174);

        Y_EQUAL(upper(0x01C4), 0x01C4);
        Y_EQUAL(upper(0x01C5), 0x01C4);
        Y_EQUAL(upper(0x01C6), 0x01C4);
    }

    static void test_lowerCase()
    {
        Y_EQUAL(lower('A'), 'a');
        Y_EQUAL(lower('a'), 'a');
        Y_EQUAL(lower('Z'), 'z');
        Y_EQUAL(lower('z'), 'z');
        Y_EQUAL(lower(':'), ':');
        Y_EQUAL(lower(','), ',');

        Y_EQUAL(lower(0x00C0), 0x00E0);
        Y_EQUAL(lower(0x00C5), 0x00E5);
        Y_EQUAL(lower(0x00D8), 0x00F8);
        Y_EQUAL(lower(0x0178), 0x00FF);

        Y_EQUAL(lower(0x01C4), 0x01C6);
        Y_EQUAL(lower(0x01C5), 0x01C6);
        Y_EQUAL(lower(0x01C6), 0x01C6);
    }

    static void test_titleCase()
    {
        Y_EQUAL(title('A'), 'A');
        Y_EQUAL(title('a'), 'A');
        Y_EQUAL(title('Z'), 'Z');
        Y_EQUAL(title('z'), 'Z');
        Y_EQUAL(title(':'), ':');
        Y_EQUAL(title(','), ',');

        Y_EQUAL(title(0x00E0), 0x00C0);
        Y_EQUAL(title(0x00E5), 0x00C5);
        Y_EQUAL(title(0x00F8), 0x00D8);

        Y_EQUAL(title(0x00FF), 0x0178);

        Y_EQUAL(title(0x0106), 0x0106);
        Y_EQUAL(title(0x0107), 0x0106);

        Y_EQUAL(title(0x0174), 0x0174);
        Y_EQUAL(title(0x0175), 0x0174);

        Y_EQUAL(title(0x01C4), 0x01C5);
        Y_EQUAL(title(0x01C5), 0x01C5);
        Y_EQUAL(title(0x01C6), 0x01C5);
    }

    Y_SUBTEST("Unicode", test_upperCase, test_lowerCase, test_titleCase);

}
