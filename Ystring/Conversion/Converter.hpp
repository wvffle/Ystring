//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-10-17
//
// This file is distributed under the BSD License.
// License text is included with the source distribution.
//****************************************************************************
#pragma once

#include <memory>
#include <string>
#include "../Encoding.hpp"
#include "../YstringDefinitions.hpp"
#include "AbstractDecoder.hpp"
#include "AbstractEncoder.hpp"
#include "ErrorHandlingPolicy.hpp"

namespace Ystring { namespace Conversion {

    // char
    // -wchar_t
    // char16_t
    // char32_t

    // string
    // wstring
    // u16string
    // u32string

    class YSTRING_API Converter
    {
    public:
        Converter(Encoding_t srcEncoding, Encoding_t dstEncoding);

        size_t bufferSize() const;

        void setBufferSize(size_t value);

        void setErrorHandlingPolicy(ErrorHandlingPolicy_t value);

        ErrorHandlingPolicy_t decoderErrorHandlingPolicy() const;

        void setDecoderErrorHandlingPolicy(ErrorHandlingPolicy_t value);

        ErrorHandlingPolicy_t encoderErrorHandlingPolicy() const;

        void setEncoderErrorHandlingPolicy(ErrorHandlingPolicy_t value);

        void setReplacementCharacter(char32_t value);

        char32_t decoderReplacementCharacter() const;

        void setDecoderReplacementCharacter(char32_t value);

        char32_t encoderReplacementCharacter() const;

        void setEncoderReplacementCharacter(char32_t value);

        //        void convert(const char* src, size_t srcLength, std::string& dst);

        size_t convert(const char* source,
                       size_t sourceLength,
                       std::u16string& destination,
                       bool sourceIsIncomplete = false);

//        void convert(const char* src, size_t srcLength, std::u32string& dst);

        size_t convert(const char16_t* source,
                       size_t sourceLength,
                       std::string& destination,
                       bool sourceIsIncomplete = false);

        size_t convert(const char16_t* source,
                       size_t sourceLength,
                       std::u16string& destination,
                       bool sourceIsIncomplete = false);

//        void convert(const char16_t* src, size_t srcLength,
//                     std::u32string& dst);
//
//        void convert(const char32_t* src, size_t srcLength,
//                     std::string& dst);
//
//        void convert(const char32_t* src, size_t srcLength,
//                     std::u16string& dst);
//
//        void convert(const char32_t* src, size_t srcLength,
//                     std::u32string& dst);
    private:
        enum ConversionType
        {
            CONVERT,
            COPY,
            SWAP_ENDIANNESS
        };

        static ConversionType getConversionType(Encoding_t srcEncoding,
                                                Encoding_t dstEncoding);

        template <typename CharT, typename StringT>
        size_t convertImpl(const CharT* src,
                           size_t srcLength,
                           StringT& dst,
                           bool sourceIsIncomplete);

        template<typename CharT, typename StringT>
        size_t doConvert(const CharT* src,
                         size_t srcLength,
                         StringT& dst,
                         bool sourceIsIncomplete);

        template<typename CharT, typename StringT>
        size_t doCopy(const CharT* src,
                      size_t srcLength,
                      StringT& dst,
                      bool sourceIsIncomplete);

        template<typename CharT, typename StringT>
        size_t doCopyAndSwapBytes(const CharT* src,
                                  size_t srcLength,
                                  StringT& dst,
                                  bool sourceIsIncomplete);

        std::unique_ptr<AbstractDecoder> m_Decoder;
        std::unique_ptr<AbstractEncoder> m_Encoder;
        ConversionType m_ConversionType;
        size_t m_BufferSize;
    };
}}
