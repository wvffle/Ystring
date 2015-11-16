//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-10-26
//
// This file is distributed under the BSD License.
// License text is included with the source distribution.
//****************************************************************************
#include "Utf8Decoder.hpp"
#include "../Utf8/DecodeUtf8.hpp"

namespace Ystring { namespace Conversion {

    Utf8Decoder::Utf8Decoder()
        : AbstractDecoder(Encoding::UTF_8, SUPPORTS_8_BIT)
    {}

    DecoderResult_t Utf8Decoder::doDecode(const char*& srcBeg,
                                          const char* srcEnd,
                                          char32_t*& dstBeg,
                                          char32_t* dstEnd)
    {
        while (dstBeg != dstEnd)
        {
            uint32_t tmp = *dstBeg;
            auto result = Utf8::nextUtf8CodePoint(tmp, srcBeg, srcEnd);
            *dstBeg = tmp;
            if (result != DecoderResult::OK)
                return result;
            ++dstBeg;
        }
        return DecoderResult::OK;
    }

    void Utf8Decoder::skipInvalidCharacter(
            const char*& srcBeg, const char* srcEnd)
    {
        Utf8::skipNextUtf8CodePoint(srcBeg, srcEnd);
    }

}}
