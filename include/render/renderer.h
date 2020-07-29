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

#include <map>
#include <list>

#include <glm/glm.hpp>

#include "data/shader.h"
#include "scene/camera.h"
#include "scene/light.h"
#include "data/material.h"
#include "data/mesh.h"
#include "scene/entity.h"
#include "data/resource_config.h"
#include "scene/scene.h"

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

// Usage of the Renderer:
// 1. Construction
// - Generate buffers for the static VBO and EBO, but don't configure
//   them yet.
// 1. Load models:
// - A model is a vector of meshes and materials
// - A mesh is a vector of vertices and indices
// - A material is a structure of properties and texture paths
// 2. While loading models, do the following:
// - For each mesh/material pair:
//   - Load the vertices into the shared vertices vector
//   - Load the indices into the shared indices vector
//   - Create a VAO for the mesh
//   - If it uses a texture, get the texture id
//   - Determine the material shader, and get the shader id
// - For the model:
//   - Store a ModelObject stucture, containing a vector of VAOs
//     and vector of MaterialObjects, with the texture id and shader id
// 3. Initialisation
// - Initialise the VBO and EBO buffers, by calling glBufferData, and pointing
//   to the shared vertices and indices vectors.
// 4. Adding entities
// - A render object is a structure of: shader id, material index, VAO,
//   mvp matrix (with unique mvp matrix id), and pointer to the entity.
// - When adding an entity:
//   - A render object is stored in the render object for each mesh/material pair
//     These are stored in a map, ordered by shader id, material index, VAO, mvp id
//   - A vector of pointers to these render objects is stored in the entity.
//     On destruction, the entity calls invalidate() on all render objects, which
//     causes them to be removed on the next render.
// 5. Rendering
// - Accesses the global information: camera and lights
// - Checks the dirty flag on any of these objects, and if set, recomputes
//   necessary information (ie: their matrices)
// - On rendering, the renderer iterates through the render objects, and due to
//   how they are ordered, minimises the number of times it has to change the
//   render environment (ie: changing shader, material, VAO, etc)
// - When loading each shader, the global uniforms are loaded first
// - When loading an entity mvp, it checks the dirty flag, and if set, recomputes
//   the model matrix. If the camera view matrix was changed, the mvp matrix is
//   also recomputed.

class Renderer {
public:
    Renderer(std::string base_dir = "data"):base_dir(base_dir) {}
    void initialise();
    void render(const Scene &scene);

    bool create_model_from_file(
        const std::string &name,
        const std::string &relative_path
    );
    bool create_model_from_config(
        const std::string &name,
        const MeshConfig &mesh_config,
        const MaterialConfig &material_config
    );
private:
    std::string base_dir;
    // Raw data
    std::unordered_map<std::string, Shader> shaders;
    std::unordered_map<std::string, Texture> textures;
    std::unordered_map<std::string, Model> models;
    // Unpacked datk
    std::map<RenderObject> render_objects;
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
