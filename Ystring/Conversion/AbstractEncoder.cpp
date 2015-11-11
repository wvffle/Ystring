//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 27.10.2015
//
// This file is distributed under the BSD License.
// License text is included with the source distribution.
//****************************************************************************
#include "AbstractEncoder.hpp"

#include "../YstringException.hpp"
#include "../EncodingInfo.hpp"
#include "../Unicode/UnicodeChars.hpp"

namespace Ystring { namespace Conversion {

    AbstractEncoder::AbstractEncoder(Encoding_t encoding)
        : m_Encoding(encoding),
          m_ErrorHandlingPolicy(),
          m_ReplacementCharacter(Unicode::REPLACEMENT_CHARACTER)
    {}

    AbstractEncoder::~AbstractEncoder()
    {}

    Encoding_t AbstractEncoder::encoding() const
    {
        return m_Encoding;
    }

    const std::string& AbstractEncoder::encodingName() const
    {
        auto info = getEncodingInfo(m_Encoding);
        if (info)
            return info->name();

        static std::string defaultName = "Unknown";
        return defaultName;
    }

    ErrorHandlingPolicy_t AbstractEncoder::errorHandlingPolicy() const
    {
        return m_ErrorHandlingPolicy;
    }

    void AbstractEncoder::setErrorHandlingPolicy(ErrorHandlingPolicy_t value)
    {
        m_ErrorHandlingPolicy = value;
    }

    char32_t AbstractEncoder::replacementCharacter() const
    {
        return m_ReplacementCharacter;
    }

    void AbstractEncoder::setReplacementCharacter(char32_t value)
    {
        m_ReplacementCharacter = value;
    }

    void AbstractEncoder::encode(std::string& dst,
                                 const char32_t*& srcBeg,
                                 const char32_t* srcEnd)
    {
        doEncode(dst, srcBeg, srcEnd);
    }

    void AbstractEncoder::encode(std::u16string& dst,
                                 const char32_t*& srcBeg,
                                 const char32_t* srcEnd)
    {
        doEncode(dst, srcBeg, srcEnd);
    }

    void AbstractEncoder::doEncode(std::string& dst,
                                   const char32_t*& srcBeg,
                                   const char32_t* srcEnd)
    {
        YSTRING_THROW(encodingName()
                      + "-encoder doesn't support 8-bit strings.");
    }

    void AbstractEncoder::doEncode(std::u16string& dst,
                                   const char32_t*& srcBeg,
                                   const char32_t* srcEnd)
    {
        YSTRING_THROW(encodingName()
                      + "-encoder doesn't support 16-bit strings.");
    }
}}
