cmake_minimum_required(VERSION 3.0)
project(
    "OPENGL Learning"
    VERSION 0.1.0
    DESCRIPTION "Project to learn opengl"
    LANGUAGES CXX
)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
set(RESOURCES_DIR ${CMAKE_CURRENT_LIST_DIR}/data} CACHE STRING "Directory of resources")

add_subdirectory(src)
