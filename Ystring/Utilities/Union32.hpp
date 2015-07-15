//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-07-08
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#pragma once

#include <algorithm>
#include <cstdint>

namespace Ystring { namespace Utilities {

union Union32
{
    Union32() : u32(0) {}
    explicit Union32(uint32_t n) : u32(n) {}

    template <typename T>
    explicit Union32(const T (&n)[2]);

    template <typename T>
    explicit Union32(const T (&n)[4]);

    void reverse();

    int32_t i32;
    uint32_t u32;
    int16_t i16[2];
    uint16_t u16[2];
    int8_t i8[4];
    uint8_t u8[4];
};

template <typename T>
Union32::Union32(const T (&n)[2])
{
    u16[0] = static_cast<uint16_t>(n[0]);
    u16[1] = static_cast<uint16_t>(n[1]);
}

template <typename T>
Union32::Union32(const T (&n)[4])
{
    u8[0] = static_cast<uint8_t>(n[0]);
    u8[1] = static_cast<uint8_t>(n[1]);
    u8[2] = static_cast<uint8_t>(n[2]);
    u8[3] = static_cast<uint8_t>(n[3]);
}

inline void Union32::reverse()
{
    std::swap(u8[0], u8[3]);
    std::swap(u8[1], u8[2]);
}

}}