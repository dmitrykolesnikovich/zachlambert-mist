#ifndef MATERIAL_H
#define MATERIAL_H

struct Material {
    unsigned int diffuse_texture;
    float diffuse_value;
    unsigned int specular_texture;
    float specular_value;
};

#endif
