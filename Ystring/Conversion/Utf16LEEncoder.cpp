//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 08.11.2015
//
// This file is distributed under the BSD License.
// License text is included with the source distribution.
//****************************************************************************
#include "Utf16LEEncoder.hpp"

namespace Ystring { namespace Conversion {

    Utf16LEEncoder::Utf16LEEncoder()
        : AbstractEncoder(Encoding::UTF_16_LE)
    {}

    void Utf16LEEncoder::doEncode(std::string& dst,
                                  const char32_t*& srcBeg,
                                  const char32_t* srcEnd)
    {
        auto out = back_inserter(dst);
        while (srcBeg != srcEnd)
        {
            Utf16::addUtf16LE(out, *srcBeg);
            ++srcBeg;
        }
    }

    void Utf16LEEncoder::doEncode(std::u16string& dst,
                                  const char32_t*& srcBeg,
                                  const char32_t* srcEnd)
    {
        auto out = back_inserter(dst);
        while (srcBeg != srcEnd)
        {
            Utf16::addUtf16LE(out, *srcBeg);
            ++srcBeg;
        }
    }

}}
