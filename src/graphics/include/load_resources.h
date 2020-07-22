#ifndef LOAD_SHADERS_H
#define LOAD_SHADERS_H

#include <GL/glew.h>
#include <string>

unsigned int load_shaders(
    const std::string &vertex_file_path,
    const std::string &fragment_file_path
);

unsigned int load_texture(const std::string &image_path);

#endif
