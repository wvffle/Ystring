//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-07-08
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#pragma once

#include "../Encoding.hpp"
#include "DecodeUtf16.hpp"
#include "EncodeUtf16.hpp"

namespace Ystring { namespace Utf16 {

template <bool SwapBytes>
class Utf16EncodingImpl
{
public:
    static const Encoding_t encoding = Encoding::UTF_8;
    typedef wchar_t CanonicalType;

    template <typename FwdIt>
    bool next(uint32_t& codePoint, FwdIt& it, FwdIt last)
    {
        switch (nextUtf16CodePoint<FwdIt, SwapBytes>(codePoint, it, last))
        {
            case DecoderResult::END_OF_STRING:
                return false;
            case DecoderResult::INCOMPLETE:
                throw std::logic_error("Incomplete character.");
            case DecoderResult::INVALID:
                throw std::logic_error("Invalid character.");
            default:
                break;
        }
        return true;
    }

    template <typename BiIt>
    bool prev(uint32_t& codePoint, BiIt first, BiIt& it)
    {
        switch (prevUtf16CodePoint<BiIt, SwapBytes>(codePoint, first, it))
        {
            case DecoderResult::END_OF_STRING:
                return false;
            case DecoderResult::INCOMPLETE:
                throw std::logic_error("Incomplete character.");
            case DecoderResult::INVALID:
                throw std::logic_error("Invalid character.");
            default:
                break;
        }
        return true;
    }

    template <typename FwdIt>
    bool skipNext(FwdIt& it, FwdIt last)
    {
        return skipNextUtf16CodePoint<FwdIt, SwapBytes>(it, last);
    }

    template <typename BiIt>
    bool skipPrev(BiIt first, BiIt& it)
    {
        return skipPrevUtf16CodePoint<BiIt, SwapBytes>(first, it);
    }

    template <typename OutIt>
    OutIt encode(OutIt dst, uint32_t codePoint)
    {
        return addUtf16(dst, codePoint);
    }

    template <typename OutIt>
    OutIt encodeAsBytes(OutIt dst, uint32_t codePoint)
    {
        return addUtf16AsBytes<SwapBytes>(dst, codePoint);
    }
};

typedef Utf16EncodingImpl<false> Utf16Encoding;
typedef Utf16EncodingImpl<Utilities::IsBigEndian> Utf16LEEncoding;
typedef Utf16EncodingImpl<Utilities::IsLittleEndian> Utf16BEEncoding;

}}
