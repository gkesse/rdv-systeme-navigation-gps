#pragma once

#include <string>

namespace rdv
{
    class StringUtf8Multilang
    {
    public:
        static int8_t constexpr kUnsupportedLanguageCode = -1;
        static int8_t constexpr kDefaultCode = 0;
        static int8_t constexpr kEnglishCode = 1;
        static int8_t constexpr kInternationalCode = 7;
        static int8_t constexpr kAltNameCode = 53;
        static int8_t constexpr kOldNameCode = 55;
    };
}
