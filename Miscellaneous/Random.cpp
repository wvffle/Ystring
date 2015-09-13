//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-09-02
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#include "Random.hpp"

namespace Ydebug
{
    std::default_random_engine& getRandomEngine()
    {
        static std::default_random_engine engine;
        static bool initialized = false;
        if (!initialized)
        {
            std::random_device rd;
            engine.seed(rd());
        }
        return engine;
    }
}
