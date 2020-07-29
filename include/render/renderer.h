#ifndef RENDERER_H
#define RENDERER_H

/* ---- Ideas ----
 * Want flexibility in how rendering is setup and executed to allow for
 * new features to be added, and optimisations to be made, without breaking
 * any external code.
 * The Renderer should be completely responsible for the rendering pipeline.
 * ie: There shouldn't be any opengl calls in other classes.
 * Other classes (like Mesh, Shader, Material), should only store the information.
 * It is up to the renderer how to store the information in buffers and then
 * render it.
 * The Renderer needs to be able to access the original information, to check
 * if it has changed (use a dirty flag in the class), such as when matrices
 * update.
 * Therefore, a pointer/reference to the original data should be kept.
 * When rendering, if the dirty flag is set, any necessary recalculations are
 * made.
 * Entities/scenes should support hierarchical transforms. To decouple this
 * from the renderer, entities should be responsible for updating their
 * absolute transform.
 */

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

namespace mist {

struct RenderObject {
    std::size_t shader_i;
    std::size_t VAO_i;
    std::size_t material_i;
    std::size_t entity_i;
};

bool render_object_compare(const RenderObject &a, const RenderObject &b)
{
    // Return true if a should go before b (strictly)
    // If the items are equal, should return false with either order
    if (a.shader_i != b.shader_i) return (a.shader_i < b.shader_i);
    if (a.VAO_i != b.VAO_i) return (a.VAO_i < b.VAO_i);
    if (a.material_i != b.material_i) return (a.material_i < b.material_i);
    return (a.entity_i < b.entity_i);
    return false;
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
    void render(const Scene &scene);

private:
    void add_model(const std::string &name, Model &model);
    void process_model(const std::string &name, const Model &model);

    // Variables for resource management
    std::string base_dir;
    TextureManager texture_manager;
    ShaderManager shader_manager;
    std::size_t material_id = 0;
    std::size_t entity_id = 0;

    // Containers for processing loaded data 
    std::unordered_map<std::string, Shader> shaders;
    std::unordered_map<std::string, Texture> textures;
    std::unordered_map<std::string, Model> models;
    std::vector<Material> materials;
    // Unpacked datk
    std::set<RenderObject> render_objects;
    // Static data
    std::vector<Vertex> static_vertices;
    std::vector<unsigned short> static_indices;
    unsigned int static_VBO, static_EBO;
    std::vector<unsigned int> static_VAOs;
    // Dynamic data
    std::vector<Vertex> dynamic_vertices;
    std::vector<unsigned short> dynamic_indices;
    unsigned int dynamic_VBO, dynamic_EBO;
    std::vector<unsigned int> dynamic_VAOs;
};

} // namespace mist

#endif
