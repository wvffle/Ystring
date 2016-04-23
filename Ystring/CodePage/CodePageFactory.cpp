//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-09-19.
//
// This file is distributed under the BSD License.
// License text is included with the source distribution.
//****************************************************************************
#include "CodePageFactory.hpp"

#include <algorithm>
#include <numeric>

namespace Ystring { namespace CodePage
{
    CodePageFactory::CodePageFactory(
            const std::pair<uint8_t, char32_t>* firstSpecialChar,
            const std::pair<uint8_t, char32_t>* lastSpecialChar,
            Encoding_t encoding)
        : m_Encoding(encoding)
    {
        m_FirstSpecialChar = 256;
        m_LastSpecialChar = 0;
        for (auto it = firstSpecialChar; it != lastSpecialChar; ++it)
        {
            if (it->first != it->second)
            {
                if (it->first < m_FirstSpecialChar)
                    m_FirstSpecialChar = it->first;
                if (it->first  > m_LastSpecialChar)
                    m_LastSpecialChar = it->first;
            }
        }
        if (m_LastSpecialChar < m_FirstSpecialChar)
            m_LastSpecialChar = m_FirstSpecialChar;
        m_FromChar.resize(m_LastSpecialChar - m_FirstSpecialChar + 1);
        iota(begin(m_FromChar), end(m_FromChar), m_FirstSpecialChar);

        for (auto i = m_FirstSpecialChar; i <= m_LastSpecialChar; ++i)
            m_FromCodePoint.push_back(std::make_pair(i, i));
        for (auto it = firstSpecialChar; it != lastSpecialChar; ++it)
        {
            if (it->first < m_FirstSpecialChar
				|| m_LastSpecialChar < it->first)
            {
                continue;
            }
            auto index = it->first - m_FirstSpecialChar;
            m_FromChar[index] = it->second;
            m_FromCodePoint[index].first = it->second;
        }
        sort(begin(m_FromCodePoint), end(m_FromCodePoint));
    }

    CodePage CodePageFactory::makeCodePage()
    {
        return CodePage(m_FromCodePoint.data(), m_FromChar.data(),
                        m_FirstSpecialChar, m_LastSpecialChar, m_Encoding);
    }
}}
