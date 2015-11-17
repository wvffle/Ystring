//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-11-16
//
// This file is distributed under the BSD License.
// License text is included with the source distribution.
//****************************************************************************
#pragma once
#include "AbstractDecoder.hpp"
#include "../Utf16/DecodeUtf16.hpp"

namespace Ystring { namespace Conversion {

    template <bool SwapBytes>
    class Utf16Decoder : public AbstractDecoder
    {
    public:
        Utf16Decoder()
                : AbstractDecoder(Encoding::UTF_16_LE, SUPPORTS_8_AND_16_BIT)
        {}

    protected:
        DecoderResult_t doDecode(
                const char*& srcBeg, const char* srcEnd,
                char32_t*& dstBeg, char32_t* dstEnd)
        {
            while (dstBeg != dstEnd)
            {
                uint32_t tmp = *dstBeg;
                auto result = Utf16::nextUtf16CodePoint<SwapBytes>(
                        tmp, srcBeg, srcEnd);
                *dstBeg = tmp;
                if (result != DecoderResult::OK)
                    return result;
                ++dstBeg;
            }
            return DecoderResult::OK;
        }

        DecoderResult_t doDecode(
                const char16_t*& srcBeg, const char16_t* srcEnd,
                char32_t*& dstBeg, char32_t* dstEnd)
        {
            while (dstBeg != dstEnd)
            {
                uint32_t tmp = *dstBeg;
                auto result = Utf16::nextUtf16CodePoint<SwapBytes>(
                        tmp, srcBeg, srcEnd);
                *dstBeg = tmp;
                if (result != DecoderResult::OK)
                    return result;
                ++dstBeg;
            }
            return DecoderResult::OK;
        }

        void skipInvalidCharacter(
                const char*& srcBeg, const char* srcEnd)
        {
            Utf16::skipNextUtf16CodePoint<SwapBytes>(srcBeg, srcEnd);
        }

        void skipInvalidCharacter(
                const char16_t*& srcBeg, const char16_t* srcEnd)
        {
            Utf16::skipNextUtf16CodePoint<SwapBytes>(srcBeg, srcEnd);
        }
    };

    typedef Utf16Decoder<IsLittleEndian> Utf16BEDecoder;
    typedef Utf16Decoder<IsBigEndian> Utf16LEDecoder;
}}
