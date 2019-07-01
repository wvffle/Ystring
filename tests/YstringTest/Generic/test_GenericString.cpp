//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-06-04.
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#include "Ystring/Generic/GenericString.hpp"
#include "Ystring/Utf/Utf8Encoding.hpp"
#include "Ytest/Ytest.hpp"

namespace {

using namespace Ystring;
using Generic::makeStringReference;
using Generic::makeRange;
using Utf8::Utf8Encoding;
using std::begin;
using std::end;

void test_appendJoin()
{
    const char* strings[] = {"foo", "faa", "fii", "fee", "fuu"};
    char result[256] = "Foo bar ";
    auto ref = makeStringReference(result, strlen(result));
    Generic::appendJoin(ref, begin(strings), end(strings));
    Y_EQUAL(result, "Foo bar foofaafiifeefuu");
}

void test_find_different_containers_same_encoding()
{
    std::string str("Abraham Brorson");
    char cmp[] = "m B";
    auto match = Generic::findFirst(makeRange(str), makeRange(cmp),
                                    Utf8Encoding());
    Y_EQUAL(std::distance(str.begin(), match.begin()), 6);
    Y_ASSERT(match.end() == str.begin() + 9);
}

void test_join()
{
    const char* strings[] = {"foo", "faa", "fii", "fee", "fuu"};
    auto result = Generic::join<std::vector<char>>(begin(strings), end(strings));
    result.push_back(0);
    Y_EQUAL_RANGES(result, "foofaafiifeefuu");
}

void test_sizeOfJoin()
{
    const char* strings[] = {"foo", "faa", "fii"};
    auto result = Generic::sizeOfJoin(begin(strings), end(strings),
                                      Generic::makeRange("::"));
    Y_EQUAL(result, 13);
}

void test_sizeOfLower()
{
    std::string str("\xC8\xBA");
    Y_EQUAL(Generic::sizeOfLower(makeRange(str), Utf8Encoding()), 3);
}

Y_SUBTEST("Generic",
          test_appendJoin,
          test_find_different_containers_same_encoding,
          test_join,
          test_sizeOfJoin,
          test_sizeOfLower);

}
