//****************************************************************************
// Copyright © 2014 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2014-05-06.
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#pragma once

#include <ostream>
#include <string>
#include <type_traits>

/** @file
  * @brief Defines functions for writing containers of streamable values to
  *     an output stream.
  */

namespace Ystring
{
    template <typename FwdIt, typename StringT>
    struct OSJoiner
    {
        OSJoiner(FwdIt first, FwdIt last, StringT separator)
            : first(first), last(last), separator(separator)
        {}

        FwdIt first, last;
        StringT separator;
    };

    template <typename StreamT, typename FwdIt, typename StringT>
    StreamT& operator<<(StreamT& os, OSJoiner<FwdIt, StringT>&& joiner)
    {
        if (joiner.first != joiner.last)
        {
            using namespace std;
            os << *joiner.first;
            if (joiner.separator != typename std::decay<StringT>::type())
            {
                for (auto it = next(joiner.first); it != joiner.last; ++it)
                    os << joiner.separator << *it;
            }
            else
            {
                for (auto it = next(joiner.first); it != joiner.last; ++it)
                    os << *it;
            }
        }
        return os;
    }

    /** @brief Writes the values from @a first to @a last to an output stream
      *     with @a separator between each pair of values.
      */
    template <typename FwdIt, typename StringT>
    OSJoiner<FwdIt, StringT> join(FwdIt first, FwdIt last,
                                  StringT&& separator)
    {
        return OSJoiner<FwdIt, StringT>(first, last, separator);
    }

    /** @brief Writes the values from @a first to @a last to an output stream.
      */
    template<typename FwdIt, typename StringT>
    OSJoiner<FwdIt, StringT> join(FwdIt first, FwdIt last)
    {
        return OSJoiner<FwdIt, StringT>(first, last, StringT());
    }
}
