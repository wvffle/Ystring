//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-11-21
//
// This file is distributed under the BSD License.
// License text is included with the source distribution.
//****************************************************************************
#include "CodePageDecoder.hpp"

namespace Ystring { namespace Conversion {

    CodePageDecoder::CodePageDecoder(Encoding_t encoding)
        : AbstractDecoder(encoding),
          m_CodePage(CodePage::makeCodePage(encoding))
    {}

    DecoderResult_t CodePageDecoder::doDecode(const char*& srcBeg,
                                              const char* srcEnd,
                                              char32_t*& dstBeg,
                                              char32_t* dstEnd)
    {
        while (dstBeg != dstEnd && srcBeg != srcEnd)
            *dstBeg++ = m_CodePage.toCodePoint(*srcBeg++);
        return DecoderResult::OK;
    }

    void CodePageDecoder::skipInvalidCharacter(
            const char*& srcBeg, const char* srcEnd)
    {
        if (srcBeg != srcEnd)
            ++srcBeg;
    }

}}
