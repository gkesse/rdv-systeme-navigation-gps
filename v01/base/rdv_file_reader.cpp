#include "rdv_file_reader.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

namespace rdv
{
    file_reader::file_reader(const std::string &_filename)
        : m_filename(_filename)
    {
    }

    file_reader::~file_reader()
    {
    }

    bool file_reader::run(std::string &_dataOut)
    {
        std::ifstream fileIn(m_filename);
        if (!fileIn.good())
        {
            std::cout << "Le fichier n'existe pas."
                      << "|filename=" << m_filename << std::endl;
            return false;
        }
        std::stringstream buffer;
        buffer << fileIn.rdbuf();
        _dataOut = buffer.str();
        return true;
    }
}