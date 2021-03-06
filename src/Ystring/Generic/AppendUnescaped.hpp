//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-07-21
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#pragma once

#include <stdexcept>
#include "Ystring/YstringDefinitions.hpp"
#include "Range.hpp"
#include "StringReference.hpp"
#include "ForwardDecoder.hpp"

namespace Ystring { namespace EncodedString
{
    inline bool isBackslash(char32_t c)
    {
        return c == '\\';
    }

    inline bool isAmpersand(char32_t c)
    {
        return c == '&';
    }

    template <typename Str, typename Enc, typename It, typename Unescaper>
    void appendUnescaped(Generic::StringReference<Str>& dst,
                         Generic::Range<It> src,
                         Enc encoding,
                         bool (*isEscaped)(char32_t),
                         Unescaper unescaper)
    {
        auto first = src.begin();
        auto last = std::find_if(first, src.end(), isEscaped);
        while (last != src.end())
        {
            dst.getAppender().append(Generic::makeRange(first, last));
            char32_t ch;
            first = last;
            if (unescaper.unescape(ch, first, src.end()))
                dst.getEncoder(encoding).encode(ch);
            last = std::find_if(first, src.end(), isEscaped);
        }
        dst.getAppender().append(Generic::makeRange(first, src.end()));
    }
}}
