//****************************************************************************
// Copyright © 2014 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2014-05-06.
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#include "../../include/Ystring/Streaming/StreamJoin.hpp"
#include <sstream>

#include "../Ytest/Ytest.hpp"

namespace
{
    using namespace Ystring;

    static void test_join()
    {
        const char* strs[] = {"alpha", "bravo", "charlie", "delta", "echo"};
        std::ostringstream ss;
        ss << "Strings: " << join(std::begin(strs), std::end(strs), ", ");
        Y_EQUAL(ss.str(), "Strings: alpha, bravo, charlie, delta, echo");
    }

    Y_SUBTEST("Streaming", test_join);
}
