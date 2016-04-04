//****************************************************************************
// Copyright © 2016 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2016-04-04.
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#include "Iso8859_9.hpp"

#include "CodePageFactory.hpp"

namespace Ystring { namespace CodePage
{
    typedef std::pair<uint8_t, uint32_t> P;
    const P Iso8859_9_SpecialChars[] = {
            P(0xD0, 0x011E), P(0xDD, 0x0130), P(0xDE, 0x015E),
            P(0xDF, 0x00DF), P(0xF0, 0x011F), P(0xFD, 0x0131),
            P(0xFE, 0x015F)
    };

    CodePage makeIso8859_9()
    {
        static CodePageFactory factory(
                std::begin(Iso8859_9_SpecialChars),
                std::end(Iso8859_9_SpecialChars),
                Encoding::ISO_8859_9);
        return factory.makeCodePage();
    }
}}
