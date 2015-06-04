//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-06-02
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#pragma once

namespace Ystring {

struct Encoding
{
    enum Type
    {
        UNKNOWN,

        ASCII,
        UTF_8,
        LATIN_1,
        WINDOWS_1252,
        UTF_16_BE,
        UTF_16_LE,
        UTF_16 = UTF_16_LE,
        UTF_32_BE,
        UTF_32_LE,
        UTF_32 = UTF_32_LE,
        UTF_7,
        UTF_1,
        UTF_EBCDIC,
        SCSU,
        BOCU1,
        UCS_2,
        GB_18030,
        UNSPECIFIED_CODE_PAGE, ///< Generic 8-bit encoding

        MAXIMUM
    };
};

typedef Encoding::Type Encoding_t;

}
