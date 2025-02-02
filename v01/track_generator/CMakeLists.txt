project(track_generator)

set(SRC
    main.cpp
    rdv_track_generator.cpp
    rdv_track_generator.hpp
)

add_executable(${PROJECT_NAME} ${SRC})

target_link_libraries(${PROJECT_NAME}
    gflags
    base
    kml
)
