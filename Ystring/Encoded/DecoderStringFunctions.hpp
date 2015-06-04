//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 03.06.15
//
// This file is distributed under the BSD License.
// License text is included with the source distribution.
//****************************************************************************
#pragma once

#include "../FindFlags.hpp"

namespace Ystring { namespace Encoded {

template <typename Decoder1, typename Decoder2>
Decoder1 find(Decoder1&& str, Decoder2&& sub);

template <typename Decoder1, typename Decoder2>
Decoder1 findCaseInsensitive(Decoder1&& str, Decoder2&& sub);


}}

#include "DecoderStringFunctions-impl.hpp"
