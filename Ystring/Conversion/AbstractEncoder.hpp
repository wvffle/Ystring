//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 27.10.2015
//
// This file is distributed under the BSD License.
// License text is included with the source distribution.
//****************************************************************************
#pragma once

#include <string>
#include "../Encoding.hpp"
#include "ErrorHandlingPolicy.hpp"

namespace Ystring { namespace Conversion {

    class AbstractEncoder
    {
    public:
        virtual ~AbstractEncoder();

        Encoding_t encoding() const;

        const std::string& encodingName() const;

        ErrorHandlingPolicy_t errorHandlingPolicy() const;

        void setErrorHandlingPolicy(ErrorHandlingPolicy_t value);

        virtual char32_t replacementCharacter() const;

        virtual void setReplacementCharacter(char32_t value);

        void encode(std::string& dst,
                    const char32_t*& srcBeg, const char32_t* srcEnd);

        void encode(std::u16string& dst,
                    const char32_t*& srcBeg, const char32_t* srcEnd);

//        void encode(std::u32string& dst,
//                    const char32_t*& srcBeg, const char32_t* srcEnd);

    protected:
        AbstractEncoder(Encoding_t encoding);

        virtual void doEncode(
                std::string& dst,
                const char32_t*& srcBeg, const char32_t* srcEnd);

        virtual void doEncode(
                std::u16string& dst,
                const char32_t*& srcBeg, const char32_t* srcEnd);

//        virtual void doEncode(
//                std::u32string& dst,
//                const char32_t*& srcBeg, const char32_t* srcEnd);

    private:
        Encoding_t m_Encoding;
        ErrorHandlingPolicy_t m_ErrorHandlingPolicy;
        char32_t m_ReplacementCharacter;
    };

}}
