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
#include "../Unicode/UnicodePredicates.hpp"
#include "DecoderAlgorithms.hpp"

namespace Ystring { namespace Encoded {

template <typename Decoder>
bool advanceCharacter(Decoder& it)
{
    uint32_t ch;
    if (!it.next(ch))
        return false;
    auto prevIt = it.getLogicalBegin();
    if (Decoder::isForward)
    {
        while (it.next(ch))
        {
            if (!Unicode::isMark(ch))
            {
                it.setLogicalBegin(prevIt);
                break;
            }
            prevIt = it.getLogicalBegin();
        }
    }
    else
    {
        while (Unicode::isMark(ch) && it.next(ch))
        {}
    }
    return true;
}

template <typename Encoder, typename Decoder>
void appendLower(Encoder&& dst, Decoder&& src)
{
    uint32_t ch;
    while (src.next(ch))
        dst.encode(Unicode::lower(ch));
}

template <typename Encoder, typename Decoder>
void appendTitle(Encoder&& dst, Decoder&& src)
{
    uint32_t ch;
    bool capNext = true;
    while (src.next(ch))
    {
        if (!Unicode::isCasedLetter(ch))
        {
            dst.encode(ch);
            capNext = !Unicode::isLetter(ch);
        }
        else if (capNext)
        {
            dst.encode(Unicode::title(ch));
            capNext = false;
        }
        else
        {
            dst.encode(Unicode::lower(ch));
        }
    }
}

template <typename Encoder, typename Decoder>
void appendUpper(Encoder&& dst, Decoder&& src)
{
    uint32_t ch;
    while (src.next(ch))
        dst.encode(Unicode::upper(ch));
}

template <typename Decoder1, typename Decoder2>
int32_t caseInsensitiveCompare(Decoder1 str,
                               Decoder2 cmp)
{
    advanceWhileEqual(str, cmp, Unicode::CaseInsensitiveEqual());
    if (str.begin() == str.end() && cmp.begin() == cmp.end())
        return 0;
    else if (str.begin() == str.end())
        return -1;
    else if (cmp.begin() == cmp.end())
        return 1;
    uint32_t strCh, cmpCh;
    str.next(strCh);
    cmp.next(cmpCh);
    return Unicode::caseInsensitiveCompare(strCh, cmpCh);
}

template <typename Decoder1, typename Decoder2>
bool caseInsensitiveEqual(Decoder1 str,
                          Decoder2 cmp)
{
    advanceWhileEqual(str, cmp, Unicode::CaseInsensitiveEqual());
    return str.begin() == str.end() && cmp.begin() == cmp.end();
}

template <typename Decoder1, typename Decoder2>
bool caseInsensitiveLess(Decoder1 str,
                         Decoder2 cmp)
{
    advanceWhileEqual(str, cmp, Unicode::CaseInsensitiveEqual());
    if (str.begin() == str.end() || cmp.begin() == cmp.end())
        return str.begin() == str.end() && cmp.begin() != cmp.end();
    uint32_t strCh, cmpCh;
    str.next(strCh);
    cmp.next(cmpCh);
    return Unicode::caseInsensitiveLess(strCh, cmpCh);
}

template <typename Decoder1, typename Decoder2>
Decoder1 find(Decoder1 str, Decoder2 sub, FindFlags_t flags)
{
    if (flags == FindFlags::CASE_INSENSITIVE)
        return search(str, sub, Unicode::CaseInsensitiveEqual());
    else
        return search(str, sub);
}

template <typename Decoder, typename UnaryPredicate>
Decoder nextToken(Decoder& str, UnaryPredicate predicate)
{
    auto token = str;
    token.setLogicalEnd(str.getLogicalBegin());
    uint32_t ch;
    while (str.next(ch) && !predicate(ch))
        token.setLogicalEnd(str.getLogicalBegin());
    return token;
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
