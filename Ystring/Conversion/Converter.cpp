//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-10-23
//
// This file is distributed under the BSD License.
// License text is included with the source distribution.
//****************************************************************************
#include "Converter.hpp"

#include <vector>
#include "../EncodingInfo.hpp"
#include "../Generic/GenericConvert.hpp"
#include "Utf8Decoder.hpp"
#include "Utf8Encoder.hpp"
#include "Utf16LEEncoder.hpp"

namespace Ystring { namespace Conversion {

    const size_t CONV_MAX_BUFFER = 256;

    namespace {

        std::unique_ptr<AbstractDecoder> makeDecoder(Encoding_t encoding)
        {
            switch (encoding)
            {
            case Encoding::ASCII:break;
            case Encoding::UTF_8:
                return std::unique_ptr<AbstractDecoder>(new Utf8Decoder);
            case Encoding::ISO_8859_1:break;
            case Encoding::ISO_8859_15:break;
            case Encoding::WINDOWS_1252:break;
            case Encoding::CP_437:break;
            case Encoding::UTF_16_BE:break;
            case Encoding::UTF_16_LE:break;
            case Encoding::UTF_32_BE:break;
            case Encoding::UTF_32_LE:break;
            case Encoding::UNKNOWN:
                break;
            case Encoding::UTF_7:break;
            case Encoding::UTF_1:break;
            case Encoding::UTF_EBCDIC:break;
            case Encoding::SCSU:break;
            case Encoding::BOCU_1:break;
            case Encoding::UCS_2:break;
            case Encoding::GB_18030:break;
            case Encoding::UNSPECIFIED_SINGLE_BYTE_CHARACTER_SET:break;
            case Encoding::MAXIMUM:break;
            }

            auto info = getEncodingInfo(encoding);
            auto name = info ? info->name() : std::to_string(encoding);
            YSTRING_THROW("Unsupported source-encoding: " + name);
        }

        std::unique_ptr<AbstractEncoder> makeEncoder(Encoding_t encoding)
        {
            switch (encoding)
            {
            case Encoding::ASCII:break;
            case Encoding::UTF_8:
                return std::unique_ptr<AbstractEncoder>(new Utf8Encoder);
            case Encoding::ISO_8859_1:break;
            case Encoding::ISO_8859_15:break;
            case Encoding::WINDOWS_1252:break;
            case Encoding::CP_437:break;
            case Encoding::UTF_16_BE:break;
            case Encoding::UTF_16_LE:
                return std::unique_ptr<AbstractEncoder>(new Utf16LEEncoder);
            case Encoding::UTF_32_BE:break;
            case Encoding::UTF_32_LE:break;
            case Encoding::UNKNOWN:
                break;
            case Encoding::UTF_7:break;
            case Encoding::UTF_1:break;
            case Encoding::UTF_EBCDIC:break;
            case Encoding::SCSU:break;
            case Encoding::BOCU_1:break;
            case Encoding::UCS_2:break;
            case Encoding::GB_18030:break;
            case Encoding::UNSPECIFIED_SINGLE_BYTE_CHARACTER_SET:break;
            case Encoding::MAXIMUM:break;
            }

            auto info = getEncodingInfo(encoding);
            auto name = info ? info->name() : std::to_string(encoding);
            YSTRING_THROW("Unsupported source-encoding: " + name);
        }

//        template <typename T>
//        void swapEndianness(T* str, size_t length)
//        {
//            for (size_t i = 0; i < length; ++i)
//                Utilities::swapEndianness(str[i]);
//        }
//
    }

    Converter::Converter(Encoding_t srcEncoding, Encoding_t dstEncoding)
        : m_Decoder(makeDecoder(srcEncoding)),
          m_Encoder(makeEncoder(dstEncoding)),
          m_ConversionType(getConversionType(srcEncoding, dstEncoding))
    {}

    ErrorHandlingPolicy_t Converter::decoderErrorHandlingPolicy() const
    {
        return m_Decoder->errorHandlingPolicy();
    }

    void Converter::setDecoderErrorHandlingPolicy(ErrorHandlingPolicy_t value)
    {
        m_Decoder->setErrorHandlingPolicy(value);
    }

    ErrorHandlingPolicy_t Converter::encoderErrorHandlingPolicy() const
    {
        return m_Encoder->errorHandlingPolicy();
    }

    void Converter::setEncoderErrorHandlingPolicy(ErrorHandlingPolicy_t value)
    {
        m_Encoder->setErrorHandlingPolicy(value);
    }

    char32_t Converter::decoderReplacementCharacter() const
    {
        return m_Decoder->replacementCharacter();
    }

    void Converter::setDecoderReplacementCharacter(char32_t value)
    {
        m_Decoder->setReplacementCharacter(value);
    }

    char32_t Converter::encoderReplacementCharacter() const
    {
        return m_Encoder->replacementCharacter();
    }

    void Converter::setEncoderReplacementCharacter(char32_t value)
    {
        m_Encoder->setReplacementCharacter(value);
    }

    void Converter::convert(const char* src,
                            size_t srcLength,
                            std::u16string& dst)
    {
        auto bufSize = std::min(srcLength, CONV_MAX_BUFFER);
        std::vector<char32_t> buffer(bufSize);
        auto srcBeg = src;
        auto srcEnd = src + srcLength;
        auto bufEnd = buffer.data() + bufSize;
        while (srcBeg != srcEnd)
        {
            auto bufIt = buffer.data();
            m_Decoder->decode(bufIt, bufEnd, srcBeg, srcEnd);
            auto bufBeg = static_cast<const char32_t*>(buffer.data());
            m_Encoder->encode(dst, bufBeg, bufIt);
        }
    }

    Converter::ConversionType Converter::getConversionType(
            Encoding_t src, Encoding_t dst)
    {
        if (src == dst)
            return COPY;
        if ((src == Encoding::UTF_16_LE && dst == Encoding::UTF_16_BE)
            || (src == Encoding::UTF_16_BE && dst == Encoding::UTF_16_LE)
            || (src == Encoding::UTF_32_LE && dst == Encoding::UTF_32_BE)
            || (src == Encoding::UTF_32_BE && dst == Encoding::UTF_32_LE))
        {
            return SWAP_ENDIANNESS;
        }
        return CONVERT;
    }
}}
