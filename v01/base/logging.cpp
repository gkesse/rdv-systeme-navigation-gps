#include "logging.hpp"

namespace base
{
    AtomicLogLevel g_LogLevel = {GetDefaultLogLevel()};

    LogLevel GetDefaultLogLevel()
    {
#if defined(DEBUG)
        return LDEBUG;
#else
        return LINFO;
#endif
    }
}
