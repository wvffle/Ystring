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
#include "Ystring/Encoding.hpp"
#include "Ystring/YstringDefinitions.hpp"

namespace Ystring { namespace Encodings
{
    class YSTRING_API CodePage
    {
    public:
        explicit CodePage(Encoding_t encoding);
        CodePage(const std::pair<char32_t, char32_t>* fromCodePoint,
                 const char32_t* fromChar,
                 char16_t firstSpecialChar,
                 char16_t lastSpecialChar,
                 Encoding_t encoding);

        char32_t toCodePoint(char c) const;

        char32_t fromCodePoint(char32_t c) const;

        Encoding_t encoding() const;
    private:
        const std::pair<char32_t, char32_t>* m_FromCodePoint;
        const char32_t* m_FromChar;
        Encoding_t m_Encoding;
        char16_t m_FirstSpecialChar;
        char16_t m_LastSpecialChar;
    };

    YSTRING_API CodePage makeCodePage(Encoding_t encoding);
}}
