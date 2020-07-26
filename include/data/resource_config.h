#ifndef RESOURCE_CONFIG_H
#define RESOURCE_CONFIG_H

#include <string>
#include <unordered_map>

#include <glm/glm.hpp>

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

} // namespace mist

#endif
