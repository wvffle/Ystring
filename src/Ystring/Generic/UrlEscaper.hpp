//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-09-06
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#pragma once

#include <stdint.h>
#include "../Utilities/Utilities.hpp"
#include "../../../include/Ystring/YstringException.hpp"

namespace Ystring { namespace EncodedString
{
    inline bool isUrlQueryEscape(char32_t c)
    {
        return !('0' <= c && c <= '9') &&
               !('A' <= c && c <= 'Z') &&
               !('a' <= c && c <= 'z') &&
               !(c == '-' || c == '.' || c == '_' || c == '~');
    }

    class UrlEscaper
    {
    public:
        template<typename Appender>
        void escape(Appender dst, char32_t chr)
        {
            if (chr > 256)
                YSTRING_THROW(
                        "Can only escape single bytes. "
                        "Convert the string to UTF-8 before escaping it.");
            using Utilities::toCharDigit;
            dst.append('%');
            dst.append(toCharDigit((chr >> 4) & 0xF));
            dst.append(toCharDigit(chr & 0xF));
        }
    };
}}
