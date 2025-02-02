project(xml)

set(SRC
    rdv_xml_parser.cpp
    rdv_xml_parser.hpp
    rdv_xml_doc.cpp
    rdv_xml_doc.hpp
    rdv_xml_node.cpp
    rdv_xml_node.hpp
)

add_library(${PROJECT_NAME} ${SRC})

target_link_libraries(${PROJECT_NAME}
    base
    xml2
)
