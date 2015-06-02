//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-06-02
//****************************************************************************
#pragma once

#include <cstdint>

namespace Ystring { namespace Encoded {

template <typename BiIt, typename Encoding>
class ReverseDecoder
{
public:
    static const bool isForward = false;

    ReverseDecoder(BiIt first, BiIt last, Encoding encoding)
        : m_First(first),
          m_Last(last),
          m_Encoding(encoding)
    {}

    bool next(uint32_t& ch)
    {
        return m_Encoding.prev(ch);
    }

    bool skip()
    {
        return m_Encoding.skipPrev();
    }

    BiIt getLogicalBegin()
    {
        return m_Last;
    }

    void setLogicalBegin(BiIt first)
    {
        m_Last = last;
    }

    BiIt getLogicalEnd()
    {
        return m_First;
    }

    void setLogicalEnd(BiIt last)
    {
        m_First = first;
    }

    BiIt begin()
    {
        return m_First;
    }

    BiIt end()
    {
        return m_Last;
    }
protected:
    BiIt m_First;
    BiIt m_Last;
    Encoding m_Encoding;
};

template <typename FwdIt, typename Encoding>
ReverseDecoder<BiIt, Encoding> makeReverseDecoder(
        BiIt first,
        BiIt last,
        Encoding encoding)
{
    return ReverseDecoder<BiIt, Encoding>(first, last, encoding);
}

}}
