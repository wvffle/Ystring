//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 08.11.2015
//
// This file is distributed under the BSD License.
// License text is included with the source distribution.
//****************************************************************************
#include "Utf16LEEncoder.hpp"
#include "../Utf16/EncodeUtf16.hpp"

namespace Ystring { namespace Conversion {

    Utf16LEEncoder::Utf16LEEncoder()
        : AbstractEncoder(Encoding::UTF_16_LE)
    {}

    void Utf16LEEncoder::doEncode(const char32_t*& srcBeg,
                                  const char32_t* srcEnd,
                                  std::string& dst)
    {
        auto out = back_inserter(dst);
        while (srcBeg != srcEnd)
        {
            Utf16::addUtf16LE(out, *srcBeg);
            ++srcBeg;
        }
    }

    void Utf16LEEncoder::doEncode(const char32_t*& srcBeg,
                                  const char32_t* srcEnd,
                                  std::u16string& dst)
    {
        auto out = back_inserter(dst);
        while (srcBeg != srcEnd)
        {
            Utf16::addUtf16LE(out, *srcBeg);
            ++srcBeg;
        }
    }

}}
