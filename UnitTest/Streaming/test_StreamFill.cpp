//****************************************************************************
// Copyright © 2014 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2014-05-06.
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#include "../../Ystring/Streaming/StreamFill.hpp"
#include <sstream>

#include "../Ytest/Ytest.hpp"

namespace
{
    using namespace Ystring;

    static void test_fill()
    {
        std::ostringstream ss;
        ss << "Hello" << spaces(4) << "Jan Erik";
        Y_EQUAL(ss.str(), "Hello    Jan Erik");
        std::wostringstream ws;
        ws << L"Hello" << spaces(4) << L"Jan Erik";
        Y_EQUAL(ws.str(), L"Hello    Jan Erik");
        std::wostringstream ws2;
        ws2 << L"Hello" << fill(3, 13) << L"Jan Erik";
        Y_EQUAL(ws2.str(), L"Hello131313Jan Erik");
    }

    Y_SUBTEST("Streaming", test_fill);
}
