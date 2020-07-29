#include "data/shader_manager.h"

#include <GL/glew.h>

#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

namespace mist {

bool load_file_into_string(const std::string &file_path, std::string& string)
{
    std::ifstream file_stream(file_path, std::ios::in);
    if (file_stream.is_open()) {
        std::stringstream sstream;
        sstream << file_stream.rdbuf();
        string = sstream.str();
        file_stream.close();
        return true;
    } else {
        printf("Failed to open file %s.\n", file_path.c_str());
        return false;
    }
}

void compile_and_check_shader(
    const std::string  &file_path,
    const std::string &code,
    const unsigned int shader_id)
{
    GLint result = GL_FALSE;
    int info_log_length;

    // Compile shader
    printf("Compiling shader : %s\n", file_path.c_str());
    char const *vertex_source_pointer = code.c_str();
    glShaderSource(shader_id, 1, &vertex_source_pointer, NULL);
    glCompileShader(shader_id);

    // Check shader
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &result);
    glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &info_log_length);
    if (info_log_length > 0) {
        std::vector<char> vertex_shader_error_message(info_log_length + 1);
        glGetShaderInfoLog(
            shader_id, info_log_length, NULL, &vertex_shader_error_message[0]
        );
        printf("%s\n", &vertex_shader_error_message[0]);
    }
}

unsigned int load_shader(const std::string &vs_path, const std::string &fs_path)
{
    // Create shaders
    unsigned int vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
    unsigned int fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);

    std::string vertex_shader_code;
    if (!load_file_into_string(vs_path, vertex_shader_code)) {
        return 0;
    }

    std::string fragment_shader_code;
    if (!load_file_into_string(fs_path, fragment_shader_code)) {
        return 0;
    }

    compile_and_check_shader(
        vs_path, vertex_shader_code, vertex_shader_id
    );

    compile_and_check_shader(
        fs_path, fragment_shader_code, fragment_shader_id
    );

    // Link the program
    printf("Linking program\n");
    GLuint program_id = glCreateProgram();
    glAttachShader(program_id, vertex_shader_id);
    glAttachShader(program_id, fragment_shader_id);
    glLinkProgram(program_id);

    // Check the program

    GLint result = GL_FALSE;
    int info_log_length;

    glGetProgramiv(program_id, GL_LINK_STATUS, &result);
    glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &info_log_length);
    if (info_log_length > 0) {
        std::vector<char> program_error_message(info_log_length + 1);
        glGetProgramInfoLog(
            program_id, info_log_length, NULL, &program_error_message[0]
        );
        printf("%s\n", &program_error_message[0]);
    }

    glDetachShader(program_id, vertex_shader_id);
    glDetachShader(program_id, fragment_shader_id);

    glDeleteShader(vertex_shader_id);
    glDeleteShader(fragment_shader_id);

    return program_id;
}

ShaderManager::ShaderManager(std::string base_dir)
{
    static const std::string shader_paths[static_cast<std::size_t>(ShaderType::COUNT)] = {
        "shaders/colored", // COLORED
        "shaders/textured" // TEXTURED
    };
    for (std::size_t i = 0; i < static_cast<std::size_t>(ShaderType::COUNT); i++) {
        shaders[i].initialise(load_shader(
            base_dir + shader_paths[i] + ".vs", base_dir + shader_paths[i] + ".fs"
        ));
    }
}

std::size_t ShaderManager::determine_shader_index(const Material &material)
{
    switch (material.type) {
        case MaterialType::COLORED:
            return static_cast<std::size_t>(ShaderType::COLORED);
        case MaterialType::TEXTURED:
            return static_cast<std::size_t>(ShaderType::TEXTURED);
    }
}

} // namespace mist
