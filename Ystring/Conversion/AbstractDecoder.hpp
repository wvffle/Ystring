//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-10-26
//
// This file is distributed under the BSD License.
// License text is included with the source distribution.
//****************************************************************************
#pragma once
#include <cstdint>
#include <string>
#include "../DecoderResult.hpp"
#include "../Encoding.hpp"
#include "ErrorHandlingPolicy.hpp"

namespace Ystring { namespace Conversion {

    class AbstractDecoder
    {
    public:
        virtual ~AbstractDecoder();

        Encoding_t encoding() const;

        const std::string& encodingName() const;

        ErrorHandlingPolicy_t errorHandlingPolicy() const;

        void setErrorHandlingPolicy(ErrorHandlingPolicy_t value);

        virtual char32_t replacementCharacter() const;

        virtual void setReplacementCharacter(char32_t value);

        bool supports8BitStrings() const;

        bool supports16BitStrings() const;

        bool supports32BitStrings() const;

        bool incompleteCharactersAreInvalid() const;

        void setIncompleteCharactersAreInvalid(bool value);

        DecoderResult_t decode(const char*& srcBeg,
                               const char* srcEnd,
                               char32_t*& dstBeg,
                               char32_t* dstEnd,
                               bool isIncomplete);

        DecoderResult_t decode(const char16_t*& srcBeg,
                               const char16_t* srcEnd,
                               char32_t*& dstBeg,
                               char32_t* dstEnd,
                               bool isIncomplete);

        DecoderResult_t decode(const char32_t*& srcBeg,
                               const char32_t* srcEnd,
                               char32_t*& dstBeg,
                               char32_t* dstEnd,
                               bool isIncomplete);

    protected:
        enum Flags
        {
            SUPPORTS_8_BIT = 1,
            SUPPORTS_16_BIT = 2,
            SUPPORTS_32_BIT = 4,
            SUPPORTS_8_AND_16_BIT = SUPPORTS_8_BIT | SUPPORTS_16_BIT,
            SUPPORTS_8_AND_32_BIT = SUPPORTS_8_BIT | SUPPORTS_32_BIT,
            SUPPORTS_ALL = SUPPORTS_8_AND_16_BIT | SUPPORTS_32_BIT
        };

        AbstractDecoder(Encoding_t encoding, int flags);

        virtual DecoderResult_t doDecode(
                const char*& srcBeg, const char* srcEnd,
                char32_t*& dstBeg, char32_t* dstEnd);

        virtual DecoderResult_t doDecode(
                const char16_t*& srcBeg, const char16_t* srcEnd,
                char32_t*& dstBeg, char32_t* dstEnd);

        virtual DecoderResult_t doDecode(
                const char32_t*& srcBeg, const char32_t* srcEnd,
                char32_t*& dstBeg, char32_t* dstEnd);

        virtual void skipInvalidCharacter(
                const char*& srcBeg, const char* srcEnd);

        virtual void skipInvalidCharacter(
                const char16_t*& srcBeg, const char16_t* srcEnd);

        virtual void skipInvalidCharacter(
                const char32_t*& srcBeg, const char32_t* srcEnd);

        bool stopOnErrors() const;

    private:
        Encoding_t m_Encoding;
        char32_t m_ReplacementCharacter;
        int m_Flags;
        ErrorHandlingPolicy_t m_ErrorHandlingPolicy;
        bool m_IncompleteCharactersAreInvalid;
    };

}}
