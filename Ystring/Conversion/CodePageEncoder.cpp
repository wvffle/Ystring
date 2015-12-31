//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-11-22
//
// This file is distributed under the BSD License.
// License text is included with the source distribution.
//****************************************************************************
#include "CodePageEncoder.hpp"
#include "../Unicode/UnicodeChars.hpp"
#include "../YstringException.hpp"

namespace Ystring { namespace Conversion {

    CodePageEncoder::CodePageEncoder(Encoding_t encoding)
        : AbstractEncoder(encoding),
          m_CodePage(CodePage::makeCodePage(encoding))
    {
        // Use ? as replacement character unless the code page supports
        // unicode's designated replacement character.
        setReplacementCharacter('?');
        setReplacementCharacter(Unicode::REPLACEMENT_CHARACTER);
    }

    void CodePageEncoder::setReplacementCharacter(char32_t value)
    {
        if (m_CodePage.fromCodePoint(value) == INVALID_CHAR)
            AbstractEncoder::setReplacementCharacter(value);
    }

    bool CodePageEncoder::doEncode(const char32_t*& srcBeg,
                                   const char32_t* srcEnd,
                                   std::string& dst)
    {
        while (srcBeg != srcEnd)
        {
            auto ch = m_CodePage.fromCodePoint(*srcBeg);
            if (ch != INVALID_CHAR)
            {
                dst.push_back(ch);
            }
            else
            {
                switch (errorHandlingPolicy())
                {
                case ErrorHandlingPolicy::REPLACE:
                    dst.push_back(char(replacementCharacter()));
                    break;
                case ErrorHandlingPolicy::STOP:
                    return false;
                case ErrorHandlingPolicy::THROW:
                    YSTRING_THROW("Unsupported code point "
                                  + std::to_string(int64_t(*srcBeg)));
                case ErrorHandlingPolicy::SKIP:
                    break;
                }
            }
            ++srcBeg;
        }
        return true;
    }

}}
