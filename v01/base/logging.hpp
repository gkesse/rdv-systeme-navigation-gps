#pragma once

#include <iostream>
#include <atomic>

namespace base
{
    enum LogLevel
    {
        LDEBUG,
        LINFO,
        LWARNING,
        LERROR,
        LCRITICAL,
        NUM_LOG_LEVELS
    };

    using AtomicLogLevel = std::atomic<LogLevel>;
    extern AtomicLogLevel g_LogLevel;

    LogLevel GetDefaultLogLevel();
}

using base::LCRITICAL;
using base::LDEBUG;
using base::LERROR;
using base::LINFO;
using base::LWARNING;
using base::NUM_LOG_LEVELS;

#define LOG(level, msg)                                    \
    do                                                     \
    {                                                      \
        if ((level) >= base::g_LogLevel)                   \
        {                                                  \
            std::cout << "level : " << level << std::endl; \
            std::cout << "msg : " << msg << std::endl;     \
        }                                                  \
    } while (false)
