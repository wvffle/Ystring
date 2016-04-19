//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-09-19.
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#include "Iso8859_15.hpp"

#include "CodePageFactory.hpp"

namespace Ystring { namespace CodePage
{
    namespace
    {
        typedef std::pair<uint8_t, uint32_t> P;
        const P SpecialChars[] = {
                P(0xA4, 0x20AC), P(0xA6, 0x0160), P(0xA8, 0x0161),
                P(0xB4, 0x017D), P(0xB8, 0x017E), P(0xBC, 0x0152),
                P(0xBD, 0x0153), P(0xBE, 0x0178)
        };

        CodePageFactory factory(std::begin(SpecialChars),
                                std::end(SpecialChars),
                                Encoding::ISO_8859_15);
    }

    CodePage makeIso8859_15()
    {
        return factory.makeCodePage();
    }
}}
