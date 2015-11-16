//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-11-16
//
// This file is distributed under the BSD License.
// License text is included with the source distribution.
//****************************************************************************
#include "Utf16LEDecoder.hpp"
#include "../Utf16/DecodeUtf16.hpp"

namespace Ystring { namespace Conversion {

    Utf16LEDecoder::Utf16LEDecoder()
            : AbstractDecoder(Encoding::UTF_16_LE, SUPPORTS_8_AND_16_BIT)
    {}

    DecoderResult_t Utf16LEDecoder::doDecode(const char*& srcBeg,
                                             const char* srcEnd,
                                             char32_t*& dstBeg,
                                             char32_t* dstEnd)
    {
        while (dstBeg != dstEnd)
        {
            uint32_t tmp = *dstBeg;
            auto result = Utf16::nextUtf16LECodePoint(tmp, srcBeg, srcEnd);
            *dstBeg = tmp;
            if (result != DecoderResult::OK)
                return result;
            ++dstBeg;
        }
        return DecoderResult::OK;
    }

    DecoderResult_t Utf16LEDecoder::doDecode(const char16_t*& srcBeg,
                                             const char16_t* srcEnd,
                                             char32_t*& dstBeg,
                                             char32_t* dstEnd)
    {
        while (dstBeg != dstEnd)
        {
            uint32_t tmp = *dstBeg;
            auto result = Utf16::nextUtf16LECodePoint(tmp, srcBeg, srcEnd);
            *dstBeg = tmp;
            if (result != DecoderResult::OK)
                return result;
            ++dstBeg;
        }
        return DecoderResult::OK;
    }

    void Utf16LEDecoder::skipInvalidCharacter(
            const char*& srcBeg, const char* srcEnd)
    {
        Utf16::skipNextUtf16LECodePoint(srcBeg, srcEnd);
    }

    void Utf16LEDecoder::skipInvalidCharacter(
            const char16_t*& srcBeg, const char16_t* srcEnd)
    {
        Utf16::skipNextUtf16LECodePoint(srcBeg, srcEnd);
    }

}}
