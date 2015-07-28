//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 27.07.15
//
// This file is distributed under the BSD License.
// License text is included with the source distribution.
//****************************************************************************
#include "Cp437.hpp"

#include <vector>

namespace Ystring { namespace CodePage {

const std::pair<uint32_t, uint8_t> Cp437SpecialChars[] = {
        {0x263A, 0x01},
        {0x263B, 0x02},
        {0x2665, 0x03},
        {0x2666, 0x04},
        {0x2663, 0x05},
        {0x2660, 0x06},
        {0x2022, 0x07},
        {0x25D8, 0x08},
        {0x25CB, 0x09},
        {0x25D9, 0x0A},
        {0x2642, 0x0B},
        {0x2640, 0x0C},
        {0x266A, 0x0D},
        {0x266B, 0x0E},
        {0x263C, 0x0F},
        {0x25BA, 0x10},
        {0x25C4, 0x11},
        {0x2195, 0x12},
        {0x203C, 0x13},
        {0x00B6, 0x14},
        {0x00A7, 0x15},
        {0x25AC, 0x16},
        {0x21A8, 0x17},
        {0x2191, 0x18},
        {0x2193, 0x19},
        {0x2192, 0x1A},
        {0x2190, 0x1B},
        {0x221F, 0x1C},
        {0x2194, 0x1D},
        {0x25B2, 0x1E},
        {0x25BC, 0x1F},
        {0x2302, 0x7F},
        {0x00C7, 0x80},
        {0x00FC, 0x81},
        {0x00E9, 0x82},
        {0x00E2, 0x83},
        {0x00E4, 0x84},
        {0x00E0, 0x85},
        {0x00E5, 0x86},
        {0x00E7, 0x87},
        {0x00EA, 0x88},
        {0x00EB, 0x89},
        {0x00E8, 0x8A},
        {0x00EF, 0x8B},
        {0x00EE, 0x8C},
        {0x00EC, 0x8D},
        {0x00C4, 0x8E},
        {0x00C5, 0x8F},
        {0x00C9, 0x90},
        {0x00E6, 0x91},
        {0x00C6, 0x92},
        {0x00F4, 0x93},
        {0x00F6, 0x94},
        {0x00F2, 0x95},
        {0x00FB, 0x96},
        {0x00F9, 0x97},
        {0x00FF, 0x98},
        {0x00D6, 0x99},
        {0x00DC, 0x9A},
        {0x00A2, 0x9B},
        {0x00A3, 0x9C},
        {0x00A5, 0x9D},
        {0x20A7, 0x9E},
        {0x0192, 0x9F},
        {0x00E1, 0xA0},
        {0x00ED, 0xA1},
        {0x00F3, 0xA2},
        {0x00FA, 0xA3},
        {0x00F1, 0xA4},
        {0x00D1, 0xA5},
        {0x00AA, 0xA6},
        {0x00BA, 0xA7},
        {0x00BF, 0xA8},
        {0x2310, 0xA9},
        {0x00AC, 0xAA},
        {0x00BD, 0xAB},
        {0x00BC, 0xAC},
        {0x00A1, 0xAD},
        {0x00AB, 0xAE},
        {0x00BB, 0xAF},
        {0x2591, 0xB0},
        {0x2592, 0xB1},
        {0x2593, 0xB2},
        {0x2502, 0xB3},
        {0x2524, 0xB4},
        {0x2561, 0xB5},
        {0x2562, 0xB6},
        {0x2556, 0xB7},
        {0x2555, 0xB8},
        {0x2563, 0xB9},
        {0x2551, 0xBA},
        {0x2557, 0xBB},
        {0x255D, 0xBC},
        {0x255C, 0xBD},
        {0x255B, 0xBE},
        {0x2510, 0xBF},
        {0x2514, 0xC0},
        {0x2534, 0xC1},
        {0x252C, 0xC2},
        {0x251C, 0xC3},
        {0x2500, 0xC4},
        {0x253C, 0xC5},
        {0x255E, 0xC6},
        {0x255F, 0xC7},
        {0x255A, 0xC8},
        {0x2554, 0xC9},
        {0x2569, 0xCA},
        {0x2566, 0xCB},
        {0x2560, 0xCC},
        {0x2550, 0xCD},
        {0x256C, 0xCE},
        {0x2567, 0xCF},
        {0x2568, 0xD0},
        {0x2564, 0xD1},
        {0x2565, 0xD2},
        {0x2559, 0xD3},
        {0x2558, 0xD4},
        {0x2552, 0xD5},
        {0x2553, 0xD6},
        {0x256B, 0xD7},
        {0x256A, 0xD8},
        {0x2518, 0xD9},
        {0x250C, 0xDA},
        {0x2588, 0xDB},
        {0x2584, 0xDC},
        {0x258C, 0xDD},
        {0x2590, 0xDE},
        {0x2580, 0xDF},
        {0x03B1, 0xE0},
        {0x00DF, 0xE1},
        {0x0393, 0xE2},
        {0x03C0, 0xE3},
        {0x03A3, 0xE4},
        {0x03C3, 0xE5},
        {0x00B5, 0xE6},
        {0x03C4, 0xE7},
        {0x03A6, 0xE8},
        {0x0398, 0xE9},
        {0x03A9, 0xEA},
        {0x03B4, 0xEB},
        {0x221E, 0xEC},
        {0x03C6, 0xED},
        {0x03B5, 0xEE},
        {0x2229, 0xEF},
        {0x2261, 0xF0},
        {0x00B1, 0xF1},
        {0x2265, 0xF2},
        {0x2264, 0xF3},
        {0x2320, 0xF4},
        {0x2321, 0xF5},
        {0x00F7, 0xF6},
        {0x2248, 0xF7},
        {0x00B0, 0xF8},
        {0x2219, 0xF9},
        {0x00B7, 0xFA},
        {0x221A, 0xFB},
        {0x207F, 0xFC},
        {0x00B2, 0xFD},
        {0x25A0, 0xFE},
        {0x00A0, 0xFF}
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