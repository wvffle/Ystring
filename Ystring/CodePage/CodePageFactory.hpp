//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-09-19.
//
// This file is distributed under the BSD License.
// License text is included with the source distribution.
//****************************************************************************
#pragma once
#include <cstdint>
#include <vector>
#include "../Encoding.hpp"
#include "CodePage.hpp"

namespace Ystring { namespace CodePage
{
    class CodePageFactory
    {
    public:
        CodePageFactory(const std::pair<uint8_t, uint32_t>* firstSpecialChar,
                        const std::pair<uint8_t, uint32_t>* lastSpecialChar,
                        Encoding_t encoding);
        CodePage makeCodePage();
    private:
        std::vector<std::pair<uint32_t, uint32_t>> m_FromCodePoint;
        std::vector<uint32_t> m_FromChar;
        Encoding_t m_Encoding;
        uint16_t m_FirstSpecialChar;
        uint16_t m_LastSpecialChar;
    };
}}
