//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 03.06.15
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#pragma once

#include "../Unicode/CaseConverter.hpp"
#include "../Unicode/CaseInsensitive.hpp"
#include "DecoderAlgorithms.hpp"

namespace Ystring { namespace Encoded {

template <typename Encoder, typename Decoder>
void appendLower(Encoder&& dst, Decoder&& src)
{
    uint32_t ch;
    while (src.next(ch))
        dst.encode(Unicode::lower(ch));
}

template <typename Encoder, typename Decoder>
void appendUpper(Encoder&& dst, Decoder&& src)
{
    uint32_t ch;
    while (src.next(ch))
        dst.encode(ch);
}

template <typename Decoder1, typename Decoder2>
Decoder1 find(Decoder1&& str, Decoder2&& sub, FindFlags_t flags)
{
    if (flags == FindFlags::CASE_INSENSITIVE)
        return search(str, sub, Unicode::CaseInsensitiveEqual());
    else
        return search(str, sub);
}

template <typename Decoder1, typename Decoder2>
bool startsWith(Decoder1&& str, Decoder2&& cmp, FindFlags_t flags)
{
    if (flags == FindFlags::CASE_INSENSITIVE)
        advanceWhileEqual(str, cmp, Unicode::CaseInsensitiveEqual());
    else
        advanceWhileEqual(str, cmp);
    return cmp.begin() == cmp.end();
}

}}
