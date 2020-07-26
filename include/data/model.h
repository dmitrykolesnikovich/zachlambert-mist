#ifndef MODEL_H
#define MODEL_H

#include <string>
#include <vector>

#include "data/mesh.h"
#include "data/material.h"

namespace mist {

class Model {
public:
    void add_mesh(Mesh mesh, const Material &material);
    const std::size_t get_mesh_count()const{ return meshes.size(); }
    const Mesh &get_mesh(std::size_t index)const{ return meshes[index]; }
    const Material &get_material(std::size_t index)const{ return materials[index]; }
private:
    std::vector<Mesh> meshes;
    std::vector<Material> materials;
};

} // namespace mist

#endif
