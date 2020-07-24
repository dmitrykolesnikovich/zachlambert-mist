#ifndef MODEL_H
#define MODEL_H

#include <string>
#include <vector>

#include "data/mesh.h"

class Model {
public:
    Model(const std::vector<Mesh> meshes):meshes(meshes) {}
    void render(const Shader &shader)const;
private:
    std::vector<Mesh> meshes;
};

#endif
