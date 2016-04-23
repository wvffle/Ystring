//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-07-21
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#include "CodePage.hpp"
#include "../YstringException.hpp"
#include "../Utilities/KeyFunctionAlgorithms.hpp"
#include "Ibm437.hpp"
#include "Ibm850.hpp"
#include "Iso8859_1.hpp"
#include "Iso8859_9.hpp"
#include "Iso8859_10.hpp"
#include "Iso8859_15.hpp"
#include "Windows1250.hpp"
#include "Windows1252.hpp"

namespace Ystring { namespace CodePage
{
    CodePage::CodePage(Encoding_t encoding)
        : m_FromCodePoint(nullptr),
          m_FromChar(nullptr),
          m_Encoding(encoding),
          m_FirstSpecialChar(256),
          m_LastSpecialChar(256)
    {}

    CodePage::CodePage(const std::pair<char32_t, char32_t>* fromCodePoint,
                       const char32_t* fromChar,
                       char16_t firstSpecialChar,
                       char16_t lastSpecialChar,
                       Encoding_t encoding)
        : m_FromCodePoint(fromCodePoint),
          m_FromChar(fromChar),
          m_Encoding(encoding),
          m_FirstSpecialChar(firstSpecialChar),
          m_LastSpecialChar(lastSpecialChar)
    {}

    char32_t CodePage::toCodePoint(char c) const
    {
        auto uc = uint8_t(c);
        if (uc < m_FirstSpecialChar || uc > m_LastSpecialChar)
            return uc;
        return m_FromChar[uc - m_FirstSpecialChar];
    }

    char32_t CodePage::fromCodePoint(char32_t c) const
    {
        if (c < m_FirstSpecialChar || (m_LastSpecialChar < c && c < 256))
            return c;
        auto n = m_LastSpecialChar - m_FirstSpecialChar + 1;
        auto it = Utilities::binaryFind(
                m_FromCodePoint, m_FromCodePoint + n, c,
                [](const std::pair<char32_t, char>& p) { return p.first; });
        if (it != m_FromCodePoint + n)
            return it->second;
        return INVALID_CHAR;
    }

    Encoding_t CodePage::encoding() const
    {
        return m_Encoding;
    }

    CodePage makeCodePage(Encoding_t encoding)
    {
        switch (encoding)
        {
        case Encoding::ASCII:
        case Encoding::ISO_8859_1:
            return makeIso8859_1();
        case Encoding::ISO_8859_9:
            return makeIso8859_9();
        case Encoding::ISO_8859_10:
            return makeIso8859_10();
        case Encoding::ISO_8859_15:
            return makeIso8859_15();
        case Encoding::WINDOWS_1250:
            return makeWindows1250();
        case Encoding::WINDOWS_1252:
            return makeWindows1252();
        case Encoding::IBM_437:
            return makeIbm437();
        case Encoding::IBM_850:
            return makeIbm850();
        default:
            break;
        }
        YSTRING_THROW("Unsupported code page encoding.");
    }
}}
