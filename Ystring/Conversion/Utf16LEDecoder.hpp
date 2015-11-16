//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-11-16
//
// This file is distributed under the BSD License.
// License text is included with the source distribution.
//****************************************************************************
#pragma once
#include "AbstractDecoder.hpp"

namespace Ystring { namespace Conversion {

    class Utf16LEDecoder : public AbstractDecoder
    {
    public:
        Utf16LEDecoder();

    protected:
        DecoderResult_t doDecode(
                const char*& srcBeg, const char* srcEnd,
                char32_t*& dstBeg, char32_t* dstEnd);

        DecoderResult_t doDecode(
                const char16_t*& srcBeg, const char16_t* srcEnd,
                char32_t*& dstBeg, char32_t* dstEnd);

        void skipInvalidCharacter(
                const char*& srcBeg, const char* srcEnd);

        void skipInvalidCharacter(
                const char16_t*& srcBeg, const char16_t* srcEnd);
    };

}}
