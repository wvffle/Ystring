//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-11-21
//
// This file is distributed under the BSD License.
// License text is included with the source distribution.
//****************************************************************************
#pragma once
#include "AbstractDecoder.hpp"
#include "../Utf32/DecodeUtf32.hpp"

namespace Ystring { namespace Conversion {

    template <bool SwapBytes>
    class Utf32Decoder : public AbstractDecoder
    {
    public:
        Utf32Decoder()
            : AbstractDecoder(IsBigEndian == SwapBytes
                              ? Encoding::UTF_32_LE
                              : Encoding::UTF_32_BE)
        {}

    protected:
        DecoderResult_t doDecode(
                const char*& srcBeg, const char* srcEnd,
                char32_t*& dstBeg, char32_t* dstEnd)
        {
            while (dstBeg != dstEnd)
            {
                uint32_t tmp = *dstBeg;
                auto result = Utf32::nextUtf32CodePoint<SwapBytes>(
                        tmp, srcBeg, srcEnd);
                *dstBeg = tmp;
                if (result != DecoderResult::OK)
                    return result;
                ++dstBeg;
            }
            return DecoderResult::OK;
        }

        DecoderResult_t doDecode(
                const char32_t*& srcBeg, const char32_t* srcEnd,
                char32_t*& dstBeg, char32_t* dstEnd)
        {
            while (dstBeg != dstEnd)
            {
                uint32_t tmp = *dstBeg;
                auto result = Utf32::nextUtf32CodePoint<SwapBytes>(
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
            Utf32::skipNextUtf32CodePoint(srcBeg, srcEnd);
        }

        void skipInvalidCharacter(
                const char32_t*& srcBeg, const char32_t* srcEnd)
        {
            Utf32::skipNextUtf32CodePoint(srcBeg, srcEnd);
        }
    };

    typedef Utf32Decoder<IsLittleEndian> Utf32BEDecoder;
    typedef Utf32Decoder<IsBigEndian> Utf32LEDecoder;
}}
