
#include "data_utils/create_material.h"

namespace mist {

Material create_material(const MaterialConfig &config)
{
    Material material;
    material.type = MaterialType::COLORED;
    material.diffuse_color = config.get_diffuse_color();
    material.specular_color = config.get_specular_color();
    return material;
}

} // namespace mist
