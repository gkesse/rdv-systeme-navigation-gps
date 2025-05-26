cmake_minimum_required(VERSION 3.10.0)
project(ReadyGPS VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 11)

set(CMAKE_PREFIX_PATH "C:/tools/Qt/6.9.0/msvc2022_64/lib/cmake")

option(BUILD_DESIGNER "Build application as design tool" OFF)
if (BUILD_DESIGNER)
  message(STATUS "Designer tool building is enabled")
  add_definitions(-DBUILD_DESIGNER)
endif()

option(NO_DOWNLOADER "Prohibit map downloading" OFF)
if (NO_DOWNLOADER)
  message(STATUS "Map download ban is enabled")
  add_definitions(-DNO_DOWNLOADER)
endif()

option(OMIM_OS_WINDOWS "Force the environment to Windows" OFF)
if (OMIM_OS_WINDOWS)
  message(STATUS "Forcing the environment to Windows is enabled")
  add_definitions(-DOMIM_OS_WINDOWS)
endif()

find_package(Qt6 REQUIRED COMPONENTS
    Widgets
    OpenGLWidgets
)

qt6_add_resources(RES_SOURCES
    resources.qrc
)

add_executable(${PROJECT_NAME}
    main.cpp
    cMainWindow.cpp
    cPopupMenuHolder.cpp
    cMapWidget.cpp
    cDrawWidget.cpp
    ${RES_SOURCES}
)

target_link_libraries (${PROJECT_NAME}
    Qt6::Widgets
    Qt6::OpenGLWidgets
)
