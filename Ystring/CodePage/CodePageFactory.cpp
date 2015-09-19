//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-09-19.
//
// This file is distributed under the BSD License.
// License text is included with the source distribution.
//****************************************************************************
#include "CodePageFactory.hpp"

#include <numeric>

namespace Ystring { namespace CodePage
{
    CodePageFactory::CodePageFactory(
            const std::pair<uint8_t, uint32_t>* firstSpecialChar,
            const std::pair<uint8_t, uint32_t>* lastSpecialChar,
            Encoding_t encoding)
        : m_Encoding(encoding)
    {
        m_FirstSpecialChar = 256;
        for (auto it = firstSpecialChar; it != lastSpecialChar; ++it)
        {
            if (it->first != it->second && it->first < m_FirstSpecialChar)
                m_FirstSpecialChar = it->first;
        }
        m_FromChar.resize(256u - m_FirstSpecialChar);
        iota(begin(m_FromChar), end(m_FromChar), m_FirstSpecialChar);
        for (auto it = firstSpecialChar; it != lastSpecialChar; ++it)
        {
            if (it->first < m_FirstSpecialChar)
                continue;
            m_FromChar[it->first - m_FirstSpecialChar] = it->second;
            m_FromCodePoint.push_back(std::make_pair(it->second, it->first));
        }
        sort(begin(m_FromCodePoint), end(m_FromCodePoint));
    }

    CodePage CodePageFactory::makeCodePage()
    {
        return CodePage(m_FromCodePoint.data(), m_FromChar.data(),
                        m_FirstSpecialChar, m_Encoding);
    }
}}
