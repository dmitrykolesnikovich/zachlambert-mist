#include "render/renderer.h"
#include "data_utils/create_mesh.h"
#include "data_utils/create_material.h"
#include "data_utils/load_model.h"

#include <iostream>

namespace mist {

void Renderer::initialise()
{
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE);
}


void Renderer::render(const Scene &scene)
{
    glClearColor(0.3f, 0.3f, 0.3f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Do any matrix updates on the scene entities
    // and camera


    const Entity *entity;
    glm::mat4 mat_mvp, mat_m;
    for(auto it = scene.get_entities().cbegin();
        it!=scene.get_entities().cend();
        it++)
    {
        /*
        entity = &it->second;
        mat_m = entity->get_mat_m();
        mat_mvp = scene.get_camera().get_projection() * scene.get_camera().get_view() * mat_m;
        // shader.use mvp, m view, light, ...
        Shader shader = ...
        // If not already created, load the shaders and pass the
        // program id back
        Material material = ...
        shader.use();
        shader.use_light(scene.get_lights().begin()->second);
        shader.use_mat_m(mat_m);
        shader.use_mat_mvp(mat_mvp);
        shader.use_mat_v(scene.get_camera().get_view());
        Model model
        for each mesh in model:
            shader.use_material(material);
            glBindVertexElements(mesh.VAO);
            glDrawElements(GL_TRIANGLES, mesh.index_count, GL_UNSIGNED_SHORT, 0);
        */
    }
}

bool Renderer::create_model_from_file(const std::string &name, const std::string &relative_path)
{
    if (models.find(name) != models.end()) {
        Model model = load_model(base_dir + relative_path);
        models.insert(std::pair<std::string, Model>(name, model));
        return true;
    } else {
        return false;
    }
}

bool Renderer::create_model_from_config(
    const std::string &name,
    const MeshConfig &mesh_config,
    const MaterialConfig &material_config)
{
    if (models.find(name) != models.end()) {
        Model model;
        model.add_mesh(create_mesh(mesh_config), create_material(material_config));;
        models.insert(std::pair<std::string, Model>(name, model));
        return true;
    } else {
        return false;
        models.insert(std::pair<std::string, Model>(name, model));
    }
}

} // namespace mist
