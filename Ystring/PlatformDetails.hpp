//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-07-28
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#pragma once
#include <cstdint>
#include <type_traits>

/** @file
  * @brief Defines compile-time macros that are used to enable or disable
  *     platform-dependent functionality.
  */

/// @cond

#ifdef _MSC_VER
    #define YSTRING_WCHAR_IS_2_BYTES
    #if _MSC_VER >= 1900
        static_assert(!std::is_same<char16_t, uint16_t>::value,
                      "char16_t and uint16_t can't be the same type.");
        static_assert(!std::is_same<char32_t, uint32_t>::value,
                      "char16_t and uint16_t can't be the same type.");
        #define YSTRING_CPP11_CHAR_TYPES_SUPPORTED
    #endif
#else
    static_assert(sizeof(wchar_t) == 4, "Size of wchar_t isn't 4 bytes.");
    #define YSTRING_WCHAR_IS_4_BYTES

    static_assert(!std::is_same<char16_t, uint16_t>::value,
                  "char16_t and uint16_t can't be the same type.");
    static_assert(!std::is_same<char32_t, uint32_t>::value,
                  "char16_t and uint16_t can't be the same type.");
    #define YSTRING_CPP11_CHAR_TYPES_SUPPORTED
#endif

/// @endcond
