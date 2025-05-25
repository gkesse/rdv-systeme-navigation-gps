cmake_minimum_required(VERSION 3.10.0)
project(ReadyGPS VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_PREFIX_PATH "C:/tools/Qt/6.9.0/msvc2022_64/lib/cmake")

find_package(Qt6 REQUIRED COMPONENTS
    Widgets
)

add_executable(${PROJECT_NAME}
    main.cpp
)

target_link_libraries (${PROJECT_NAME}
    Qt6::Widgets
)
