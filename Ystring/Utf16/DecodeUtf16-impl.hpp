//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-07-08
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#include <type_traits>
#include "../Utilities/Union16.hpp"
#include "../DecoderResult.hpp"

namespace Ystring { namespace Utf16 {

typedef std::make_unsigned<wchar_t>::type UnsignedWChar;

namespace internal
{
    using Utilities::swapEndianness;

    template <typename FwdIt, bool SwapBytes>
    unsigned nextWord(uint16_t& word, FwdIt& it, FwdIt end, uint32_t)
    {
        if (it == end)
            return DecodeResult::END_OF_STRING;
        else if (*it > 0xFFFFu)
            return DecodeResult::INVALID;

        word = *it++;
        swapEndianness<SwapBytes>(word);

        return DecodeResult::OK;
    }

    template <typename BiIt, bool SwapBytes>
    unsigned prevWord(uint16_t& word, BiIt begin, BiIt& it, uint32_t)
    {
        if (it == begin)
            return DecodeResult::END_OF_STRING;
        else if (*it > 0xFFFFu)
            return DecodeResult::INVALID;

        word = *(--it);
        swapEndianness<SwapBytes>(word);

        return DecodeResult::OK;
    }

    template <typename FwdIt, bool SwapBytes>
    unsigned nextWord(uint16_t& word, FwdIt& it, FwdIt end, uint16_t)
    {
        if (it == end)
            return DecodeResult::END_OF_STRING;

        word = *it++;
        swapEndianness<SwapBytes>(word);

        return DecodeResult::OK;
    }

    template <typename BiIt, bool SwapBytes>
    unsigned prevWord(uint16_t& word, BiIt begin, BiIt& it, uint16_t)
    {
        if (it == begin)
            return DecodeResult::END_OF_STRING;

        word = *(--it);
        swapEndianness<SwapBytes>(word);

        return DecodeResult::OK;
    }

    template <typename FwdIt, bool SwapBytes>
    unsigned nextWord(uint16_t& word, FwdIt& it, FwdIt end, char)
    {
        if (it == end)
            return DecodeResult::END_OF_STRING;

        FwdIt initialIt = it;
        Utilities::Union16 chr;
        chr.u8[SwapBytes ? 1 : 0] = *it++;

        if (it == end)
        {
            it = initialIt;
            return DecodeResult::INCOMPLETE | DecodeResult::END_OF_STRING;
        }

        chr.u8[SwapBytes ? 0 : 1] = *it++;

        word = chr.u16;
        return DecodeResult::OK;
    }

    template <typename BiIt, bool SwapBytes>
    unsigned prevWord(uint16_t& word, BiIt begin, BiIt& it, char)
    {
        if (it == begin)
            return DecodeResult::END_OF_STRING;

        BiIt initialIt = it;
        Utilities::Union16 chr;
        chr.u8[SwapBytes ? 0 : 1] = *(--it);

        if (it == begin)
        {
            it = initialIt;
            return DecodeResult::INCOMPLETE | DecodeResult::END_OF_STRING;
        }

        chr.u8[SwapBytes ? 1 : 0] = *(--it);

        word = chr.u16;
        return DecodeResult::OK;
    }

    template <typename FwdIt, bool SwapBytes>
    unsigned nextWord(uint16_t& word, FwdIt& it, FwdIt end, wchar_t)
    {
        return nextWord<FwdIt, SwapBytes>(word, it, end, UnsignedWChar());
    }

    template <typename BiIt, bool SwapBytes>
    unsigned prevWord(uint16_t& word, BiIt begin, BiIt& it, wchar_t)
    {
        return prevWord<BiIt, SwapBytes>(word, begin, it, UnsignedWChar());
    }
}

template <typename FwdIt, bool SwapBytes>
unsigned nextUtf16CodePoint(uint32_t& codePoint, FwdIt& it, FwdIt end)
{
    uint16_t chr;
    unsigned nwResult = internal::nextWord<FwdIt, SwapBytes>(
            chr, it, end,
            typename std::iterator_traits<FwdIt>::value_type());
    if (nwResult != DecodeResult::OK)
        return nwResult;

    if (chr < 0xD800 || 0xE000 <= chr)
    {
        codePoint = chr;
        return DecodeResult::OK;
    }
    else if (0xDC00 <= chr)
    {
        codePoint = chr;
        return DecodeResult::INVALID;
    }

    codePoint = (chr & 0x3FF) << 10;

    nwResult = internal::nextWord<FwdIt, SwapBytes>(
            chr, it, end,
            typename std::iterator_traits<FwdIt>::value_type());
    if (nwResult == DecodeResult::END_OF_STRING)
        return DecodeResult::END_OF_STRING | DecodeResult::INCOMPLETE;
    else if (nwResult != DecodeResult::OK)
        return nwResult;

    if (chr < 0xDC00 || 0xE000 <= chr)
    {
        codePoint |= chr;
        return DecodeResult::INVALID;
    }

    codePoint |= chr & 0x3FF;
    codePoint += 0x10000;

    return DecodeResult::OK;
}

template <typename FwdIt>
unsigned nextUtf16CodePoint(uint32_t& codePoint, FwdIt& it, FwdIt end)
{
    return nextUtf16CodePoint<FwdIt, false>(codePoint, it, end);
}

template <typename BiIt, bool SwapBytes>
unsigned prevUtf16CodePoint(uint32_t& codePoint, BiIt begin, BiIt& it)
{
    uint16_t chr;
    unsigned pwResult = internal::prevWord<BiIt, SwapBytes>(
            chr, begin, it,
            typename std::iterator_traits<BiIt>::value_type());
    if (pwResult != DecodeResult::OK)
        return pwResult;

    if (chr < 0xD800 || 0xE000 <= chr)
    {
        codePoint = chr;
        return DecodeResult::OK;
    }
    else if (chr < 0xDC00)
    {
        codePoint = chr;
        return DecodeResult::INVALID;
    }

    codePoint = chr & 0x3FF;

    pwResult = internal::prevWord<BiIt, SwapBytes>(
            chr, begin, it,
            typename std::iterator_traits<BiIt>::value_type());
    if (pwResult == DecodeResult::END_OF_STRING)
        return DecodeResult::END_OF_STRING | DecodeResult::INCOMPLETE;
    else if (pwResult != DecodeResult::OK)
        return pwResult;

    if (chr < 0xD800 || 0xDC00 <= chr)
    {
        codePoint |= chr << 10;
        return DecodeResult::INVALID;
    }

    codePoint |= (chr & 0x3FF) << 10;
    codePoint += 0x10000;

    return DecodeResult::OK;
}

template <typename BiIt>
unsigned prevUtf16CodePoint(uint32_t& codePoint, BiIt begin, BiIt& it)
{
    return prevUtf16CodePoint<BiIt, false>(codePoint, begin, it);
}

}}
