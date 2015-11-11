//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 10.11.2015
//
// This file is distributed under the BSD License.
// License text is included with the source distribution.
//****************************************************************************
#pragma once

namespace Ystring { namespace Conversion {

    struct ErrorHandlingPolicy
    {
        enum Type
        {
            REPLACE,
            STOP,
            THROW,
            SKIP
        };
    };

    typedef ErrorHandlingPolicy::Type ErrorHandlingPolicy_t;

}}
