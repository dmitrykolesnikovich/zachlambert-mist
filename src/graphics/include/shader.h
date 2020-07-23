#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <glm/glm.hpp>
#include "light.h"

class Shader {
public:
    Shader(unsigned int program_id);
    void use(const glm::mat4 &mvp, const glm::mat4 &m, const glm::mat4 &v, const Light &light)const;

    void set_bool(const std::string &name, bool value)const;
    void set_int(const std::string &name, int value)const;
    void set_float(const std::string &name, float value)const;
private:
    unsigned int program_id;
    unsigned int mvp_loc;
    unsigned int m_loc;
    unsigned int v_loc;
    unsigned int light_pos_loc;
    unsigned int light_power_loc;
    unsigned int light_color_loc;
};

#endif
