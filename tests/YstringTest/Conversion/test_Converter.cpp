//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-11-03
//
// This file is distributed under the BSD License.
// License text is included with the source distribution.
//****************************************************************************
#include "Ystring/Conversion/Converter.hpp"
#include "Ystring/YstringException.hpp"
#include "../Ytest/Ytest.hpp"
#include "Ystring/Utf/Utf8Chars.hpp"

using namespace Ystring;
using namespace Ystring::Conversion;

namespace
{
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

    void test_Cp437_to_Utf32()
    {
        Converter converter(Encoding::IBM_437, Encoding::UTF_32);
        char src[] = "\x01" "1A" "\x7F\xD0\xF0";
        std::u32string dst;
        Y_EQUAL(converter.convert(src, sizeof(src), dst), sizeof(src));
        char32_t expected[] = {0x263A, '1', 'A', 0x2302, 0x2568, 0x2261, 0};
        Y_EQUAL(dst, std::u32string(expected,
                                    sizeof(expected) / sizeof(char32_t)));
    }

    void test_Utf32_to_Cp437()
    {
        Converter converter(Encoding::UTF_32, Encoding::IBM_437);
        std::u32string src = U"\u2642st\u00C6uv\u2568wx\u00F8";
        std::string dst;
        Y_EQUAL(converter.convert(src.data(), src.size(), dst), src.size());
        Y_EQUAL((int)dst[0], (int)0xB);
    }

    void test_Utf8_to_Utf8_WithErrors()
    {
        Converter converter(Encoding::UTF_8, Encoding::UTF_8);
        std::string dst;
        std::string src = "AB\xCF";
        Y_ASSERT(converter.convert(src, dst, true) == src.end() - 1);
        Y_EQUAL(dst, "AB");
        src = "CD\xCF" "E";
        Y_ASSERT(converter.convert(src, dst) == src.end());
        Y_EQUAL(dst, "ABCD" UTF8_REPLACEMENT_CHARACTER "E");
    }

    void test_Utf8_to_Windows1252()
    {
        Converter converter(Encoding::UTF_8, Encoding::WINDOWS_1252);
        std::string s8 = "ABCD \xC3\x86\xC3\x98\xC3\x85 \xC3\xA6\xC3\xB8\xC3\xA5";
        std::string s1252;
        Y_EQUAL(converter.convert(s8.data(), s8.size(), s1252), s8.size());
        Y_EQUAL(s1252, "ABCD \xC6\xD8\xC5 \xE6\xF8\xE5");
    }

    void test_Utf8_to_Iso8859_1()
    {
        Converter converter(Encoding::UTF_8, Encoding::ISO_8859_1);
        std::string src = "Foobar";
        std::string dst;
        Y_EQUAL(converter.convert(src.data(), src.size(), dst), src.size());
        Y_EQUAL(src, dst);
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
              test_Cp437_to_Utf32,
              test_Utf32_to_Cp437,
              test_Utf8_to_Utf8_WithErrors,
              test_Utf8_to_Windows1252,
              test_Utf8_to_Iso8859_1);
}
