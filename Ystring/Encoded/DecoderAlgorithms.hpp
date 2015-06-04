//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 03.06.15
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#pragma once

#include <cstdint>
#include <utility>

namespace Ystring { namespace Encoded {

template <typename Decoder1, typename Decoder2, typename BinaryPred>
bool advanceIfEqual(Decoder1& a, Decoder2& b, BinaryPred compare)
{
    auto aPos = a.getLogicalBegin();
    auto bPos = b.getLogicalBegin();
    uint32_t aCh, bCh;
    bool aNext = a.next(aCh);
    bool bNext = b.next(bCh);
    if (!aNext && !bNext)
        return false;
    if (!aNext || !bNext || !compare(aCh, bCh))
    {
        a.setLogicalBegin(aPos);
        b.setLogicalBegin(bPos);
        return false;
    }
    return true;
}

//template <typename Decoder1, typename Decoder2>
//bool advanceIfEqual(Decoder1& str, Decoder2& cmp)
//{
//    return advanceIfEqual(str, cmp,
//                          [](uint32_t a, uint32_t b){return a == b;});
//}

template <typename Decoder1, typename Decoder2, typename BinaryPred>
bool advanceWhileEqual(Decoder1& str, Decoder2& cmp, BinaryPred compare)
{
    while (advanceIfEqual(str, cmp, compare))
    {}
    return cmp.begin() == cmp.end();
}

template <typename Decoder1, typename Decoder2>
bool advanceWhileEqual(Decoder1& str, Decoder2& cmp)
{
    return advanceWhileEqual(str, cmp,
                             [](uint32_t a, uint32_t b){return a == b;});
}

template <typename Decoder1, typename Decoder2, typename BinaryPred>
Decoder1 search(Decoder1& str, Decoder2& cmp, BinaryPred compare)
{
    while (true)
    {
        auto copyOfStr = str;
        auto copyOfCmp = cmp;
        if (advanceWhileEqual(copyOfStr, copyOfCmp, compare))
        {
            str.setLogicalEnd(copyOfStr.getLogicalBegin());
            std::swap(str, copyOfStr);
            return copyOfStr;
        }
        if (!str.skip())
            break;
    }
    return str;
}

template <typename Decoder1, typename Decoder2>
Decoder1 search(Decoder1& str, Decoder2& cmp)
{
    return search(str, cmp, [](uint32_t a, uint32_t b){return a == b;});
}

}}
