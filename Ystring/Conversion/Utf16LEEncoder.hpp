//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 08.11.2015
//
// This file is distributed under the BSD License.
// License text is included with the source distribution.
//****************************************************************************
#pragma once
#include "AbstractEncoder.hpp"
#include "../Utf16/EncodeUtf16.hpp"

namespace Ystring { namespace Conversion {

    class Utf16LEEncoder : public AbstractEncoder
    {
    public:
        Utf16LEEncoder();

    protected:
        virtual void doEncode(
                std::string& dst,
                const char32_t*& srcBeg, const char32_t* srcEnd);

        virtual void doEncode(
                std::u16string& dst,
                const char32_t*& srcBeg, const char32_t* srcEnd);
    };

}}
