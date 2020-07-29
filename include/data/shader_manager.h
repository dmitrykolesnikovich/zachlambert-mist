#ifndef SHADER_MANAGER_H
#define SHADER_MANAGER_H

#include <unordered_map>

#include "data/shader.h"
#include "data/material.h"

namespace mist {

enum class ShaderType {
    COLORED,
    TEXTURED,
    COUNT
};

class ShaderManager{
public:
    ShaderManager(std::string base_dir);
    std::size_t determine_shader_index(const Material &material);
    const Shader &get_shader(std::size_t index){ return shaders[index]; };
private:
    std::string base_dir;
    Shader shaders[static_cast<std::size_t>(ShaderType::COUNT)];
};

} // namespace mist

#endif
