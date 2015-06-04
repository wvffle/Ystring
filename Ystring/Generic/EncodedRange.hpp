//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 02.06.15
//
// This file is distributed under the Simplified BSD License.
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

    EncodedRange(Utilities::Range<It> range, Enc encoding)
        : m_Range(range),
          m_Encoding(encoding)
    {}

    Utilities::Range<It> getRange() const
    {
        return m_Range;
    }

    Encoded::ForwardDecoder<It, Enc> getForwardDecoder() const
    {
        return Encoded::makeForwardDecoder(m_Range, m_Encoding);
    }

    Encoded::ReverseDecoder<It, Enc> getReverseDecoder() const
    {
        return Encoded::makeReverseDecoder(m_Range, m_Encoding);
    }

    It begin() const
    {
        return m_Range.begin();
    }

    It end() const
    {
        return m_Range.end();
    }

private:
    Utilities::Range<It> m_Range;
    Enc m_Encoding;
};

template<typename It, typename Enc>
EncodedRange<It, Enc> makeEncodedRange(Utilities::Range<It> range,
                                       Enc encoding)
{
    return EncodedRange<It, Enc>(range, encoding);
}

template<typename It, typename Enc>
EncodedRange<It, Enc> makeEncodedRange(Encoded::ForwardDecoder<It, Enc> dec)
{
    return EncodedRange<It, Enc>(Utilities::makeRange(dec),
                                 dec.getEncoding());
}

template<typename It, typename Enc>
EncodedRange<It, Enc> makeEncodedRange(Encoded::ReverseDecoder<It, Enc> dec)
{
    return EncodedRange<It, Enc>(Utilities::makeRange(dec),
                                 dec.getEncoding());
}

}}
