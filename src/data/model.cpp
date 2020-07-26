#include "data/model.h"

#include <iostream>

#include <glm/glm.hpp>

namespace mist {

void Model::append_mesh(Mesh mesh, const std::string &material)
{
    meshes.push_back(mesh);
    materials.push_back(material);
}

} // namespace mist
