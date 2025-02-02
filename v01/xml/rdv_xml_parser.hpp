#pragma once

#include <string>
#include <libxml2/libxml/parser.h>

namespace rdv
{
    class xml_parser
    {
    public:
        explicit xml_parser(const std::string &_filename);
        ~xml_parser();
        bool run(xmlDocPtr &_xmlDoc, xmlNodePtr &_xmlRoot);

    private:
        std::string m_filename;
    };

    void xml_parser_init();
    void xml_parser_clean();
}
