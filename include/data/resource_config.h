#ifndef RESOURCE_CONFIG_H
#define RESOURCE_CONFIG_H

#include <string>
#include <unordered_map>

#include <glm/glm.hpp>

namespace mist {

enum class MeshType {
    SPHERE,
    BOX
};

class MeshConfig {
public:
    void set_type(ModelType type);
    void set_dimension(std::string name, float value);
    void set_material(std::string material);
    const ModelType get_type()const{ return type; }
    float get_dimension(const std::string &name, float default_value)const;
    const std::string &get_material()const{ return material; }
private:
    ModelType type;
    std::unordered_map<std::string, float> dimensions;
    std::string material;    
};

class MaterialConfig {
public:
    void set_diffuse_color(float r, float g, float b);
    void set_specular_color(float r, float g, float b);
    const glm::vec3 get_diffuse_color()const{ return diffuse_color; }
    const glm::vec3 get_specular_color()const{ return specular_color; }
private:
    glm::vec3 diffuse_color;
    glm::vec3 specular_color;
};

} // namespace mist

#endif
