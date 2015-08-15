//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-07-29
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#include "../Ystring/EncodingInfo.hpp"

#include <sstream>
#include <JEBTest/JEBTest.hpp>

namespace {

using namespace Ystring;

void test_FromName()
{
    JT_EQUAL(encodingFromName("UTF8"), Encoding::UTF_8);
    JT_EQUAL(encodingFromName("UTF-8"), Encoding::UTF_8);
    JT_EQUAL(encodingFromName("UTF-16"), Encoding::UTF_16);
    JT_EQUAL(encodingFromName("Utf-16bE"), Encoding::UTF_16_BE);
    JT_EQUAL(encodingFromName("Utf32Le"), Encoding::UTF_32_LE);
    JT_EQUAL(encodingFromName("Kjell"), Encoding::UNKNOWN);
}

void test_FromBom()
{
    JT_EQUAL(determineEncodingFromByteOrderMark("\xEF\xBB\xBF""Abrakadabra"),
             Encoding::UTF_8);
}

void test_DetermineEncoding()
{
    std::stringstream ss;
    ss << "\xEF\xBB\xBF" " Abrakadabra hokus pokus filiokus";
    std::string s;
    Encoding_t enc = determineEncoding(ss);
    JT_EQUAL(enc, Encoding::UTF_8);
    JT_EQUAL(ss.tellg(), (std::streamoff)3);
}

JT_TEST(test_FromName, test_FromBom, test_DetermineEncoding);

}
