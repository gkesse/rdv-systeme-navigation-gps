#include "rdv_xml_parser.hpp"
#include "rdv_xml_doc.hpp"
#include <iostream>

namespace rdv
{
    xml_parser::xml_parser(const std::string &_filename)
        : m_filename(_filename)
    {
    }

    xml_parser::~xml_parser()
    {
    }

    bool xml_parser::run(xmlDocPtr &_xmlDoc, xmlNodePtr &_xmlRoot)
    {
        _xmlDoc = xmlParseFile(m_filename.c_str());
        if (!_xmlDoc)
        {
            return false;
        }
        _xmlRoot = xmlDocGetRootElement(_xmlDoc);
        if (!_xmlRoot)
        {
            return false;
        }
        return true;
    }

    void xml_parser_init()
    {
        xmlInitParser();
        xmlKeepBlanksDefault(0);
    }

    void xml_parser_clean()
    {
        xmlCleanupParser();
    }
}