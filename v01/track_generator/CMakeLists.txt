project(track_generator)
find_package(gflags REQUIRED)
add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} gflags base)
