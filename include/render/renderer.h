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
        const ModelConfig &config
    );
private:
    std::string base_dir;
    std::unordered_map<std::string, Shader> shaders;
    std::unordered_map<std::string, Texture> textures;
    std::unordered_map<std::string, Model> models;
};

} // namespace mist

#endif
