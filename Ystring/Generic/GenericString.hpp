//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 02.06.15
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#pragma once

#include "../FindFlags.hpp"
#include "../Utilities/RangeAlgorithms.hpp"
#include "StringReference.hpp"

namespace Ystring { namespace Generic {

template <typename Str, typename It1, typename It2>
void appendJoin(StringReference<Str>& dst, It1 first, It1 last,
                It2 delimiterFirst, It2 delimiterLast);

template <typename Str, typename It>
void appendJoin(StringReference<Str>& dst, It first, It last);

template <typename Str, typename It, typename Enc>
void appendLower(StringReference<Str>& dst,
                 Utilities::Range<It> src,
                 Enc encoding);

template <typename Str, typename It, typename Enc>
void appendUpper(StringReference<Str>& dst,
                 Utilities::Range<It> src,
                 Enc encoding);

//template <typename Str, typename It2, typename Enc>
//void replace(EncodedString<Str, Enc> dst,
//             EncodedRange<It2, Enc> cmp,)
//{
//    Encoded::appendLower(dst.getEncoder(), src.getForwardDecoder());
//}

template <typename It1, typename It2, typename Enc>
bool endsWith(Utilities::Range<It1> str,
              Utilities::Range<It2> cmp,
              Enc encoding,
              FindFlags_t flags = FindFlags::DEFAULTS);

template <typename It1, typename It2, typename Enc>
Utilities::Range<It1> find(Utilities::Range<It1> str,
                           Utilities::Range<It2> cmp,
                           Enc encoding,
                           FindFlags_t flags = FindFlags::DEFAULTS);

template <typename Str, typename It1, typename It2>
Str join(It1 first, It1 last, It2 delimiterFirst, It2 delimiterLast);

template <typename Str, typename It>
Str join(It first, It last);

template <typename Str, typename It, typename Enc>
Str lower(Utilities::Range<It> src, Enc encoding);

template <typename It, typename Delimiter>
size_t sizeOfJoin(It first, It last, const Delimiter& delimiter);

template <typename It>
size_t sizeOfJoin(It first, It last);

template <typename It, typename Enc>
size_t sizeOfLower(Utilities::Range<It> src, Enc encoding);

template <typename It, typename Enc>
size_t sizeOfUpper(Utilities::Range<It> src, Enc encoding);

template <typename It1, typename It2, typename Enc>
bool startsWith(Utilities::Range<It1> str,
                Utilities::Range<It2> cmp,
                Enc encoding,
                FindFlags_t flags = FindFlags::DEFAULTS);

template <typename Str, typename It, typename Enc>
Str upper(Utilities::Range<It> src, Enc encoding);

}}

#include "GenericString-impl.hpp"
