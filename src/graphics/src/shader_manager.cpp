#include "shader_manager.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

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
    const GLuint& shader_id)
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

Shader load_shader(const std::string &vs_path, const std::string &fs_path);
{
    // Create shaders
    GLuint vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);

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

    return Shader(program_id);
}

const Shader &ShaderManager::get_shader(const std::string &relative_path)
{
    std::unordered_map<std::string, Shader>::const_iterator search
        = shaders.find(relative_path);
    if (find != shaders.end()) {
        return find->second;
    } else {
        std::pair<std::string, Shader> new_pair(
            relative_path,
            load_shader(root_dir + relative_path)
        );
        return models.insert(new_pair)->second;
    }
}

