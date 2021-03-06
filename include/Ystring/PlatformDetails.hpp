//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-07-28.
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

    #define YSTRING_WCHAR_IS_2_BYTES
    static_assert(!std::is_same<wchar_t, char16_t>::value,
                  "wchar_t and char16_t can't be the same type.");
    #define YSTRING_CPP11_CHAR_TYPES_SUPPORTED

/// @endcond
