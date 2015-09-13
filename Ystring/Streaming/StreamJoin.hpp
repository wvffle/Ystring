//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2014-05-06.
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#pragma once

#include <ostream>
#include <string>
#include "JEBIO/JEBIODefinitions.hpp"

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
            os << *joiner.first;
            for (auto it = std::next(joiner.first); it != joiner.last; ++it)
                os << joiner.separator << *it;
        }
        return os;
    }

    template <typename FwdIt, typename StringT>
    OSJoiner<FwdIt, StringT> join(FwdIt first, FwdIt last,
                                  StringT&& separator)
    {
        return OSJoiner<FwdIt, StringT>(first, last, separator);
    }
}
