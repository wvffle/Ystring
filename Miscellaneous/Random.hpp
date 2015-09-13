//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-09-02
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#pragma once

#include <limits>
#include <random>

namespace Ydebug
{

std::default_random_engine& getRandomEngine();

template <typename IntType>
class RandomIntGenerator
{
public:
    RandomIntGenerator(IntType min = 0,
                       IntType max = std::numeric_limits<IntType>::max());
    RandomIntGenerator(std::default_random_engine& randomEngine,
                       IntType min = 0,
                       IntType max = std::numeric_limits<IntType>::max());

    IntType generate();
private:
    std::default_random_engine& m_Engine;
    std::uniform_int_distribution<IntType> m_Dist;
};

template <typename RealType>
class RandomRealGenerator
{
public:
    RandomRealGenerator(RealType min = 0.0, RealType max = 1.0);
    RandomRealGenerator(std::default_random_engine& randomEngine,
                        RealType min = 0.0, RealType max = 1.0);

    RealType generate();
private:
    std::default_random_engine& m_Engine;
    std::uniform_real_distribution<RealType> m_Dist;
};

template <typename IntType>
RandomIntGenerator<IntType>::RandomIntGenerator(
        IntType min, IntType max)
    : m_Engine(getRandomEngine()),
      m_Dist(min, max)
{}

template <typename IntType>
RandomIntGenerator<IntType>::RandomIntGenerator(
        std::default_random_engine& randomEngine,
        IntType min, IntType max)
    : m_Engine(getRandomEngine()),
      m_Dist(min, max)
{}

template <typename IntType>
IntType RandomIntGenerator<IntType>::generate()
{
    return m_Dist(m_Engine);
}

template <typename RealType>
RandomRealGenerator<RealType>::RandomRealGenerator(
        RealType min, RealType max)
    : m_Engine(getRandomEngine()),
      m_Dist(min, std::nextafter(max, std::numeric_limits<RealType>::max()))
{}

template <typename RealType>
RealType RandomRealGenerator<RealType>::generate()
{
    return m_Dist(m_Engine);
}

}
