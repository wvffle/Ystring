//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-11-25.
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#include "Iso8859_10.hpp"

#include "CodePageFactory.hpp"

namespace Ystring { namespace Encodings
{
    namespace
    {
        typedef std::pair<uint8_t, char32_t> P;
        const P SpecialChars[] = {
                P(0xA1, 0x0104), P(0xA2, 0x0112), P(0xA3, 0x0122),
                P(0xA4, 0x012A), P(0xA5, 0x0128), P(0xA6, 0x0136),
                P(0xA8, 0x013B), P(0xA9, 0x0110), P(0xAA, 0x0160),
                P(0xAB, 0x0166), P(0xAC, 0x017D), P(0xAE, 0x016A),
                P(0xAF, 0x014A), P(0xB1, 0x0105), P(0xB2, 0x0113),
                P(0xB3, 0x0123), P(0xB4, 0x012B), P(0xB5, 0x0129),
                P(0xB6, 0x0137), P(0xB8, 0x013C), P(0xB9, 0x0111),
                P(0xBA, 0x0161), P(0xBB, 0x0167), P(0xBC, 0x017E),
                P(0xBD, 0x2015), P(0xBE, 0x016B), P(0xBF, 0x014B),
                P(0xC0, 0x0100), P(0xC7, 0x012E), P(0xC8, 0x010C),
                P(0xCA, 0x0118), P(0xCC, 0x0116), P(0xD1, 0x0145),
                P(0xD2, 0x014C), P(0xD7, 0x0168), P(0xD9, 0x0172),
                P(0xE0, 0x0101), P(0xE7, 0x012F), P(0xE8, 0x010D),
                P(0xEA, 0x0119), P(0xEC, 0x0117), P(0xF1, 0x0146),
                P(0xF2, 0x014D), P(0xF7, 0x0169), P(0xF9, 0x0173),
                P(0xFF, 0x0138)
        };

        CodePageFactory factory(std::begin(SpecialChars),
                                std::end(SpecialChars),
                                Encoding::ISO_8859_10);
    }

    CodePage makeIso8859_10()
    {
        return factory.makeCodePage();
    }
}}
