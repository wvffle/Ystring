//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 26.10.2015
//
// This file is distributed under the BSD License.
// License text is included with the source distribution.
//****************************************************************************
#pragma once
#include "AbstractDecoder.hpp"

namespace Ystring { namespace Conversion {

    class Utf8Decoder : public AbstractDecoder
    {
    public:
        Utf8Decoder();

    protected:
        DecoderResult_t doDecode(char32_t*& dstBeg, char32_t* dstEnd,
                                 const char*& srcBeg, const char* srcEnd);
    };

}}
