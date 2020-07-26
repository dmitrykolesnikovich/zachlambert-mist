#ifndef MODEL_H
#define MODEL_H

#include <string>
#include <vector>

#include "data/mesh.h"

namespace mist {

class Model {
public:
    void append_mesh(Mesh mesh, const std::string &material);
    const std::size_t get_mesh_count()const{ return meshes.size(); }
    const Mesh &get_mesh(std::size_t index)const{ return meshes[index]; }
    const std::string &get_material(std::size_t index)const{ return materials[index]; }
private:
    std::vector<Mesh> meshes;
    std::vector<std::string> materials;
};

} // namespace mist

#endif
