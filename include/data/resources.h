#ifndef RESOURCES_H
#define RESOURCES_H

#include <string>
#include <unordered_map>

#include <glm/glm.hpp>

#include "data/shader.h"
#include "data/model.h"
#include "data/texture.h"
#include "data/material.h"

namespace mist {

enum class ModelType {
    SPHERE,
    BOX
};

class ModelConfig {
public:
    void set_type(ModelType type);
    void set_dimension(std::string name, float value);
    void set_material(std::string material);
private:
    ModelType type;
    std::unordered_map<std::string, float> dimensions;
    std::string material;    
};

class MaterialConfig {
public:
    void set_color(float r, float g, float b);
    void set_specularity(float specularity);
private:
    glm::vec3 color;
    float specularity;
};

class Resources {
public:
    Resources(std::string base_dir = "data"):base_dir(base_dir) {}

    bool create_model_from_file(std::string name, std::string relative_path);
    bool create_model_from_config(std::string name, ModelConfig config);
    bool create_material_config(std::string name, MaterialConfig config);
private:
    std::string base_dir;
    std::unordered_map<std::string, Shader> shaders;
    std::unordered_map<std::string, Material> materials;
    std::unordered_map<std::string, Texture> textures;
    std::unordered_map<std::string, Model> models;
};

} // namespace mist

#endif
