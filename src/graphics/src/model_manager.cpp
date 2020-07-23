#include "model_manager.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "mesh.h"

const Model &ModelManager::get_model(const std::string &relative_path);
{
    std::unordered_map<std::string, Model>::const_iterator search
        = models.find(relative_path);
    if (find != models.end()) {
        return find->second;
    } else {
        std::pair<std::string, Model> new_pair(
            relative_path,
            load_model(root_dir + relative_path)
        );
        return models.insert(new_pair)->second;
    }
}

void load_model(TextureManager &texture_manager, const std::string& model_path)
{
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

void process_node(TextureManager texture_manager, std::vector<Mesh> meshes, const aiScene *scene, aiNode *node)
{
    for (std::size_t i = 0; i < node->mNumMeshes; i++) {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        process_mesh(texture_manager, meshes, scene, mesh);
    }
    for (std::size_t i = 0; i < node->mNumChildren; i++) {
        process_node(texture_manager, meshes, scene, node->mChildren[i]);
    }
}

void process_mesh(TextureManager &texture_manager, std::vector<Mesh> meshes, const aiScene *scene, aiMesh *mesh)
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
    Material material;
    if (mesh->mMaterialIndex >= 0) {
        aiMaterial *ai_material = scene->mMaterials[mesh->mMaterialIndex];

        if (ai_material->GetTextureCount(aiTexture_DIFFUSE) > 0) {
            aiString relative_path;
            ai_material->getTexture(aiTextureType_DIFFUSE, 0, &relative_path);
            material.diffuse_texture = texture_manager.get_texture(relative_path);
        }

        aiColor3D diffuse_color(0.0f, 0.0f, 0.0f);
        ai_material->Get(AI_MATKEY_COLOR_DIFFUSE, diffuse_color);
        material.diffuse_color = glm::vec3(
            diffuse_value.r, diffuse_value.g, diffuse_value.b
        );

        if (ai_material->GetTextureCount(aiTexture_DIFFUSE) > 0) {
            aiString relative_path;
            ai_material->getTexture(aiTextureType_DIFFUSE, 0, &relative_path);
            material.diffuse_texture = texture_manager.get_texture(relative_path);
        }

        aiColor3D specular_color(0.0f, 0.0f, 0.0f);
        ai_material->Get(AI_MATKEY_COLOR_SPECULAR, specular_color);
        material.specular_color = glm::vec3(
            specular_value.r, specular_value.g, specular_value.b
        );
    }

    meshes.push_back(Mesh(vertices, indices, material));
}

