cmake_minimum_required(VERSION 3.5.0)
project(rdv_gps VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_C_VISIBILITY_PRESET hidden)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN ON)

set(VERBOSE ON)

find_package(gflags REQUIRED)
find_package(LibXml2 REQUIRED)
find_package(Qt6 COMPONENTS REQUIRED
  Core
)

include_directories(
  ${CMAKE_HOME_DIRECTORY}
  ${LIBXML2_INCLUDE_DIR}
)

add_subdirectory(base)
add_subdirectory(lang)
add_subdirectory(xml)
add_subdirectory(kml)
add_subdirectory(track_generator)
