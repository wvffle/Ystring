//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-07-28
//
// This file is distributed under the BSD License.
// License text is included with the source distribution.
//****************************************************************************
#pragma once

#ifdef _MSC_VER
    #define YSTRING_WCHAR_IS_2_BYTES
    #if _MSC_VER >= 1900
        #define YSTRING_CPP11_CHAR_TYPES_SUPPORTED
    #endif
#else
    static_assert(sizeof(wchar_t) == 4, "Size of wchar_t isn't 4 bytes.");
    #define YSTRING_WCHAR_IS_4_BYTES
    #define YSTRING_CPP11_CHAR_TYPES_SUPPORTED
#endif
