//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-06-06.
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#pragma once

#include <iterator>
#include "Appender.hpp"
#include "Encoder.hpp"
#include "../Utilities/ArrayOutputIterator.hpp"

namespace Ystring { namespace Generic
{
    template <typename String>
    class StringReference
    {
    public:
        typedef typename String::value_type ValueType;
        typedef std::back_insert_iterator<String> BackInsertIterator;

        StringReference(String& str)
            : m_String(str)
        {}

        EncodedString::Appender<String> getAppender()
        {
            return EncodedString::Appender<String>(m_String);
        }

        template <typename Enc>
        EncodedString::Encoder<BackInsertIterator, Enc> getEncoder(Enc encoding)
        {
            return EncodedString::makeEncoder(std::back_inserter(m_String),
                                        encoding);
        }

        void reserve(size_t size)
        {
            if (size)
                m_String.reserve(m_String.size() + size);
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
        typedef T ValueType;
        typedef Utilities::ArrayOutputIterator<T*> BackInsertIterator;

        StringReference(T* str, size_t size, size_t capacity)
            : m_String(str),
              m_Size(size)
        {}

        EncodedString::Appender<T*> getAppender()
        {
            return EncodedString::Appender<T*>(m_String, &m_Size, m_Capacity);
        }

        template <typename Encoding>
        EncodedString::Encoder<BackInsertIterator, Encoding>
            getEncoder(Encoding encoding)
        {
            return EncodedString::makeEncoder(
                    BackInsertIterator(m_String, &m_Size, m_Capacity - 1),
                    encoding);
        }

        void reserve(size_t size)
        {}

        void terminate()
        {
            if (m_Size != m_Capacity)
                m_String[m_Size] = 0;
            else
                m_String[m_Capacity - 1] = 0;
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
    StringReference<T*> makeStringReference(T (&arr)[N], size_t size = 0)
    {
        return StringReference<T*>(&arr[0], size, N - 1);
    }

    template <typename T>
    StringReference<T*> makeStringReference(T* str, size_t size,
                                            size_t capacity)
    {
        return StringReference<T*>(str, size, capacity);
    }
}}
