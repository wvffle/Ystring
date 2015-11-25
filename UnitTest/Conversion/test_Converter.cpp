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
        char16_t src16[] = u"ABCDEFGHIJKL";
        auto src8 = reinterpret_cast<const char*>(src16);
        std::u16string dst;
        Y_EQUAL(converter.convert(src8, sizeof(src16) - 2, dst),
                sizeof(src16) - 2);
        Y_EQUAL(dst, u"ABCDEFGHIJKL");
    }

    void test_Utf16_to_Utf8()
    {
        Converter converter(Encoding::UTF_16, Encoding::UTF_8);
        std::u16string src = u"ABCDEFGHIJKL";
        std::string dst;
        Y_EQUAL(converter.convert(src.data(), src.size(), dst), src.size());
        Y_EQUAL(dst, "ABCDEFGHIJKL");
    }

    void test_Utf16BE_to_Utf16LE()
    {
        Converter converter(Encoding::UTF_16_BE, Encoding::UTF_16_LE);
        char16_t src[] = {'A', 'B', 'C', 'D', 'E', 'F', 'H', 'I'};
        auto srcLen = sizeof(src) / sizeof(*src);
        std::u16string dst;
        Y_EQUAL(converter.convert(src, srcLen, dst), srcLen);
        std::u16string expected;
        for (auto i = 0; i != srcLen; ++i)
            expected.push_back(src[i] << 8);
        Y_EQUAL(dst, expected);
    }

    void test_Utf16LE_to_Utf16BE()
    {
        Converter converter(Encoding::UTF_16_LE, Encoding::UTF_16_BE);
        char16_t src[] = {'A', 'B', 'C', 'D', 'E', 'F', 'H', 'I'};
        auto srcLen = sizeof(src) / sizeof(*src);
        std::u16string dst;
        Y_EQUAL(converter.convert(src, srcLen, dst), srcLen);
        std::u16string expected;
        for (auto i = 0; i != srcLen; ++i)
            expected.push_back(src[i] << 8);
        Y_EQUAL(dst, expected);
    }

    void test_Cp437_to_Utf8()
    {
        Converter converter(Encoding::IBM_437, Encoding::UTF_8);
        std::string src = "ab\x0Aqr\x0Bst\x92uv\xD0";
        std::string dst;
        Y_EQUAL(converter.convert(src.data(), src.size(), dst), src.size());
        Y_EQUAL(dst, "ab\x0Aqr\xE2\x99\x82st\xC3\x86uv\xE2\x95\xA8");
    }


    void test_Utf32_to_Cp437()
    {
        Converter converter(Encoding::UTF_32, Encoding::IBM_437);
        std::u32string src = U"\u2642st\u00C6uv\u2568wx\u00F8";
//        std::u32string src = U"ab\u000Aqr\u2642st\u00C6uv\u2568wx\u00F8";
        std::string dst;
        Y_EQUAL(converter.convert(src.data(), src.size(), dst), src.size());
        Y_EQUAL((int)dst[0], (int)0xB);
//        Y_EQUAL_RANGES(dst, "ab\x0Aqr\x0Bst\x92uv\xD0wx?");
    }

    Y_SUBTEST("Conversion",
              test_Utf8_to_Utf16,
              test_Utf8_to_Utf16_IncompleteSource,
              test_Utf8_to_Utf16_SmallBuffer,
              test_Utf16_to_Utf16,
              test_Utf16_to_Utf8,
              test_Utf16BE_to_Utf16LE,
              test_Utf16LE_to_Utf16BE,
              test_Cp437_to_Utf8,
              test_Utf32_to_Cp437);
}
