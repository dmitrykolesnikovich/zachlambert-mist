#include "data/model.h"

#include <iostream>

#include <glm/glm.hpp>

namespace mist {

void Model::add_mesh(Mesh mesh, const Material &material)
{
    meshes.push_back(mesh);
    materials.push_back(material);
}

} // namespace mist
