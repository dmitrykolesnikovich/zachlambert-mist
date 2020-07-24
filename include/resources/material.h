#ifndef MATERIAL_H
#define MATERIAL_H

#include "resources/texture.h"

// Use pointers to textures, to allow for a null pointer
// when not using textures
struct Material {
    const Texture *diffuse_texture;
    glm::vec3 diffuse_color;
    const Texture *specular_texture;
    glm::vec3 specular_color;
};

#endif
