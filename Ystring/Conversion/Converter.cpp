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
#include "Utf16LEDecoder.hpp"
#include "Utf16LEEncoder.hpp"

namespace Ystring { namespace Conversion {

    namespace {

        const size_t DEFAULT_BUFFER_SIZE = 256;

        std::unique_ptr<AbstractDecoder> makeDecoder(Encoding_t encoding);

        std::unique_ptr<AbstractEncoder> makeEncoder(Encoding_t encoding);

        template <typename T>
        void swapEndianness(T* str, size_t length);

    }

    Converter::Converter(Encoding_t srcEncoding, Encoding_t dstEncoding)
        : m_Decoder(makeDecoder(srcEncoding)),
          m_Encoder(makeEncoder(dstEncoding)),
          m_ConversionType(getConversionType(srcEncoding, dstEncoding)),
          m_BufferSize(DEFAULT_BUFFER_SIZE)
    {}

    size_t Converter::bufferSize() const
    {
        return m_BufferSize;
    }

    void Converter::setBufferSize(size_t value)
    {
        m_BufferSize = value;
    }

    void Converter::setErrorHandlingPolicy(ErrorHandlingPolicy_t value)
    {
        setDecoderErrorHandlingPolicy(value);
        setEncoderErrorHandlingPolicy(value);
    }

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

    void Converter::setReplacementCharacter(char32_t value)
    {
        setDecoderReplacementCharacter(value);
        setEncoderReplacementCharacter(value);
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

    size_t Converter::convert(const char* source,
                              size_t sourceLength,
                              std::u16string& destination,
                              bool sourceIsIncomplete)
    {
        return convertImpl(source,
                           sourceLength,
                           destination,
                           sourceIsIncomplete);
    }

    size_t Converter::convert(const char16_t* source,
                              size_t sourceLength,
                              std::string& destination,
                              bool sourceIsIncomplete)
    {
        return convertImpl(source,
                           sourceLength,
                           destination,
                           sourceIsIncomplete);
    }

    size_t Converter::convert(const char16_t* source,
                              size_t sourceLength,
                              std::u16string& destination,
                              bool sourceIsIncomplete)
    {
        return convertImpl(source,
                           sourceLength,
                           destination,
                           sourceIsIncomplete);
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


    template<typename CharT, typename StringT>
    size_t Converter::convertImpl(const CharT* src,
                                  size_t srcLength,
                                  StringT& dst,
                                  bool sourceIsIncomplete)
    {
        auto srcBeg = src;
        auto srcEnd = src + srcLength;
        if (m_ConversionType == COPY)
        {
            if (sizeof(CharT) == sizeof(typename StringT::value_type))
            {
                std::copy(srcBeg, srcEnd, back_inserter(dst));
                return srcLength;
            }
        }
        else if (m_ConversionType == SWAP_ENDIANNESS)
        {
            if (sizeof(CharT) == sizeof(typename StringT::value_type))
            {
                auto originalSize = dst.size();
                std::copy(srcBeg, srcEnd, back_inserter(dst));
                swapEndianness(dst.data() + originalSize, srcLength);
                return srcLength;
            }
        }
        auto bufSize = std::min(srcLength, m_BufferSize);
        std::vector<char32_t> buffer(bufSize);
        auto bufEnd = buffer.data() + bufSize;
        while (srcBeg != srcEnd)
        {
            auto bufIt = buffer.data();
            auto result = m_Decoder->decode(srcBeg, srcEnd, bufIt, bufEnd,
                                            sourceIsIncomplete);
            auto bufBeg = static_cast<const char32_t*>(buffer.data());
            m_Encoder->encode(bufBeg, bufIt, dst);
            if (result != DecoderResult::OK)
                break;
        }
        return srcBeg - src;
    }

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
            case Encoding::UTF_16_LE:
                return std::unique_ptr<AbstractDecoder>(new Utf16LEDecoder);
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

        template <typename T>
        void swapEndianness(T* str, size_t length)
        {
            for (size_t i = 0; i < length; ++i)
                Utilities::reverseBytes(str[i]);
        }

    }
}}
