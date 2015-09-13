//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-08-30.
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#pragma once

#include <chrono>
#include <ostream>
#include <string>

namespace Ydebug
{
    using std::chrono::steady_clock;

    class Timer
    {
    public:
        Timer();
        void start();
        void stop();
        void reset();
        double seconds() const;
        bool isStopped() const;
    private:
        steady_clock::time_point m_StartTime;
        steady_clock::duration m_AccumulatedTime;
        bool m_IsStopped;
    };

    template <typename String>
    class ScopedTimerImpl
    {
    public:
        typedef typename String::value_type CharT;
        typedef std::basic_ostream<CharT, std::char_traits<CharT>> Stream;

        ScopedTimerImpl(const String& label, Stream& stream)
            : m_Label(label),
              m_Stream(stream)
        {
            m_Timer.start();
        }

        ~ScopedTimerImpl()
        {
            m_Timer.stop();
            m_Stream << m_Label << ": " << m_Timer << "\n";
        }
    private:
        Timer m_Timer;
        String m_Label;
        Stream& m_Stream;
    };

    typedef ScopedTimerImpl<std::string> ScopedTimer;
    typedef ScopedTimerImpl<std::wstring> ScopedTimerW;

    template <typename Char, typename Traits>
    std::basic_ostream<Char, Traits>& operator<<(
            std::basic_ostream<Char, Traits>& os,
            const Timer& timer)
    {
      os << timer.seconds();
      return os;
    }

    inline Timer::Timer()
        : m_AccumulatedTime(steady_clock::duration::zero()),
          m_IsStopped(true)
    {}

    inline void Timer::start()
    {
        m_IsStopped = false;
        m_StartTime = steady_clock::now();
    }

    inline void Timer::stop()
    {
        auto endTime = steady_clock::now();
        m_AccumulatedTime += endTime - m_StartTime;
        m_IsStopped = true;
    }

    inline void Timer::reset()
    {
        m_AccumulatedTime = steady_clock::duration::zero();
        m_IsStopped = true;
    }

    inline double Timer::seconds() const
    {
        using namespace std::chrono;
        auto tmp = m_AccumulatedTime;
        if (!isStopped())
        {
            auto endTime = steady_clock::now();
            tmp += endTime - m_StartTime;
        }
        return duration<double>(tmp).count();
    }

    inline bool Timer::isStopped() const
    {
        return m_IsStopped;
    }
}
