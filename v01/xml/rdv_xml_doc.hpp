#pragma once

#include <string>
#include <vector>
#include <libxml2/libxml/parser.h>
#include <libxml2/libxml/xpath.h>
#include <libxml2/libxml/xpathInternals.h>

namespace rdv
{
    using XmlnsList = std::vector<std::vector<std::string>>;

    class xml_node;

    class xml_doc
    {
    public:
        explicit xml_doc(xmlDocPtr _xmlDoc,
                         xmlNodePtr _xmlRoot,
                         const XmlnsList &_xmlns = XmlnsList());
        ~xml_doc();
        bool run();
        int countXNode(const std::string &_path) const;
        xml_node getXNode(const std::string &_path) const;
        xml_node first() const;
        xml_node first(const std::string &_name) const;
        xml_node next() const;
        xml_node next(const std::string &_name) const;
        std::string rootName() const;
        std::string toString() const;

        xml_node operator()(const std::string &_path) const;

        const xmlDocPtr &xmlDoc() const { return m_xmlDoc; }
        const xmlNodePtr &xmlRoot() const { return m_xmlRoot; }
        const XmlnsList &xmlns() const { return m_xmlns; }

    private:
        xmlDocPtr m_xmlDoc;
        xmlNodePtr m_xmlRoot;
        XmlnsList m_xmlns;
    };
}
