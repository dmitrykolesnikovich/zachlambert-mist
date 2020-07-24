cmake_minimum_required(VERSION 3.0)
project(
    "Graphics Engine"
    VERSION 0.1.0
    DESCRIPTION "Learning opengl by building a simple graphics engine"
    LANGUAGES CXX
)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

set(SRC
    src/render/renderer.cpp
    src/scene/world.cpp
    src/scene/camera.cpp
    src/scene/entity.cpp
    src/window/clock.cpp
    src/window/window.cpp
    src/window/fps_counter.cpp
    src/resources/mesh.cpp
    src/resources/shader.cpp
    src/resources/shader_manager.cpp
    src/resources/model.cpp
    src/resources/model_manager.cpp
    src/resources/texture_manager.cpp
)

add_library(zgraphics ${SRC})

target_include_directories(zgraphics
    PRIVATE
        src/render
        src/scene
        src/window
        src/resources
    PUBLIC include
)

add_library(stb INTERFACE)
target_include_directories(stb INTERFACE /opt/stb)

target_link_libraries(zgraphics GL glfw glm assimp stb)
