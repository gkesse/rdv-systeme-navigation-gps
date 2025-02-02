#pragma once

#include <string>
#include <vector>
#include <libxml2/libxml/parser.h>
#include <libxml2/libxml/xpath.h>
#include <libxml2/libxml/xpathInternals.h>

namespace rdv
{
    using XmlnsList = std::vector<std::vector<std::string>>;

    class xml_doc;

    class xml_node
    {
    public:
        explicit xml_node(xmlDocPtr _xmlDoc,
                          xmlNodePtr _xmlNode = nullptr,
                          const XmlnsList &_xmlns = XmlnsList());
        explicit xml_node(const xml_doc &_obj);
        explicit xml_node(const xml_node &_obj);
        ~xml_node();
        void setValue(const std::string &_value);
        void setCData(const std::string &_value);
        int countXNode(const std::string &_path) const;
        xml_node getXNode(const std::string &_path);
        xml_node first() const;
        xml_node first(const std::string &_name) const;
        xml_node next() const;
        xml_node next(const std::string &_name) const;
        std::string value() const;
        std::string cdata() const;
        std::string attr(const std::string &_name) const;
        std::string nodeName() const;
        std::string toString() const;

        explicit operator bool() const;
        explicit operator std::string() const;
        xml_node operator()(const std::string &_path) const;
        xml_node &operator=(const xml_doc &_obj);
        xml_node &operator=(const xml_node &_obj);
        xml_node &operator=(const std::string &_value);

    private:
        xmlDocPtr m_xmlDoc;
        xmlNodePtr m_xmlNode;
        XmlnsList m_xmlns;
    };
}
