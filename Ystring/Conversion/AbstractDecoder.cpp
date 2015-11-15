//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-10-26
//
// This file is distributed under the BSD License.
// License text is included with the source distribution.
//****************************************************************************
#include "AbstractDecoder.hpp"

#include "../YstringException.hpp"
#include "../EncodingInfo.hpp"
#include "../Unicode/UnicodeChars.hpp"

namespace Ystring { namespace Conversion {

    AbstractDecoder::AbstractDecoder(Encoding_t encoding, int flags)
        : m_Encoding(encoding),
          m_ReplacementCharacter(Unicode::REPLACEMENT_CHARACTER),
          m_Flags(flags),
          m_ErrorHandlingPolicy(),
          m_IncompleteCharactersAreInvalid(true)
    {}

    AbstractDecoder::~AbstractDecoder()
    {}

    Encoding_t AbstractDecoder::encoding() const
    {
        return m_Encoding;
    }

    const std::string& AbstractDecoder::encodingName() const
    {
        auto info = getEncodingInfo(m_Encoding);
        if (info)
            return info->name();

        static std::string defaultName = "Unknown";
        return defaultName;
    }

    ErrorHandlingPolicy_t AbstractDecoder::errorHandlingPolicy() const
    {
        return m_ErrorHandlingPolicy;
    }

    void AbstractDecoder::setErrorHandlingPolicy(ErrorHandlingPolicy_t value)
    {
        m_ErrorHandlingPolicy = value;
    }

    char32_t AbstractDecoder::replacementCharacter() const
    {
        return m_ReplacementCharacter;
    }

    void AbstractDecoder::setReplacementCharacter(char32_t value)
    {
        m_ReplacementCharacter = value;
    }

    bool AbstractDecoder::supports8BitStrings() const
    {
        return (m_Flags & SUPPORTS_8_BIT) != 0;
    }

    bool AbstractDecoder::supports16BitStrings() const
    {
        return (m_Flags & SUPPORTS_16_BIT) != 0;
    }

    bool AbstractDecoder::supports32BitStrings() const
    {
        return (m_Flags & SUPPORTS_32_BIT) != 0;
    }

    bool AbstractDecoder::incompleteCharactersAreInvalid() const
    {
        return m_IncompleteCharactersAreInvalid;
    }

    void AbstractDecoder::setIncompleteCharactersAreInvalid(bool value)
    {
        m_IncompleteCharactersAreInvalid = value;
    }

    DecoderResult_t AbstractDecoder::decode(const char*& srcBeg,
                                            const char* srcEnd,
                                            char32_t*& dstBeg,
                                            char32_t* dstEnd,
                                            bool sourceIsIncomplete)
    {
        while (true)
        {
            auto result = doDecode(srcBeg, srcEnd, dstBeg, dstEnd);
            if (result == DecoderResult::OK
                || result == DecoderResult::END_OF_STRING)
            {
                return DecoderResult::OK;
            }
            if (result == DecoderResult::INCOMPLETE && sourceIsIncomplete)
                return DecoderResult::INCOMPLETE;

            switch (m_ErrorHandlingPolicy)
            {
            case ErrorHandlingPolicy::REPLACE:
                *dstBeg++ = m_ReplacementCharacter;
                skipInvalidCharacter(srcBeg, srcEnd);
                break;
            case ErrorHandlingPolicy::STOP:
                return DecoderResult::INVALID;
            case ErrorHandlingPolicy::THROW:
                YSTRING_THROW("Invalid character starting at index "
                              + std::to_string(srcBeg - srcEnd));
            case ErrorHandlingPolicy::SKIP:
                skipInvalidCharacter(srcBeg, srcEnd);
                break;
            }
        }
    }

    DecoderResult_t AbstractDecoder::decode(const char16_t*&,
                                            const char16_t*,
                                            char32_t*&,
                                            char32_t*,
                                            bool sourceIsIncomplete)
    {
        return DecoderResult::OK;
    }

    DecoderResult_t AbstractDecoder::decode(const char32_t*&,
                                            const char32_t*,
                                            char32_t*&,
                                            char32_t*,
                                            bool sourceIsIncomplete)
    {
        return DecoderResult::OK;
    }

    DecoderResult_t AbstractDecoder::doDecode(const char*& srcBeg,
                                              const char* srcEnd,
                                              char32_t*& dstBeg,
                                              char32_t* dstEnd)
    {
        YSTRING_THROW(encodingName()
                      + "-decoder doesn't support 8-bit strings.");
    }

    DecoderResult_t AbstractDecoder::doDecode(const char16_t*& srcBeg,
                                              const char16_t* srcEnd,
                                              char32_t*& dstBeg,
                                              char32_t* dstEnd)
    {
        YSTRING_THROW(encodingName()
                      + "-decoder doesn't support 16-bit strings.");
    }

    DecoderResult_t AbstractDecoder::doDecode(const char32_t*& srcBeg,
                                              const char32_t* srcEnd,
                                              char32_t*& dstBeg,
                                              char32_t* dstEnd)
    {
        YSTRING_THROW(encodingName()
                      + "-decoder doesn't support 32-bit strings.");
    }

    void AbstractDecoder::skipInvalidCharacter(
            const char*& srcBeg, const char* srcEnd)
    {
        YSTRING_THROW(encodingName()
                      + "-decoder doesn't support 8-bit strings.");
    }

    void AbstractDecoder::skipInvalidCharacter(
            const char16_t*& srcBeg, const char16_t* srcEnd)
    {
        YSTRING_THROW(encodingName()
                      + "-decoder doesn't support 16-bit strings.");
    }

    void AbstractDecoder::skipInvalidCharacter(
            const char32_t*& srcBeg, const char32_t* srcEnd)
    {
        YSTRING_THROW(encodingName()
                      + "-decoder doesn't support 32-bit strings.");
    }

    bool AbstractDecoder::stopOnErrors() const
    {
        return m_ErrorHandlingPolicy != ErrorHandlingPolicy::STOP;
    }
}}
