#ifndef RENDERER_H
#define RENDERER_H

#include <list>
#include <map>
#include <set>
#include <vector>

#include <glm/glm.hpp>

#include "data/shader.h"
#include "scene/camera.h"
#include "scene/light.h"
#include "data/material.h"
#include "data/mesh.h"
#include "scene/entity.h"
#include "data/resource_config.h"
#include "scene/scene.h"
#include "data/texture_manager.h"
#include "data/shader_manager.h"

namespace mist {

struct RenderObject {
    std::size_t shader_id;
    std::size_t material_id;
    std::size_t entity_id;
    std::size_t mesh_id;
    const Entity *entity;
    std::size_t index_count;
    std::size_t indices_offset;
    std::size_t vertices_offset;
    std::shared_ptr<bool> invalid_flag;
};

bool render_object_compare(const RenderObject &a, const RenderObject &b)
{
    // Return true if a should go before b (strictly)
    // If the items are equal, should return false with either order
    if (a.shader_id != b.shader_id) return (a.shader_id < b.shader_id);
    if (a.material_id != b.material_id) return (a.material_id < b.material_id);
    if (a.entity_id != b.entity_id) return (a.entity_id < b.entity_id);
    return (a.mesh_id < b.mesh_id);
    // Shouldn't have identical render objects, otherwise they just render
    // the same thing
}

class Renderer {
public:
    Renderer(std::string base_dir = "data");
    bool create_model_from_file(
        const std::string &name,
        const std::string &relative_path
    );
    bool create_model_from_config(
        const std::string &name,
        const MeshConfig &mesh_config,
        const MaterialConfig &material_config
    );
    void initialise();
    void add_entity(const Entity& entity);
    void render(const Scene &scene);

private:
    void add_model(const std::string &name, Model &model);

    // Variables for resource management
    std::string base_dir;
    TextureManager texture_manager;
    ShaderManager shader_manager;
    std::size_t material_id = 0;
    std::size_t entity_id = 0;
    std::size_t mesh_id = 0;

    // Containers for processing loaded data 
    std::unordered_map<std::string, Shader> shaders;
    std::unordered_map<std::string, Texture> textures;
    std::unordered_map<std::string, Model> models;
    std::vector<Material> materials;

    // Render information
    std::set<RenderObject> render_objects;

    // Static data (only static for now)
    std::vector<Vertex> static_vertices;
    std::vector<unsigned short> static_indices;
    unsigned int static_VAO, static_VBO, static_EBO;
};

} // namespace mist

#endif
