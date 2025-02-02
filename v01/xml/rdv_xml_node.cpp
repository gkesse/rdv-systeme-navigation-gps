#include "rdv_xml_node.hpp"
#include "rdv_xml_doc.hpp"
#include <iostream>

namespace rdv
{
    xml_node::xml_node(xmlDocPtr _xmlDoc,
                       xmlNodePtr _xmlNode,
                       const XmlnsList &_xmlns)
        : m_xmlDoc(_xmlDoc),
          m_xmlNode(_xmlNode),
          m_xmlns(_xmlns)
    {
    }

    xml_node::xml_node(const xml_doc &_obj)
    {
        *this = _obj;
    }

    xml_node::xml_node(const xml_node &_obj)
    {
        *this = _obj;
    }

    xml_node::~xml_node()
    {
    }

    void xml_node::setValue(const std::string &_value)
    {
        if (!(*this))
            return;
        xmlNodeSetContent(m_xmlNode, BAD_CAST(_value.c_str()));
    }

    void xml_node::setCData(const std::string &_value)
    {
        if (!(*this))
            return;
        xmlNodePtr node = xmlNewChild(m_xmlNode, NULL, m_xmlNode->name, NULL);
        xmlNodePtr cdata = xmlNewCDataBlock(m_xmlDoc,
                                            BAD_CAST(_value.c_str()),
                                            _value.size());
        xmlAddChild(node, cdata);
        xmlReplaceNode(m_xmlNode, node);
    }

    int xml_node::countXNode(const std::string &_path) const
    {
        if (!(*this))
            return 0;
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
        xmlXPathObjectPtr oXPath = xmlXPathNodeEval(m_xmlNode, BAD_CAST(_path.c_str()), cXPath);
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

    xml_node xml_node::getXNode(const std::string &_path)
    {
        if (!(*this))
            return xml_node(m_xmlDoc);

        xmlXPathContextPtr cXPath = xmlXPathNewContext(m_xmlDoc);
        if (!cXPath)
        {
            return xml_node(m_xmlDoc);
        }
        for (const auto &xmlnsList : m_xmlns)
        {
            const std::string &ns = xmlnsList[0];
            const std::string &xmlns = xmlnsList[1];
            xmlXPathRegisterNs(cXPath, BAD_CAST(ns.c_str()), BAD_CAST(xmlns.c_str()));
        }
        xmlNodePtr nodeRoot = xmlDocGetRootElement(m_xmlDoc);
        xmlDocSetRootElement(m_xmlDoc, m_xmlNode);
        xmlXPathObjectPtr oXPath = xmlXPathEvalExpression(BAD_CAST(_path.c_str()), cXPath);
        xmlDocSetRootElement(m_xmlDoc, nodeRoot);
        if (!oXPath)
        {
            return xml_node(m_xmlDoc);
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

    xml_node xml_node::first() const
    {
        if (!(*this))
            return xml_node(m_xmlDoc);

        xmlNodePtr node = xmlFirstElementChild(m_xmlNode);
        return xml_node(m_xmlDoc, node, m_xmlns);
    }

    xml_node xml_node::first(const std::string &_name) const
    {
        if (!(*this))
            return xml_node(m_xmlDoc);

        xmlNodePtr node = xmlFirstElementChild(m_xmlNode);
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

    xml_node xml_node::next() const
    {
        if (!(*this))
            return xml_node(m_xmlDoc);

        xmlNodePtr node = xmlNextElementSibling(m_xmlNode);
        return xml_node(m_xmlDoc, node, m_xmlns);
    }

    xml_node xml_node::next(const std::string &_name) const
    {
        if (!(*this))
            return xml_node(m_xmlDoc);

        xmlNodePtr node = xmlNextElementSibling(m_xmlNode);
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

    std::string xml_node::value() const
    {
        if (!(*this))
            return "";
        return (const char *)xmlNodeGetContent(m_xmlNode);
    }

    std::string xml_node::cdata() const
    {
        if (!(*this))
            return "";
        return (const char *)xmlNodeGetContent(m_xmlNode);
    }

    std::string xml_node::attr(const std::string &_name) const
    {
        if (!(*this))
            return "";
        return (const char *)xmlGetProp(m_xmlNode, BAD_CAST(_name.c_str()));
    }

    std::string xml_node::nodeName() const
    {
        if (!(*this))
            return "";
        return (const char *)m_xmlNode->name;
    }

    std::string xml_node::toString() const
    {
        if (!(*this))
            return "";
        xmlBufferPtr buffer = xmlBufferCreate();
        int size = xmlNodeDump(buffer, m_xmlDoc, m_xmlNode, 0, 1);
        std::string data((char *)buffer->content, size);
        xmlBufferFree(buffer);
        return data;
    }

    xml_node::operator bool() const
    {
        return (m_xmlDoc && m_xmlNode);
    }

    xml_node::operator std::string() const
    {
        return value();
    }

    xml_node xml_node::operator()(const std::string &_path) const
    {
        return first(_path);
    }

    xml_node &xml_node::operator=(const xml_doc &_obj)
    {
        m_xmlDoc = _obj.xmlDoc();
        m_xmlNode = _obj.xmlRoot();
        m_xmlns = _obj.xmlns();
        return *this;
    }

    xml_node &xml_node::operator=(const xml_node &_obj)
    {
        m_xmlDoc = _obj.m_xmlDoc;
        m_xmlNode = _obj.m_xmlNode;
        m_xmlns = _obj.m_xmlns;
        return *this;
    }

    xml_node &xml_node::operator=(const std::string &_value)
    {
        setValue(_value);
        return *this;
    }
}