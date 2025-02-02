#pragma once

#include "kml/rdv_kml_file_data.hpp"
#include "lang/rdv_multi_lang.hpp"

namespace rdv
{
    auto constexpr kDefaultLang = StringUtf8Multilang::kDefaultCode;
    auto constexpr kDefaultTrackWidth = 5.0;
    auto constexpr kDefaultTrackColor = 0x006ec7ff;

    class kml_deserializer
    {
    public:
        explicit kml_deserializer(const std::string &_filename);
        ~kml_deserializer();
        bool run(kml::FileData &_fileData);

    private:
        std::string m_filename;
    };
}
