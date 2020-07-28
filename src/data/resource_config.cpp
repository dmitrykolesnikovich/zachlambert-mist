
#include "data/resource_config.h"

namespace mist {

void MeshConfig::set_type(MeshType type)
{
    this->type = type;
}

void MeshConfig::set_dimension(std::string name, float value)
{
    // Overwrite if already present
    dimensions[name] = value;
}

void MeshConfig::set_material(std::string material)
{
    this->material = material;
}

float MeshConfig::get_dimension(const std::string &name, float default_value)const
{
    std::unordered_map<std::string, float>::const_iterator search
        = dimensions.find(name);
    if (search != dimensions.end()) {
        return search->second;
    } else {
        return default_value;
    }
}


void MaterialConfig::set_diffuse_color(float r, float g, float b)
{
    diffuse_color = glm::vec3(r, g, b);
}

void MaterialConfig::set_specular_color(float r, float g, float b)
{
    specular_color = glm::vec3(r, g, b);
}

} // namespace mist
