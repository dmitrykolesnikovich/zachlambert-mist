#ifndef MATERIAL_H
#define MATERIAL_H

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
    union {
    struct { //COLORED
        glm::vec3 diffuse_color;
        glm::vec3 specular_color;
    };
    struct { // TEXTURED
        const Texture *diffuse_texture;
        const Texture *specular_texture;
    };
    };
    MaterialType type;
};

} // namespace mist

#endif
