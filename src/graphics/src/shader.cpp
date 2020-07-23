#include "shader.h"

#include <GL/glew.h>

Shader::Shader(unsigned int program_id):program_id(program_id)
{
    mvp_loc = glGetUniformLocation(program_id, "MVP");
    m_loc = glGetUniformLocation(program_id, "M");
    v_loc = glGetUniformLocation(program_id, "V");
    light_pos_loc = glGetUniformLocation(
        program_id, "LightPosition_worldspace"
    );
    light_power_loc = glGetUniformLocation(
        program_id, "LightPower"
    );
    light_color_loc = glGetUniformLocation(
        program_id, "LightColor"
    );
}

void Shader::use(const glm::mat4 &mvp, const glm::mat4 &m, const glm::mat4 &v, const Light &light)const
{
    glUseProgram(program_id);
    glUniformMatrix4fv(mvp_loc, 1, GL_FALSE, &mvp[0][0]);
    glUniformMatrix4fv(m_loc, 1, GL_FALSE, &m[0][0]);
    glUniformMatrix4fv(v_loc, 1, GL_FALSE, &v[0][0]);
    glUniform3f(
        light_pos_loc,
        light.get_position().x,
        light.get_position().y,
        light.get_position().z
    );
    glUniform1f(light_power_loc, light.get_power());
    glUniform3f(
        light_color_loc,
        light.get_color().x,
        light.get_color().y,
        light.get_color().z
    );
}

void Shader::set_bool(const std::string &name, bool value)const
{
    glUniform1i(glGetUniformLocation(program_id, name.c_str()), (int)value);
}

void Shader::set_int(const std::string &name, int value)const
{
    glUniform1i(glGetUniformLocation(program_id, name.c_str()), value);
}

void Shader::set_float(const std::string &name, float value)const
{
    glUniform1f(glGetUniformLocation(program_id, name.c_str()), value);
}

