//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-05-31
//
// This file is distributed under the BSD License.
// License text is included with the source distribution.
//****************************************************************************
#pragma once

#include "../Encoding.hpp"
#include "DecodeUtf8.hpp"
#include "EncodeUtf8.hpp"

namespace Ystring { namespace Utf8 {

class Utf8Encoding
{
public:
    static const Encoding_t encoding = Encoding::UTF_8;

    template <typename FwdIt>
    bool next(uint32_t& codePoint, FwdIt& it, FwdIt last)
    {
        switch (nextUtf8CodePoint(codePoint, it, last))
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
        return skipNextUtf8CodePoint(it, last);
    }

    template <typename BiIt>
    bool prevCodePoint(uint32_t& codePoint, BiIt first, BiIt& it)
    {
        switch (prevUtf8CodePoint(codePoint, first, it))
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
    bool skipPrev(uint32_t& codePoint, BiIt first, BiIt& it)
    {
        return skipPrevUtf8CodePoint(first, it);
    }

    template <typename OutIt>
    OutIt encode(OutIt dst, uint32_t codePoint)
    {
        return addUtf8(dst, codePoint);
    }
};

}}
