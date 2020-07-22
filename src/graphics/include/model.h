#ifndef MODEL_H
#define MODEL_h

#include <string>
#include <vector>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "mesh.h"

class Model {
public:
    Model(const std::string &object_path, const std::string &texture_dir);
    void render(const Shader &shader)const;
private:
    void processNode(const aiScene *scene, aiNode *node);
    Mesh processMesh(const aiScene *scene, aiMesh *mesh);
    std::vector<Mesh> meshes;
    std::string texture_dir;
};

#endif
