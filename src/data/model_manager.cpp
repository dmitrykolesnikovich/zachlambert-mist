#include "data/model_manager.h"

#include <iostream>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "data/mesh.h"

namespace data {

void process_mesh(TextureManager &texture_manager, std::vector<Mesh> &meshes, const aiScene *scene, aiMesh *mesh)
{
    std::cout << "Processing mesh" << std::endl;
    // Process vertices
    std::vector<Vertex> vertices;
    glm::vec3 position;
    glm::vec2 tex_coords;
    glm::vec3 normal;
    for (std::size_t i = 0; i < mesh->mNumVertices; i++) {
        position = glm::vec3(
            mesh->mVertices[i].x,
            mesh->mVertices[i].y,
            mesh->mVertices[i].z
        );
        if (mesh->mNumUVComponents[0] == 2) {
            tex_coords = glm::vec2(
                mesh->mTextureCoords[0][i].x,
                mesh->mTextureCoords[0][i].y
            );
        }
        normal = glm::vec3(
            mesh->mNormals[i].x,
            mesh->mNormals[i].y,
            mesh->mNormals[i].z
        );
        vertices.push_back(Vertex(position, tex_coords, normal));
    }

    // Process indices
    // Assimp's interface defines meshes as having an array of faces,
    // corresponding to primitives. Since the aiProcesss_Triangulate flag
    // was passed, these faces correspond to the triangle primitives.
    // This contains the indices of the vertices, in the correct order
    std::vector<unsigned short> indices;
    for (std::size_t i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        for (std::size_t j = 0; j < face.mNumIndices; j++) {
            indices.push_back(face.mIndices[j]);
        }
    }

    std::cout << "Processing material" << std::endl;

    // Process material
    const Texture *diffuse_texture = 0;
    glm::vec3 diffuse_color;
    const Texture *specular_texture = 0;
    glm::vec3 specular_color;
    if (mesh->mMaterialIndex >= 0) {
        aiMaterial *ai_material = scene->mMaterials[mesh->mMaterialIndex];

        if (ai_material->GetTextureCount(aiTextureType_DIFFUSE) > 0) {
            aiString relative_path;
            ai_material->GetTexture(aiTextureType_DIFFUSE, 0, &relative_path);
            diffuse_texture = &texture_manager.get_texture(relative_path.C_Str());
        }

        aiColor3D ai_diffuse_color(0.0f, 0.0f, 0.0f);
        ai_material->Get(AI_MATKEY_COLOR_DIFFUSE, ai_diffuse_color);
        diffuse_color = glm::vec3(
            ai_diffuse_color.r, ai_diffuse_color.g, ai_diffuse_color.b
        );

        if (ai_material->GetTextureCount(aiTextureType_SPECULAR) > 0) {
            aiString relative_path;
            ai_material->GetTexture(aiTextureType_SPECULAR, 0, &relative_path);
            specular_texture = &texture_manager.get_texture(relative_path.C_Str());
        }

        aiColor3D ai_specular_color(0.0f, 0.0f, 0.0f);
        ai_material->Get(AI_MATKEY_COLOR_SPECULAR, ai_specular_color);
        specular_color = glm::vec3(
            ai_specular_color.r, ai_specular_color.g, ai_specular_color.b
        );
    }
    Material material = {
        diffuse_texture, diffuse_color, specular_texture, specular_color
    };

    meshes.push_back(Mesh(vertices, indices, material));
}


void process_node(TextureManager &texture_manager, std::vector<Mesh> &meshes, const aiScene *scene, aiNode *node)
{
    for (std::size_t i = 0; i < node->mNumMeshes; i++) {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        process_mesh(texture_manager, meshes, scene, mesh);
    }
    for (std::size_t i = 0; i < node->mNumChildren; i++) {
        process_node(texture_manager, meshes, scene, node->mChildren[i]);
    }
}


Model load_model(TextureManager &texture_manager, const std::string& model_path)
{
    std::cout << "Loading model " << model_path << std::endl;
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(
        model_path.c_str(),
        aiProcess_Triangulate | aiProcess_FlipUVs
    );
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
    }
    std::vector<Mesh> meshes;
    process_node(texture_manager, meshes, scene, scene->mRootNode);
    return Model(meshes);
}


const Model &ModelManager::get_model(TextureManager &texture_manager, const std::string &relative_path)
{
    std::unordered_map<std::string, Model>::const_iterator search
        = models.find(relative_path);
    if (search != models.end()) {
        return search->second;
    } else {
        std::pair<std::string, Model> new_pair(
            relative_path,
            load_model(texture_manager, root_dir + relative_path)
        );
        return models.insert(new_pair).first->second;
    }
}

} // namespace data
