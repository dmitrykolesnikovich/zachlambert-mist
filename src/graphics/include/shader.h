#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <glm/glm.hpp>
#include "light.h"
#include "material.h"

class Shader {
public:
    Shader(unsigned int program_id);
    void use(const glm::mat4 &mvp, const glm::mat4 &m, const glm::mat4 &v, const Light &light)const;
    void use_material(const Material &material)const;
private:
    unsigned int program_id;
    unsigned int mvp_loc;
    unsigned int m_loc;
    unsigned int v_loc;
    unsigned int light_pos_loc;
    unsigned int light_power_loc;
    unsigned int light_color_loc;
    unsigned int diffuse_texture_loc;
    unsigned int diffuse_color_loc;
    unsigned int specular_texture_loc;
    unsigned int specular_color_loc;
};

#endif
