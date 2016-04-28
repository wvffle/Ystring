//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-06-02.
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#include "../../Ystring/Unicode/CharMappingTypes.hpp"

#include "../Ytest/Ytest.hpp"

namespace {

    using namespace Ystring::Unicode;

    static void test_Get()
    {
        CompactCharMapping ccs = {0x40, 0x20, 0x07FFFDFE, 0xF8000001};
        char32_t lcase;
        Y_ASSERT(ccs.get(0x40, lcase));
        Y_EQUAL(lcase, 0x40);
        Y_ASSERT(ccs.get('A', lcase));
        Y_EQUAL(lcase, 'a');
        Y_ASSERT(!ccs.get('I', lcase));
        Y_ASSERT(ccs.get('Z', lcase));
        Y_EQUAL(lcase, 'z');
        Y_ASSERT(ccs.get(0x5B, lcase));
        Y_EQUAL(lcase, 0x5B);
    }

    Y_SUBTEST("Unicode", test_Get);

}
