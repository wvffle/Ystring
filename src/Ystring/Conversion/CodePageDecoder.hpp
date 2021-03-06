//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-11-21
//
// This file is distributed under the BSD License.
// License text is included with the source distribution.
//****************************************************************************
#pragma once
#include "AbstractDecoder.hpp"
#include "Ystring/Encodings/CodePage.hpp"

namespace Ystring { namespace Conversion {

    class CodePageDecoder : public AbstractDecoder
    {
    public:
        CodePageDecoder(Encoding_t encoding);

    protected:
        DecoderResult_t doDecode(
                const char*& srcBeg, const char* srcEnd,
                char32_t*& dstBeg, char32_t* dstEnd) const;

        void skipInvalidCharacter(
                const char*& srcBeg, const char* srcEnd) const;

    private:
        Encodings::CodePage m_CodePage;
    };

}}
