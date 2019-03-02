//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-07-29.
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#include "Ystring/EncodingInfo.hpp"

#include <sstream>
#include "Ytest/Ytest.hpp"

namespace {

using namespace Ystring;

void test_FromName()
{
    Y_EQUAL(encodingFromName("UTF-8"), Encoding::UTF_8);
    Y_EQUAL(encodingFromName("UTF-16"), Encoding::UTF_16);
    Y_EQUAL(encodingFromName("Utf-16bE"), Encoding::UTF_16_BE);
    Y_EQUAL(encodingFromName("Kjell"), Encoding::UNKNOWN);
}

void test_FromBom()
{
    Y_EQUAL(determineEncodingFromByteOrderMark("\xEF\xBB\xBF""Abrakadabra"),
             Encoding::UTF_8);
}

void doDetermineEncoding(const std::string& s, Encoding_t expectedEnc,
                         ptrdiff_t expectedOffset)
{
    auto enc = determineEncoding(s.data(), s.size());
    Y_EQUAL(enc.first, expectedEnc);
    auto offset = enc.second - s.data();
    Y_EQUAL(offset, expectedOffset);
}

void test_determineEncoding()
{
    Y_CALL(doDetermineEncoding("999888777666555", Encoding::UTF_8, 0));
}

void test_determineEncoding_in_stream()
{
    std::stringstream ss;
    ss << "\xEF\xBB\xBF" " Abrakadabra hokus pokus filiokus";
    std::string s;
    Encoding_t enc = determineEncoding(ss);
    Y_EQUAL(enc, Encoding::UTF_8);
    Y_EQUAL(ss.tellg(), (std::streamoff)3);
}

Y_TEST(test_FromName,
       test_FromBom,
       test_determineEncoding,
       test_determineEncoding_in_stream);

}
