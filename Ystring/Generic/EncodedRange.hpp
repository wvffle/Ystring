//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 02.06.15
//
// This file is distributed under the BSD License.
// License text is included with the source distribution.
//****************************************************************************
#pragma once

#include "../Encoding.hpp"
#include "../Encoded/ForwardDecoder.hpp"
#include "../Encoded/ReverseDecoder.hpp"
#include "../Utilities/Range.hpp"

namespace Ystring { namespace Generic {

template<typename It, typename Enc>
class EncodedRange
{
public:
    static const Encoding_t encoding = Enc::encoding;

    EncodedRange(It first, It last, Enc encoding)
        : m_First(first),
          m_Last(last),
          m_Encoding(encoding)
    {}

    Utilities::Range<It> getRange() const
    {
        return Utilities::makeRange(m_First, m_Last);
    }

    Encoded::ForwardDecoder<It, Enc> getForwardDecoder() const
    {
        return Encoded::makeForwardDecoder(m_First, m_Last, m_Encoding);
    }

    Encoded::ReverseDecoder<It, Enc> getReverseDecoder() const
    {
        return Encoded::makeReverseDecoder(m_First, m_Last, m_Encoding);
    }

private:
    It m_First;
    It m_Last;
    Enc m_Encoding;
};

template<typename It, typename Enc>
EncodedRange<It, Enc> makeEncodedRange(It first, It last, Enc encoding)
{
    return EncodedRange<It, Enc>(first, last, encoding);
}

template<typename It, typename Enc>
EncodedRange<It, Enc> makeEncodedRange(Utilities::Range<It> range, Enc encoding)
{
    return EncodedRange<It, Enc>(begin(range), end(range), encoding);
}

}}
