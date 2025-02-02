#include "rdv_file_loader.hpp"
#include <iostream>
#include <regex>
#include <QDir>

namespace rdv
{
    file_loader::file_loader(const std::string &_dirname,
                             const std::string &_regex)
        : m_dirname(_dirname),
          m_regex(_regex)
    {
    }

    file_loader::~file_loader()
    {
    }

    bool file_loader::run(FilesList &_outFiles)
    {
        QDir dir(QString::fromUtf8(m_dirname.c_str()));
        const int count = dir.count();
        std::regex regex(m_regex);

        for (int i = 0; i < count; ++i)
        {
            std::string name = dir[i].toStdString();
            if (std::regex_search(name.begin(), name.end(), regex))
            {
                _outFiles.push_back(std::move(name));
            }
        }
        return true;
    }
}