#include "rdv_xml_doc.hpp"
#include "rdv_xml_node.hpp"
#include <iostream>

namespace rdv
{
    xml_doc::xml_doc(xmlDocPtr _xmlDoc,
                     xmlNodePtr _xmlRoot,
                     const XmlnsList &_xmlns)
        : m_xmlDoc(_xmlDoc),
          m_xmlRoot(_xmlRoot),
          m_xmlns(_xmlns)
    {
    }

    xml_doc::~xml_doc()
    {
        xmlFreeDoc(m_xmlDoc);
    }

    bool xml_doc::run()
    {
        return true;
    }

    int xml_doc::countXNode(const std::string &_path) const
    {
        xmlXPathContextPtr cXPath = xmlXPathNewContext(m_xmlDoc);
        if (!cXPath)
        {
            return 0;
        }
        for (const auto &xmlnsList : m_xmlns)
        {
            const std::string &ns = xmlnsList[0];
            const std::string &xmlns = xmlnsList[1];
            xmlXPathRegisterNs(cXPath, BAD_CAST(ns.c_str()), BAD_CAST(xmlns.c_str()));
        }
        xmlXPathObjectPtr oXPath = xmlXPathNodeEval(m_xmlRoot, BAD_CAST(_path.c_str()), cXPath);
        if (!oXPath)
        {
            return 0;
        }
        xmlXPathFreeContext(cXPath);
        int count = 0;
        if (oXPath->nodesetval)
        {
            count = oXPath->nodesetval->nodeNr;
        }
        xmlXPathFreeObject(oXPath);
        return count;
    }

    xml_node xml_doc::getXNode(const std::string &_path) const
    {
        xmlXPathContextPtr cXPath = xmlXPathNewContext(m_xmlDoc);
        if (!cXPath)
        {
            return xml_node(m_xmlDoc, nullptr);
        }
        for (const auto &xmlnsList : m_xmlns)
        {
            const std::string &ns = xmlnsList[0];
            const std::string &xmlns = xmlnsList[1];
            xmlXPathRegisterNs(cXPath, BAD_CAST(ns.c_str()), BAD_CAST(xmlns.c_str()));
        }
        xmlXPathObjectPtr oXPath = xmlXPathEvalExpression(BAD_CAST(_path.c_str()), cXPath);
        if (!oXPath)
        {
            return xml_node(m_xmlDoc, nullptr);
        }
        xmlXPathFreeContext(cXPath);
        xmlNodePtr node = nullptr;
        if (oXPath->nodesetval)
        {
            if (oXPath->nodesetval->nodeNr)
            {
                node = oXPath->nodesetval->nodeTab[0];
            }
        }
        xmlXPathFreeObject(oXPath);
        return xml_node(m_xmlDoc, node, m_xmlns);
    }

    xml_node xml_doc::first() const
    {
        xmlNodePtr node = xmlFirstElementChild(m_xmlRoot);
        return xml_node(m_xmlDoc, node, m_xmlns);
    }

    xml_node xml_doc::first(const std::string &_name) const
    {
        xmlNodePtr node = xmlFirstElementChild(m_xmlRoot);
        while (node)
        {
            const std::string &name = (const char *)node->name;
            if (name == _name)
            {
                return xml_node(m_xmlDoc, node, m_xmlns);
            }
            node = xmlNextElementSibling(node);
        }
        return xml_node(m_xmlDoc);
    }

    xml_node xml_doc::next() const
    {
        xmlNodePtr node = xmlNextElementSibling(m_xmlRoot);
        return xml_node(m_xmlDoc, node, m_xmlns);
    }

    xml_node xml_doc::next(const std::string &_name) const
    {
        xmlNodePtr node = xmlNextElementSibling(m_xmlRoot);
        while (node)
        {
            const std::string &name = (const char *)node->name;
            if (name == _name)
            {
                return xml_node(m_xmlDoc, node, m_xmlns);
            }
            node = xmlNextElementSibling(node);
        }
        return xml_node(m_xmlDoc);
    }

    std::string xml_doc::rootName() const
    {
        return (const char *)m_xmlRoot->name;
    }

    std::string xml_doc::toString() const
    {
        xmlChar *buffer = nullptr;
        int size;
        xmlDocDumpFormatMemoryEnc(m_xmlDoc, &buffer, &size, "UTF-8", 4);
        std::string data((char *)buffer, size);
        xmlFree(buffer);
        return data;
    }

    xml_node xml_doc::operator()(const std::string &_path) const
    {
        return first(_path);
    }
}