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

#include "data/model_manager.h"
#include "data/texture_manager.h"
#include "data/shader_manager.h"
#include "data/shader.h"
#include "scene/camera.h"
#include "scene/light.h"
#include "data/material.h"
#include "data/mesh.h"
#include "scene/entity.h"

namespace mist {


class Renderer {
public:
    Renderer() {}
    void render();
    void add_entity(const Entity& entity);
    void set_camera(Camera *camera){ this->camera = camera; }
    void set_light(Light *light){ this->light = light; }

private:
    void render_model(const glm::mat4 &mat_m, const Model &model);

    std::list<const Entity&> entities;
    const Camera *camera;
    const Light *light;

    ModelManager model_manager;
    TextureManager texture_manager;
    ShaderManager shader_manager;
};

} // namespace mist

#endif
