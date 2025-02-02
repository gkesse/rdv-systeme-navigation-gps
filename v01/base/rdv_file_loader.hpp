#pragma once

#include <string>
#include <vector>

namespace rdv
{

    using FilesList = std::vector<std::string>;

    class file_loader
    {
    public:
        explicit file_loader(const std::string &_dirname,
                             const std::string &_regex);
        ~file_loader();
        bool run(FilesList &_outFiles);

    private:
        std::string m_dirname;
        std::string m_regex;
    };
}
