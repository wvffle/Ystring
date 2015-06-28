//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 17.06.15
//
// This file is distributed under the BSD License.
// License text is included with the source distribution.
//****************************************************************************
#pragma once

#include <string>
#include "../Utilities/Algorithms.hpp"
#include "../Generic/Range.hpp"

namespace Ystring { namespace Encoded {

template <typename String>
class Appender
{
public:
    Appender(String& str)
        : m_String(str)
    {}

    template <typename It>
    void append(Generic::Range<It> str)
    {
        m_String.insert(end(m_String), str.begin(), str.end());
    }
private:
    String& m_String;
};

template <typename Char>
class Appender<Char*>
{
public:
    Appender(Char* str, size_t* size, size_t capacity)
        : m_String(str),
          m_Size(size),
          m_Capacity(capacity)
    {}

    template <typename It>
    void append(Generic::Range<It> str)
    {
        auto its = Utilities::copy(str.begin(), str.end(),
                                   &m_String[*m_Size], &m_String[m_Capacity]);
        if (its.second == &m_String[m_Capacity])
        {
            m_String[m_Capacity - 1] = 0;
            throw std::runtime_error(
                    "Attempt to write beyond the end of string.");
        }
        *m_Size = its.second - m_String;
    }
private:
    Char* m_String;
    size_t* m_Size;
    size_t m_Capacity;
};

template <>
class Appender<std::string>
{
public:
    Appender(std::string& str)
        : m_String(str)
    {}

    template <typename It>
    void append(Generic::Range<It> str)
    {
        m_String.append(str.begin(), str.end());
    }
private:
    std::string& m_String;
};

template <>
class Appender<std::wstring>
{
public:
    Appender(std::wstring& str)
        : m_String(str)
    {}

    template <typename It>
    void append(Generic::Range<It> str)
    {
        m_String.append(str.begin(), str.end());
    }
private:
    std::wstring& m_String;
};

}}
