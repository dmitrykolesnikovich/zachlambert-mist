
set(COMMON_LIBS
    GL glfw GLEW assimp)
set(COMMON_INCLUDES
    /usr/include/GL
    /usr/include/glm
    /usr/include/GLFW
    /opt/stb
    /usr/include/assimp
)

add_subdirectory(graphics)
add_subdirectory(entity)
add_subdirectory(timing)
add_subdirectory(core)

add_executable(main main.cpp)
target_link_libraries(main
    PRIVATE libgraphics libentity libtiming libcore
    PUBLIC ${COMMON_LIBS}
)
target_include_directories(main
    PRIVATE ${COMMON_INCLUDES}
)
