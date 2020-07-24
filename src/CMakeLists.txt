
add_subdirectory(graphics)
add_subdirectory(entity)
add_subdirectory(timing)
add_subdirectory(core)

add_executable(main main.cpp)
target_link_libraries(main
    PRIVATE libgraphics libentity libtiming libcore
)
