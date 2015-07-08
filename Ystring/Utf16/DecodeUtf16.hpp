//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-07-08
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#pragma once

#include <cstdint>
#include <limits>
#include <string>
#include "../Utilities/Endian.hpp"

namespace Ystring { namespace Utf16 {

using Ystring::Utilities::IsBigEndian;
using Ystring::Utilities::IsLittleEndian;

template <typename FwdIt, bool SwapBytes>
unsigned nextUtf16CodePoint(uint32_t& codePoint, FwdIt& it, FwdIt end);

template <typename FwdIt>
unsigned nextUtf16CodePoint(uint32_t& codePoint, FwdIt& it, FwdIt end);

template <typename BiIt, bool SwapBytes>
unsigned prevUtf16CodePoint(uint32_t& codePoint, BiIt begin, BiIt& it);

template <typename BiIt>
unsigned prevUtf16CodePoint(uint32_t& codePoint, BiIt begin, BiIt& it);

template <typename FwdIt>
unsigned nextUtf16LECodePoint(uint32_t& codePoint, FwdIt& it, FwdIt end)
{
    return nextUtf16CodePoint<FwdIt, IsBigEndian>(codePoint, it, end);
}

template <typename FwdIt>
unsigned nextUtf16BECodePoint(uint32_t& codePoint, FwdIt& it, FwdIt end)
{
    return nextUtf16CodePoint<FwdIt, IsLittleEndian>(codePoint, it, end);
}

template <typename BiIt>
unsigned prevUtf16LECodePoint(uint32_t& codePoint, BiIt begin, BiIt& it)
{
    return prevUtf16CodePoint<BiIt, IsBigEndian>(codePoint, begin, it);
}

template <typename BiIt>
unsigned prevUtf16BECodePoint(uint32_t& codePoint, BiIt begin, BiIt& it)
{
    return prevUtf16CodePoint<BiIt, IsLittleEndian>(codePoint, begin, it);
}

}}

#include "DecodeUtf16-impl.hpp"
