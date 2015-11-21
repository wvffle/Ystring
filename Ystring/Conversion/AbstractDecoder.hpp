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

        size_t characterUnitSize() const;

        Encoding_t encoding() const;

        const std::string& encodingName() const;

        ErrorHandlingPolicy_t errorHandlingPolicy() const;

        void setErrorHandlingPolicy(ErrorHandlingPolicy_t value);

        virtual char32_t replacementCharacter() const;

        virtual void setReplacementCharacter(char32_t value);

        DecoderResult_t decode(const char*& srcBeg,
                               const char* srcEnd,
                               char32_t*& dstBeg,
                               char32_t* dstEnd,
                               bool sourceIsIncomplete);

        DecoderResult_t decode(const char16_t*& srcBeg,
                               const char16_t* srcEnd,
                               char32_t*& dstBeg,
                               char32_t* dstEnd,
                               bool sourceIsIncomplete);

        DecoderResult_t decode(const char32_t*& srcBeg,
                               const char32_t* srcEnd,
                               char32_t*& dstBeg,
                               char32_t* dstEnd,
                               bool sourceIsIncomplete);

    protected:
        AbstractDecoder(Encoding_t encoding);

        template <typename CharT>
        DecoderResult_t decodeImpl(const CharT*& srcBeg,
                                   const CharT* srcEnd,
                                   char32_t*& dstBeg,
                                   char32_t* dstEnd,
                                   bool isIncomplete);

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
        ErrorHandlingPolicy_t m_ErrorHandlingPolicy;
    };

}}
