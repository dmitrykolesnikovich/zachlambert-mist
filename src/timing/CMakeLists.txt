get_filename_component(DIR_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
set(MODULE_NAME lib${DIR_NAME})

set(SRC src/clock.cpp src/fps_counter.cpp)

add_library(${MODULE_NAME} STATIC ${SRC})

target_include_directories(${MODULE_NAME}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src ${COMMON_INCLUDES}
)

target_link_libraries(${MODULE_NAME}
    PRIVATE ${COMMON_LIBS}
)

