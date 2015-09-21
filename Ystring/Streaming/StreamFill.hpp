//****************************************************************************
// Copyright © 2014 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2014-03-15.
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#pragma once

#include <ostream>
#include <string>

/** @file
  * @brief Defines functions for writing the same string to a stream multiple
  *     times.
  */

namespace Ystring
{
    template <typename ValueT>
    struct OSFiller
    {
        OSFiller(size_t n, const ValueT& value)
            : n(n), value(value) {}
        OSFiller(size_t n, ValueT&& value)
            : n(n), value(std::move(value)) {}
        size_t n;
        ValueT value;
    };

    template <typename StreamT, typename ValueT>
    StreamT& operator<<(StreamT& os, OSFiller<ValueT>&& filler)
    {
        for (size_t i = 0; i < filler.n; ++i)
            os << filler.value;
        return os;
    }

    /** @brief When used in a stream expression it writes @a str @a n times
      * to the output stream.
      */
    template <typename ValueT>
    OSFiller<ValueT> fill(size_t n, ValueT&& str)
    {
        return OSFiller<ValueT>(n, str);
    }

    /** @brief When used in a stream expression it writes @a n spaces
      * to the output stream.
      */
    inline OSFiller<char> spaces(size_t n)
    {
        return fill(n, ' ');
    }
}
