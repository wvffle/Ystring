//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-07-2115
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#pragma once

#include <cstddef>
#include <cstdint>
#include <vector>
#include <utility>
#include "../Encoding.hpp"
#include "../YstringDefinitions.hpp"

namespace Ystring { namespace CodePage
{
    class YSTRING_API CodePage
    {
    public:
        CodePage(Encoding_t encoding);
        CodePage(const std::pair<uint32_t, uint32_t>* fromCodePoint,
                 const uint32_t* fromChar,
                 uint16_t firstSpecialChar,
                 uint16_t lastSpecialChar,
                 Encoding_t encoding);

        uint32_t toCodePoint(char c) const;

        uint32_t fromCodePoint(uint32_t c) const;

        Encoding_t encoding() const;
    private:
        const std::pair<uint32_t, uint32_t>* m_FromCodePoint;
        const uint32_t* m_FromChar;
        Encoding_t m_Encoding;
        uint16_t m_FirstSpecialChar;
        uint16_t m_LastSpecialChar;
    };

    YSTRING_API CodePage makeCodePage(Encoding_t encoding);
}}
