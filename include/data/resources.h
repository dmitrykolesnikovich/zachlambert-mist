#ifndef RESOURCES_H
#define RESOURCES_H

#include <string>
#include <unordered_map>

#include <glm/glm.hpp>

#include "data/shader.h"
#include "data/model.h"
#include "data/texture.h"
#include "data/material.h"
#include "data/resource_config.h"

namespace mist {

class Resources {
public:
    Resources(std::string base_dir = "data"):base_dir(base_dir) {}

    bool create_model_from_file(const std::string &name, const std::string &relative_path);
    bool create_model_from_config(const std::string &name, const ModelConfig &config);
    bool create_material_from_config(const std::string &name, const MaterialConfig &config);
private:
    std::string base_dir;
    std::unordered_map<std::string, Shader> shaders;
    std::unordered_map<std::string, Material> materials;
    std::unordered_map<std::string, Texture> textures;
    std::unordered_map<std::string, Model> models;
};

} // namespace mist

#endif
