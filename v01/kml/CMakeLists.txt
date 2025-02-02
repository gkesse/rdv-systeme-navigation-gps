project(kml)

set(SRC
    rdv_kml_deserializer.cpp
    rdv_kml_deserializer.hpp
    rdv_kml_file_data.hpp
)

add_library(${PROJECT_NAME} ${SRC})

target_link_libraries(${PROJECT_NAME}
    base
    xml
    lang
)
