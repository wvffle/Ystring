//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 03.06.15
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#pragma once

#include "../FindFlags.hpp"

namespace Ystring { namespace Encoded {

template <typename Encoder, typename Decoder>
void appendLower(Encoder&& dst, Decoder&& src);

template <typename Encoder, typename Decoder>
void appendTitle(Encoder&& dst, Decoder&& src);

template <typename Encoder, typename Decoder>
void appendUpper(Encoder&& dst, Decoder&& src);

template <typename Decoder1, typename Decoder2>
Decoder1 find(Decoder1 str, Decoder2 sub,
              FindFlags_t flags = FindFlags::DEFAULTS);

template <typename Decoder, typename UnaryPredicate>
Decoder nextToken(Decoder& str, UnaryPredicate predicate);

template <typename Decoder1, typename Decoder2>
bool startsWith(Decoder1&& str, Decoder2&& sub,
                FindFlags_t flags = FindFlags::DEFAULTS);


}}

#include "DecoderStringFunctions-impl.hpp"
