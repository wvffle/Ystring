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
    namespace
    {
        typedef std::pair<uint8_t, uint32_t> P;
        const P SpecialChars[] = {
                P(0xD0, 0x011E), P(0xDD, 0x0130), P(0xDE, 0x015E),
                P(0xDF, 0x00DF), P(0xF0, 0x011F), P(0xFD, 0x0131),
                P(0xFE, 0x015F)
        };

        static CodePageFactory factory(std::begin(SpecialChars),
                                       std::end(SpecialChars),
                                       Encoding::ISO_8859_9);
    }

    CodePage makeIso8859_9()
    {
        return factory.makeCodePage();
    }
}}
