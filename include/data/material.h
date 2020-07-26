#ifndef MATERIAL_H
#define MATERIAL_H

#include <string>
#include <glm/glm.hpp>
#include "data/texture.h"

namespace mist {

enum class MaterialType {
    COLORED,
    TEXTURED
};

// Use pointers to textures, to allow for a null pointer
// when not using textures
struct Material {
    glm::vec3 diffuse_color;
    std::string diffuse_texture;
    glm::vec3 specular_color;
    std::string specular_texture;
    MaterialType type;
};

} // namespace mist

#endif
