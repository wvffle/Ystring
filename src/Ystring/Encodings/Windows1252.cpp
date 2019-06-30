//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-07-27
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#include "Windows1252.hpp"

#include "CodePageFactory.hpp"

namespace Ystring { namespace Encodings
{
    namespace
    {
        typedef std::pair<uint8_t, char32_t> P;
        const P SpecialChars[] = {
                P(0x8C, 0x0152), P(0x9C, 0x0153), P(0x8A, 0x0160),
                P(0x9A, 0x0161), P(0x9F, 0x0178), P(0x8E, 0x017D),
                P(0x9E, 0x017E), P(0x83, 0x0192), P(0x98, 0x02DC),
                P(0x96, 0x2013), P(0x97, 0x2014), P(0x91, 0x2018),
                P(0x92, 0x2019), P(0x82, 0x201A), P(0x93, 0x201C),
                P(0x94, 0x201D), P(0x84, 0x201E), P(0x86, 0x2020),
                P(0x87, 0x2021), P(0x95, 0x2022), P(0x85, 0x2026),
                P(0x89, 0x2030), P(0x8B, 0x2039), P(0x9B, 0x203A),
                P(0x80, 0x20AC), P(0x88, 0x20C6), P(0x99, 0x2122)
        };

        static CodePageFactory factory(
                std::begin(SpecialChars),
                std::end(SpecialChars),
                Encoding::WINDOWS_1252);
    }

    CodePage makeWindows1252()
    {
        return factory.makeCodePage();
    }
}}
