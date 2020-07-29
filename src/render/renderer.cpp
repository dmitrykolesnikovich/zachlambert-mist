#include "render/renderer.h"
#include "data_utils/create_mesh.h"
#include "data_utils/create_material.h"
#include "data_utils/load_model.h"

#include <iostream>

namespace mist {

// ----- 1: Construction -----

Renderer::Renderer(std::string base_dir):base_dir(base_dir)
{
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE);
    glGenBuffers(1, &static_VBO);
    glGenBuffers(1, &static_EBO);
}


// ----- 2: Loading and process data -----

bool Renderer::create_model_from_file(const std::string &name, const std::string &relative_path)
{
    if (models.find(name) != models.end()) {
        Model model = load_model(base_dir + relative_path);
        add_model(name, model);
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
        add_model(name, model);
        return true;
    } else {
        return false;
    }
}

void Renderer::add_model(const std::string &name, Model &model)
{
    Mesh *mesh;
    for (std::size_t i = 0; i < model.get_mesh_count(); i++) {
        mesh = &model.get_mesh(i);
        mesh->vertices_offset = static_vertices.size();
        mesh->indices_offset = static_indices.size();
        std::copy(
            mesh->vertices.cbegin(), mesh->vertices.cend(), static_vertices.end()
        );
        std::copy(
            mesh->indices.cbegin(), mesh->indices.cend(), static_indices.end()
        );
    }

    models.insert(std::pair<std::string, Model>(name, model));
}

void Renderer::initialise()
{
    for (auto it = models.cbegin(); it != models.cend(); it++) {
        process_model(it->first, it->second);
    }
}

void Renderer::process_model(const std::string &name, const Model &model)
{
    unsigned int new_VAOs[model.get_mesh_count()];
    glGenVertexArrays(model.get_mesh_count(), new_VAOs);

    const Mesh *mesh;
    for (std::size_t i = 0; i < model.get_mesh_count(); i++) {
        mesh = &model.get_mesh(i);
        glBindVertexArray(new_VAOs[i]);

        glBindBuffer(GL_ARRAY_BUFFER, static_VBO);
        glBufferData(
            GL_ARRAY_BUFFER,
            static_vertices.size() * sizeof(Vertex),
            &static_vertices[mesh->vertices_offset],
            GL_STATIC_DRAW
        );

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, static_EBO);
        glBufferData( GL_ELEMENT_ARRAY_BUFFER,
            static_indices.size() * sizeof(unsigned short),
            &static_indices[mesh->indices_offset],
            GL_STATIC_DRAW
        );

        // Attribute 0: Vertex positions
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(
            0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
            (void*)0
        );

        // Attribute 1: Texture coordinates
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(
            1, 2, GL_UNSIGNED_SHORT, GL_TRUE, sizeof(Vertex),
            (void*)offsetof(Vertex, tex_coords)
        );

        // Attribute 2: Normal
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(
            2, 4, GL_INT_2_10_10_10_REV, GL_TRUE, sizeof(Vertex),
            (void*)offsetof(Vertex, normal_i32)
        );
    }
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

} // namespace mist
