#include "model.h"

#include <iostream>

#include <glm/glm.hpp>

Model::Model(const std::string &object_path, const std::string &texture_dir):texture_dir(texture_dir)
{
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(
        object_path.c_str(),
        aiProcess_Triangulate | aiProcess_FlipUVs
    );
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
    }
    processNode(scene, scene->mRootNode);
}

void Model::processNode(const aiScene *scene, aiNode *node)
{
    for (std::size_t i = 0; i < node->mNumMeshes; i++) {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(processMesh(scene, mesh));
    }
    for (std::size_t i = 0; i < node->mNumChildren; i++) {
        processNode(scene, node->mChildren[i]);
    }
}

Mesh Model::processMesh(const aiScene *scene, aiMesh *mesh)
{
    // Process vertices
    std::vector<Vertex> vertices;
    for (std::size_t i = 0; i < mesh->mNumVertices; i++) {
        Vertex vertex;
        vertex.position = glm::vec3(
            mesh->mVertices[i].x,
            mesh->mVertices[i].y,
            mesh->mVertices[i].z
        );
        vertex.tex_coords = glm::vec2(
            // Can have up to 8 sets of texture coords
            // per vertex. We're just using the first.
            mesh->mTextureCoords[0][i].x,
            mesh->mTextureCoords[0][i].y
        );
        vertex.normal = glm::vec3(
            mesh->mNormals[i].x,
            mesh->mNormals[i].y,
            mesh->mNormals[i].z
        );
        vertices.push_back(vertex);
    }

    // Process indices
    // Assimp's interface defines meshes as having an array of faces,
    // corresponding to primitives. Since the aiProcesss_Triangulate flag
    // was passed, these faces correspond to the triangle primitives.
    // This contains the indices of the vertices, in the correct order
    std::vector<unsigned int> indices;
    for (std::size_t i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        for (std::size_t j = 0; j < face.mNumIndices; j++) {
            indices.push_back(face.mIndices[j]);
        }
    }

    // Process material
    std::vector<Texture> textures;
    if (mesh->mMaterialIndex >= 0) {
        aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];

        for (std::size_t i = 0;
            i < material->GetTextureCount(aiTextureType_DIFFUSE);
            i++)
        {
            aiString str;
            material->GetTexture(aiTextureType_DIFFUSE, i, &str);
            Texture texture;
            std::cout << str.C_Str() << std::endl;
            std::cout << texture_dir + str.C_Str() << std::endl;
            texture.id = load_texture(texture_dir + str.C_Str());
            texture.type = TextureType::DIFFUSE;
            textures.push_back(texture);
            std::cout << "Loaded diffuse texture" << std::endl;
        }

        for (std::size_t i = 0;
            i < material->GetTextureCount(aiTextureType_SPECULAR);
            i++)
        {
            aiString str;
            material->GetTexture(aiTextureType_SPECULAR, i, &str);
            Texture texture;
            texture.id = load_texture(texture_dir + str.C_Str());
            texture.type = TextureType::SPECULAR;
            textures.push_back(texture);
            std::cout << "Loaded specular texture" << std::endl;
        }
    }
    std::cout << "Loaded mesh" << std::endl;

    return Mesh(vertices, indices, textures);
}

void Model::render(const Shader &shader)const
{
    for (std::vector<Mesh>::const_iterator it = meshes.begin();
        it != meshes.end(); it++)
    {
        it->render(shader);
    }
}
