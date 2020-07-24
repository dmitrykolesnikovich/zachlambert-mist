#include "resources/shader.h"

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

    diffuse_texture_loc = glGetUniformLocation(
        program_id, "material.diffuse_texture"
    );
    diffuse_color_loc = glGetUniformLocation(
        program_id, "material.diffuse_color"
    );
    specular_texture_loc = glGetUniformLocation(
        program_id, "material.specular_texture"
    );
    specular_color_loc = glGetUniformLocation(
        program_id, "material.specular_color"
    );
}

void Shader::use_program()const
{
    glUseProgram(program_id);
}

void Shader::use_mat_m(const glm::mat4 &m)const
{
    glUniformMatrix4fv(m_loc, 1, GL_FALSE, &m[0][0]);
}

void Shader::use_mat_v(const glm::mat4 &v)const
{
    glUniformMatrix4fv(v_loc, 1, GL_FALSE, &v[0][0]);
}

void Shader::use_mat_mvp(const glm::mat4 &mvp)const
{
    glUniformMatrix4fv(mvp_loc, 1, GL_FALSE, &mvp[0][0]);
}

void Shader::use_light(const Light &light)const
{
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

void Shader::use_material(const Material &material)const
{
    if (material.diffuse_texture) {
        glActiveTexture(GL_TEXTURE0);
        glUniform1i(diffuse_texture_loc, 0);
        glBindTexture(GL_TEXTURE_2D, material.diffuse_texture->id);
    } else {
        glUniform3f(
            diffuse_color_loc,
            material.diffuse_color.x,
            material.diffuse_color.y,
            material.diffuse_color.z
        );
    }

    if (material.specular_texture) {
        glActiveTexture(GL_TEXTURE1);
        glUniform1i(specular_texture_loc, 1);
        glBindTexture(GL_TEXTURE_2D, material.specular_texture->id);
    } else {
        glUniform3f(
            specular_color_loc,
            material.specular_color.x,
            material.specular_color.y,
            material.specular_color.z
        );
    }
}
