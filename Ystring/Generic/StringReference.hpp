//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 06.06.15
//
// This file is distributed under the BSD License.
// License text is included with the source distribution.
//****************************************************************************
#pragma once

#include <iterator>
#include "../Encoded/Encoder.hpp"
#include "../Utilities/ArrayOutputIterator.hpp"

namespace Ystring { namespace Generic {

template <typename String>
class StringReference
{
public:
    typedef std::back_insert_iterator<String> BackInsertIterator;

    StringReference(String& str)
        : m_String(str)
    {}

    template <typename Encoding>
    Encoded::Encoder<BackInsertIterator, Encoding> getEncoder(Encoding encoding)
    {
        return Encoded::makeEncoder(std::back_inserter(m_String), encoding);
    }

    void terminate()
    {}
private:
    String& m_String;
};

template <typename T>
class StringReference<T*>
{
public:
    typedef Utilities::ArrayOutputIterator<T*> BackInsertIterator;

    StringReference(T* str, size_t size, size_t capacity)
        : m_String(str),
          m_Size(size)
    {}

    template <typename Encoding>
    Encoded::Encoder<BackInsertIterator, Encoding> getEncoder(Encoding encoding)
    {
        return Encoded::makeEncoder(BackInsertIterator(m_String, &m_Size, m_Capacity - 1), encoding);
    }

    void terminate()
    {
        m_String[m_Size] = 0;
    }
private:
    T* m_String;
    size_t m_Size;
    size_t m_Capacity;
};

template <typename T>
StringReference<T> makeStringReference(T& str)
{
    using namespace std;
    return StringReference<T>(str);
}

template <typename T, size_t N>
StringReference<T*> makeStringReference(T (&arr)[N])
{
    return StringReference<T*>(&arr[0], 0, N - 1);
}

}}
