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

namespace Ystring { namespace Utf8 {

class Utf16Encoding
{
public:
    static const Encoding_t encoding = Encoding::UTF_8;
    typedef char CanonicalType;

    template <typename FwdIt>
    bool next(uint32_t& codePoint, FwdIt& it, FwdIt last)
    {
        switch (nextUtf16CodePoint(codePoint, it, last))
        {
            case DecodeResult::END_OF_STRING:
                return false;
            case DecodeResult::INCOMPLETE:
                throw std::logic_error("Incomplete character.");
            case DecodeResult::INVALID:
                throw std::logic_error("Invalid character.");
            default:
                break;
        }
        return true;
    }

    template <typename FwdIt>
    bool skipNext(FwdIt& it, FwdIt last)
    {
        return skipNextUtf16CodePoint(it, last);
    }

    template <typename BiIt>
    bool prev(uint32_t& codePoint, BiIt first, BiIt& it)
    {
        switch (prevUtf16CodePoint(codePoint, first, it))
        {
            case DecodeResult::END_OF_STRING:
                return false;
            case DecodeResult::INCOMPLETE:
                throw std::logic_error("Incomplete character.");
            case DecodeResult::INVALID:
                throw std::logic_error("Invalid character.");
            default:
                break;
        }
        return true;
    }

    template <typename BiIt>
    bool skipPrev(BiIt first, BiIt& it)
    {
        return skipPrevUtf16CodePoint(first, it);
    }

    template <typename OutIt>
    OutIt encode(OutIt dst, uint32_t codePoint)
    {
        return addUtf16(dst, codePoint);
    }
};

}}
