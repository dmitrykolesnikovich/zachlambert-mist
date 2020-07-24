cmake_minimum_required(VERSION 3.0)
project(
    "Graphics engine examples"
    VERSION 0.1.0
    DESCRIPTION "Example usage for graphics engine"
    LANGUAGES CXX
)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

add_executable(main src/main.cpp)

target_link_libraries(main zgraphics)
