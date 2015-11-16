//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-11-03
//
// This file is distributed under the BSD License.
// License text is included with the source distribution.
//****************************************************************************
#include "../../Ystring/Conversion/Converter.hpp"
#include "../../Ystring/YstringException.hpp"
#include "../Ytest/Ytest.hpp"

using namespace Ystring;
using namespace Ystring::Conversion;

namespace {

    void test_Utf8_to_Utf16()
    {
        Converter converter(Encoding::UTF_8, Encoding::UTF_16);
        std::string s8 = "ABCD";
        std::u16string s16;
        Y_EQUAL(converter.convert(s8.data(), s8.size(), s16), s8.size());
        Y_EQUAL(s16, u"ABCD");
    }

    void test_Utf8_to_Utf16_IncompleteSource()
    {
        Converter converter(Encoding::UTF_8, Encoding::UTF_16);
        std::string s8 = "ABCDEF\xE4\xB8\xA0GHIJKL";
        std::u16string s16;
        Y_EQUAL(converter.convert(s8.data(), 8, s16), 8);
        Y_EQUAL(s16, u"ABCDEF\uFFFD");

        s16.clear();
        Y_EQUAL(converter.convert(s8.data(), 8, s16, true), 6);
        Y_EQUAL(s16, u"ABCDEF");

        converter.setDecoderReplacementCharacter('?');
        s16.clear();
        Y_EQUAL(converter.convert(s8.data(), 8, s16), 8);
        Y_EQUAL(s16, u"ABCDEF?");

        converter.setDecoderErrorHandlingPolicy(ErrorHandlingPolicy::THROW);
        s16.clear();
        Y_THROWS(converter.convert(s8.data(), 8, s16), YstringException);

        converter.setDecoderErrorHandlingPolicy(ErrorHandlingPolicy::STOP);
        s16.clear();
        Y_EQUAL(converter.convert(s8.data(), 8, s16), 6);
        Y_EQUAL(s16, u"ABCDEF");

        converter.setDecoderErrorHandlingPolicy(ErrorHandlingPolicy::SKIP);
        s16.clear();
        Y_EQUAL(converter.convert(s8.data(), 8, s16), 8);
        Y_EQUAL(s16, u"ABCDEF");
    }

    void test_Utf8_to_Utf16_SmallBuffer()
    {
        Converter converter(Encoding::UTF_8, Encoding::UTF_16);
        converter.setBufferSize(4);
        std::string s8 = "ABCDEF\xE4\xB8\xA0GHIJKL";
        std::u16string s16;
        Y_EQUAL(converter.convert(s8.data(), s8.size(), s16), s8.size());
        Y_EQUAL(s16, u"ABCDEF\u4E20GHIJKL");
    }

    void test_Utf16_to_Utf16()
    {
        Converter converter(Encoding::UTF_16, Encoding::UTF_16);
        std::u16string src = u"ABCDEFGHIJKL";
        std::u16string dst;
        Y_EQUAL(converter.convert(src.data(), src.size(), dst), src.size());
        Y_EQUAL(dst, u"ABCDEFGHIJKL");
    }

    Y_SUBTEST("Conversion",
              test_Utf8_to_Utf16,
              test_Utf8_to_Utf16_IncompleteSource,
              test_Utf8_to_Utf16_SmallBuffer,
              test_Utf16_to_Utf16);
}
