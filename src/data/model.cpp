#include "data/model.h"

#include <iostream>

#include <glm/glm.hpp>

namespace mist {

void Model::render(const Shader &shader)const
{
    for (std::vector<Mesh>::const_iterator it = meshes.begin();
        it != meshes.end(); it++)
    {
        it->render(shader);
    }
}

} // namespace mist
