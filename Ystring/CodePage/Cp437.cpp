//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-07-27
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#include "Cp437.hpp"

#include <vector>

namespace Ystring { namespace CodePage
{
    typedef std::pair<uint32_t, uint8_t> P;

    const std::pair<uint32_t, uint8_t> Cp437SpecialChars[] = {
            P(0x263A, 0x01),
            P(0x263B, 0x02),
            P(0x2665, 0x03),
            P(0x2666, 0x04),
            P(0x2663, 0x05),
            P(0x2660, 0x06),
            P(0x2022, 0x07),
            P(0x25D8, 0x08),
            P(0x25CB, 0x09),
            P(0x25D9, 0x0A),
            P(0x2642, 0x0B),
            P(0x2640, 0x0C),
            P(0x266A, 0x0D),
            P(0x266B, 0x0E),
            P(0x263C, 0x0F),
            P(0x25BA, 0x10),
            P(0x25C4, 0x11),
            P(0x2195, 0x12),
            P(0x203C, 0x13),
            P(0x00B6, 0x14),
            P(0x00A7, 0x15),
            P(0x25AC, 0x16),
            P(0x21A8, 0x17),
            P(0x2191, 0x18),
            P(0x2193, 0x19),
            P(0x2192, 0x1A),
            P(0x2190, 0x1B),
            P(0x221F, 0x1C),
            P(0x2194, 0x1D),
            P(0x25B2, 0x1E),
            P(0x25BC, 0x1F),
            P(0x2302, 0x7F),
            P(0x00C7, 0x80),
            P(0x00FC, 0x81),
            P(0x00E9, 0x82),
            P(0x00E2, 0x83),
            P(0x00E4, 0x84),
            P(0x00E0, 0x85),
            P(0x00E5, 0x86),
            P(0x00E7, 0x87),
            P(0x00EA, 0x88),
            P(0x00EB, 0x89),
            P(0x00E8, 0x8A),
            P(0x00EF, 0x8B),
            P(0x00EE, 0x8C),
            P(0x00EC, 0x8D),
            P(0x00C4, 0x8E),
            P(0x00C5, 0x8F),
            P(0x00C9, 0x90),
            P(0x00E6, 0x91),
            P(0x00C6, 0x92),
            P(0x00F4, 0x93),
            P(0x00F6, 0x94),
            P(0x00F2, 0x95),
            P(0x00FB, 0x96),
            P(0x00F9, 0x97),
            P(0x00FF, 0x98),
            P(0x00D6, 0x99),
            P(0x00DC, 0x9A),
            P(0x00A2, 0x9B),
            P(0x00A3, 0x9C),
            P(0x00A5, 0x9D),
            P(0x20A7, 0x9E),
            P(0x0192, 0x9F),
            P(0x00E1, 0xA0),
            P(0x00ED, 0xA1),
            P(0x00F3, 0xA2),
            P(0x00FA, 0xA3),
            P(0x00F1, 0xA4),
            P(0x00D1, 0xA5),
            P(0x00AA, 0xA6),
            P(0x00BA, 0xA7),
            P(0x00BF, 0xA8),
            P(0x2310, 0xA9),
            P(0x00AC, 0xAA),
            P(0x00BD, 0xAB),
            P(0x00BC, 0xAC),
            P(0x00A1, 0xAD),
            P(0x00AB, 0xAE),
            P(0x00BB, 0xAF),
            P(0x2591, 0xB0),
            P(0x2592, 0xB1),
            P(0x2593, 0xB2),
            P(0x2502, 0xB3),
            P(0x2524, 0xB4),
            P(0x2561, 0xB5),
            P(0x2562, 0xB6),
            P(0x2556, 0xB7),
            P(0x2555, 0xB8),
            P(0x2563, 0xB9),
            P(0x2551, 0xBA),
            P(0x2557, 0xBB),
            P(0x255D, 0xBC),
            P(0x255C, 0xBD),
            P(0x255B, 0xBE),
            P(0x2510, 0xBF),
            P(0x2514, 0xC0),
            P(0x2534, 0xC1),
            P(0x252C, 0xC2),
            P(0x251C, 0xC3),
            P(0x2500, 0xC4),
            P(0x253C, 0xC5),
            P(0x255E, 0xC6),
            P(0x255F, 0xC7),
            P(0x255A, 0xC8),
            P(0x2554, 0xC9),
            P(0x2569, 0xCA),
            P(0x2566, 0xCB),
            P(0x2560, 0xCC),
            P(0x2550, 0xCD),
            P(0x256C, 0xCE),
            P(0x2567, 0xCF),
            P(0x2568, 0xD0),
            P(0x2564, 0xD1),
            P(0x2565, 0xD2),
            P(0x2559, 0xD3),
            P(0x2558, 0xD4),
            P(0x2552, 0xD5),
            P(0x2553, 0xD6),
            P(0x256B, 0xD7),
            P(0x256A, 0xD8),
            P(0x2518, 0xD9),
            P(0x250C, 0xDA),
            P(0x2588, 0xDB),
            P(0x2584, 0xDC),
            P(0x258C, 0xDD),
            P(0x2590, 0xDE),
            P(0x2580, 0xDF),
            P(0x03B1, 0xE0),
            P(0x00DF, 0xE1),
            P(0x0393, 0xE2),
            P(0x03C0, 0xE3),
            P(0x03A3, 0xE4),
            P(0x03C3, 0xE5),
            P(0x00B5, 0xE6),
            P(0x03C4, 0xE7),
            P(0x03A6, 0xE8),
            P(0x0398, 0xE9),
            P(0x03A9, 0xEA),
            P(0x03B4, 0xEB),
            P(0x221E, 0xEC),
            P(0x03C6, 0xED),
            P(0x03B5, 0xEE),
            P(0x2229, 0xEF),
            P(0x2261, 0xF0),
            P(0x00B1, 0xF1),
            P(0x2265, 0xF2),
            P(0x2264, 0xF3),
            P(0x2320, 0xF4),
            P(0x2321, 0xF5),
            P(0x00F7, 0xF6),
            P(0x2248, 0xF7),
            P(0x00B0, 0xF8),
            P(0x2219, 0xF9),
            P(0x00B7, 0xFA),
            P(0x221A, 0xFB),
            P(0x207F, 0xFC),
            P(0x00B2, 0xFD),
            P(0x25A0, 0xFE),
            P(0x00A0, 0xFF)
    };

    const uint32_t* cp437ToUnicode()
    {
        static std::vector<uint32_t> table;
        if (table.empty())
        {
            table.resize(256);
            for (uint32_t i = 0; i < 256; ++i)
                table[i] = i;
            for (auto it = std::begin(Cp437SpecialChars);
                 it != std::end(Cp437SpecialChars); ++it)
                table[it->second] = it->first;
        }
        return &table[0];
    }

    std::pair<const CodePointMapping*, const CodePointMapping*>
        unicodeToCp437()
    {
        return std::make_pair(std::begin(Cp437SpecialChars),
                              std::end(Cp437SpecialChars));
    }

    CodePage makeCp437()
    {
        auto to = cp437ToUnicode();
        auto from = unicodeToCp437();
        return CodePage(to, from.first, from.second, Encoding::CP_437);
    }
}}
