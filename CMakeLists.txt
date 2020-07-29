cmake_minimum_required(VERSION 3.0)
project(
    "Mist Graphics Engine"
    VERSION 0.1.0
    DESCRIPTION "Learning opengl by building a simple graphics engine"
    LANGUAGES CXX
)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

set(SRC
    src/data/mesh.cpp
    src/data/model.cpp
    src/data/resource_config.cpp
    # src/data/shader.cpp
    # src/data/shader_manager.cpp
    # src/data/texture_manager.cpp
    src/data_utils/create_material.cpp
    src/data_utils/create_mesh.cpp
    src/data_utils/load_model.cpp
    src/render/renderer.cpp
    src/scene/camera.cpp
    src/scene/entity.cpp
    src/scene/scene.cpp
    src/window/clock.cpp
    src/window/fps_counter.cpp
    src/window/window.cpp
)

add_library(mist STATIC ${SRC})

target_include_directories(mist
    PRIVATE src
    PUBLIC include
)

add_library(stb INTERFACE)
target_include_directories(stb INTERFACE /opt/stb)

target_link_libraries(mist PRIVATE GL glfw GLEW assimp stb)

add_subdirectory(examples)
