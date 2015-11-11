//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-10-26
//
// This file is distributed under the BSD License.
// License text is included with the source distribution.
//****************************************************************************
#include "Utf8Decoder.hpp"
#include "../Utf8/DecodeUtf8.hpp"
#include "../Unicode/UnicodeChars.hpp"

namespace Ystring { namespace Conversion {

    Utf8Decoder::Utf8Decoder()
        : AbstractDecoder(Encoding::UTF_8, SUPPORTS_8_BIT)
    {}

    DecoderResult_t Utf8Decoder::doDecode(char32_t*& dstBeg, char32_t* dstEnd,
                                          const char*& srcBeg,
                                          const char* srcEnd)
    {
        while (dstBeg != dstEnd)
        {
            uint32_t tmp = *dstBeg;
            auto result = Utf8::nextUtf8CodePoint(tmp, srcBeg, srcEnd);
            *dstBeg = tmp;
            if (result != DecoderResult::OK)
            {
                if (stopOnErrors()
                        || result != DecoderResult::INVALID
                        || !Utf8::skipNextUtf8CodePoint(srcBeg, srcEnd, 1))
                {
                    return result;
                }
                *dstBeg = Unicode::REPLACEMENT_CHARACTER;
            }
            ++dstBeg;
        }
        return DecoderResult::OK;
    }

}}
