
#include "load_model.h"

#include <iostream>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "data/mesh.h"

namespace mist {

void process_mesh(
    const aiScene *scene,
    aiMesh *mesh,
    std::vector<Mesh> &meshes_out,
    std::vector<Material> &materials_out)
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
    Material material;
    if (mesh->mMaterialIndex >= 0) {
        aiMaterial *ai_material = scene->mMaterials[mesh->mMaterialIndex];

        if (ai_material->GetTextureCount(aiTextureType_DIFFUSE) > 0) {
            aiString relative_path;
            ai_material->GetTexture(aiTextureType_DIFFUSE, 0, &relative_path);
            material.diffuse_texture = relative_path.C_Str();
        }

        aiColor3D ai_diffuse_color(0.0f, 0.0f, 0.0f);
        ai_material->Get(AI_MATKEY_COLOR_DIFFUSE, ai_diffuse_color);
        material.diffuse_color = glm::vec3(
            ai_diffuse_color.r, ai_diffuse_color.g, ai_diffuse_color.b
        );

        if (ai_material->GetTextureCount(aiTextureType_SPECULAR) > 0) {
            aiString relative_path;
            ai_material->GetTexture(aiTextureType_SPECULAR, 0, &relative_path);
            material.specular_texture = relative_path.C_Str();
        }

        aiColor3D ai_specular_color(0.0f, 0.0f, 0.0f);
        ai_material->Get(AI_MATKEY_COLOR_SPECULAR, ai_specular_color);
        material.specular_color = glm::vec3(
            ai_specular_color.r, ai_specular_color.g, ai_specular_color.b
        );
    }
    meshes_out.push_back(Mesh(vertices, indices));
    materials_out.push_back(material);
}


void process_node(
    const aiScene *scene,
    aiNode *node,
    std::vector<Mesh> &meshes_out,
    std::vector<Material> &materials_out)
{
    for (std::size_t i = 0; i < node->mNumMeshes; i++) {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        process_mesh(scene, mesh, meshes_out, materials_out);
    }
    for (std::size_t i = 0; i < node->mNumChildren; i++) {
        process_node(scene, node->mChildren[i], meshes_out, materials_out);
    }
}

Model load_model(const std::string &model_path)
{
    Model model;
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
    std::vector<Material> materials;
    process_node(scene, scene->mRootNode, meshes, materials);
    for (size_t i = 0; i < meshes.size(); i++) {
        model.add_mesh(meshes[i], materials[i]);
    }
    return model;
}

} // namespace mist
