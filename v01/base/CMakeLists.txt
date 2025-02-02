project(base)

set(SRC
    rdv_file_loader.cpp
    rdv_file_loader.hpp
    rdv_file_reader.cpp
    rdv_file_reader.hpp
)

add_library(${PROJECT_NAME} ${SRC})

target_link_libraries(${PROJECT_NAME}
    Qt6::Core
)