#ifndef SHADER_MANAGER
#define SHADER_MANAGER

#include <string>
#include <unordered_map>

#include "resources/shader.h"

class ShaderManager {
public:
    ShaderManager(const std::string &root_dir):root_dir(root_dir) {}
    const Shader &get_shader(
        const std::string &vs_relative_path,
        const std::string &fs_relative_path);
private:
    const std::string root_dir;
    std::unordered_map<std::string, Shader> shaders;
};

#endif
