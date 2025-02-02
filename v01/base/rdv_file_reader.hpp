#pragma once

#include <string>

namespace rdv
{
    class file_reader
    {
    public:
        explicit file_reader(const std::string &_filename);
        ~file_reader();
        bool run(std::string &_dataOut);

    private:
        std::string m_filename;
    };
}
