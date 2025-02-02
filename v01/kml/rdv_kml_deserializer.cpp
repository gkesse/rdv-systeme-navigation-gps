#include "rdv_kml_deserializer.hpp"
#include "base/rdv_file_reader.hpp"
#include "xml/rdv_xml_doc.hpp"
#include "xml/rdv_xml_node.hpp"
#include "xml/rdv_xml_parser.hpp"
#include <iostream>

namespace rdv
{
    kml_deserializer::kml_deserializer(const std::string &_filename)
        : m_filename(_filename)
    {
    }

    kml_deserializer::~kml_deserializer()
    {
    }

    bool kml_deserializer::run(kml::FileData &_fileData)
    {
        xmlDocPtr xmlDoc;
        xmlNodePtr xmlRoot;
        xml_parser xmlParser(m_filename);
        if (!xmlParser.run(xmlDoc, xmlRoot))
        {
            return false;
        }

        xml_doc docXml(xmlDoc, xmlRoot);

        kml::CategoryData &m_categoryData = _fileData.m_categoryData;
        m_categoryData.m_lastModified;
        m_categoryData.m_accessRules;
        m_categoryData.m_imageUrl;
        m_categoryData.m_rating;
        m_categoryData.m_reviewsNumber;
        m_categoryData.m_annotation;
        m_categoryData.m_toponyms;
        m_categoryData.m_languageCodes;
        m_categoryData.m_properties;
        m_categoryData.m_tags;

        xml_node documentXml = docXml("Document");
        m_categoryData.m_name[kDefaultLang] = documentXml("name").value();
        m_categoryData.m_description[kDefaultLang] = documentXml("description").value();
        m_categoryData.m_visible = (documentXml("visibility").value() != "0");

        xml_node extendedDataXml = documentXml("ExtendedData");
        std::string serverId = extendedDataXml("serverId").value();
        std::string imageUrl = extendedDataXml("imageUrl").value();
        m_categoryData.m_authorName = extendedDataXml("author").value();
        m_categoryData.m_authorId = extendedDataXml("author").attr("id");
        std::string lastModified = extendedDataXml("lastModified").value();
        std::string rating = extendedDataXml("rating").value();
        std::string reviewsNumber = extendedDataXml("reviewsNumber").value();
        std::string accessRules = extendedDataXml("accessRules").value();

        std::cout << "=============================================" << std::endl;
        std::cout << "m_filename: " << m_filename << std::endl;
        std::cout << "=============================================" << std::endl;
        std::cout << "m_categoryData.m_name[kDefaultLang]: " << m_categoryData.m_name[kDefaultLang] << std::endl;
        std::cout << "m_categoryData.m_description[kDefaultLang]: " << m_categoryData.m_description[kDefaultLang] << std::endl;
        std::cout << "m_categoryData.m_visible: " << m_categoryData.m_visible << std::endl;
        std::cout << "............................................." << std::endl;
        std::cout << "imageUrl: " << imageUrl << std::endl;
        std::cout << "serverId: " << serverId << std::endl;
        std::cout << "m_categoryData.m_authorName: " << m_categoryData.m_authorName << std::endl;
        std::cout << "m_categoryData.m_authorId: " << m_categoryData.m_authorId << std::endl;
        std::cout << "lastModified: " << lastModified << std::endl;
        std::cout << "rating: " << rating << std::endl;
        std::cout << "reviewsNumber: " << reviewsNumber << std::endl;
        std::cout << "accessRules: " << accessRules << std::endl;
        std::cout << "............................................." << std::endl;

        return true;
    }
}