//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-06-02
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#pragma once

#include <cstdint>
#include "../Generic/Range.hpp"

namespace Ystring { namespace Encoded {

template <typename FwdIt, typename Encoding>
class ForwardDecoder
{
public:
    static const bool isForward = true;

    ForwardDecoder(FwdIt first, FwdIt last, Encoding encoding)
        : m_First(first),
          m_Last(last),
          m_Encoding(encoding)
    {}

    bool next(uint32_t &ch)
    {
        return m_Encoding.next(ch, m_First, m_Last);
    }

    bool skip()
    {
        return m_Encoding.skipNext(m_First, m_Last);
    }

    const Encoding& getEncoding() const
    {
        return m_Encoding;
    }

    FwdIt getLogicalBegin() const
    {
        return m_First;
    }

    void setLogicalBegin(FwdIt first)
    {
        m_First = first;
    }

    FwdIt getLogicalEnd() const
    {
        return m_Last;
    }

    void setLogicalEnd(FwdIt last)
    {
        m_Last = last;
    }

    Generic::Range<FwdIt> getRange() const
    {
        return Generic::makeRange(m_First, m_Last);
    }

    FwdIt begin()
    {
        return m_First;
    }

    FwdIt end()
    {
        return m_Last;
    }

protected:
    FwdIt m_First;
    FwdIt m_Last;
    Encoding m_Encoding;
};

template <typename FwdIt, typename Encoding>
ForwardDecoder<FwdIt, Encoding> makeForwardDecoder(
        FwdIt first,
        FwdIt last,
        Encoding encoding)
{
    return ForwardDecoder<FwdIt, Encoding>(first, last, encoding);
}

template <typename FwdIt, typename Encoding>
ForwardDecoder<FwdIt, Encoding> makeForwardDecoder(
        Generic::Range<FwdIt> range,
        Encoding encoding)
{
    return ForwardDecoder<FwdIt, Encoding>(range.begin(), range.end(),
                                           encoding);
}

}}
