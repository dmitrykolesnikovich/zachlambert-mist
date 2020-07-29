#include "render/renderer.h"
#include "data_utils/create_mesh.h"
#include "data_utils/create_material.h"
#include "data_utils/load_model.h"

#include <iostream>
#include <iterator>

namespace mist {

const bool operator<(const RenderObject &a, const RenderObject &b)
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

// ----- 1: Construction -----

Renderer::Renderer(std::string base_dir):
    base_dir(base_dir), texture_manager(base_dir), shader_manager(base_dir)
{
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE);
}


// ----- 2: Loading and process data -----

bool Renderer::create_model_from_file(const std::string &name, const std::string &relative_path)
{
    if (models.find(name) == models.end()) {
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
    if (models.find(name) == models.end()) {
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
    Material *material;
    for (std::size_t i = 0; i < model.get_mesh_count(); i++) {
        // Add mesh
        mesh = &model.get_mesh(i);
        mesh->vertices_offset = static_vertices.size();
        mesh->indices_offset = static_indices.size();
        std::copy(
            mesh->vertices.cbegin(), mesh->vertices.cend(),
            back_inserter(static_vertices)
        );
        std::copy(
            mesh->indices.cbegin(), mesh->indices.cend(),
            back_inserter(static_indices)
        );
        mesh->id = mesh_id++; // Evaluate then increment

        // Process material
        material = &model.get_material(i);
        if (material->type == MaterialType::TEXTURED) {
            material->diffuse_texture_id = texture_manager.get_texture(
                material->diffuse_texture_path
            ).id;
            material->specular_texture_id = texture_manager.get_texture(
                material->specular_texture_path
            ).id;
        }
        material->shader_index = shader_manager.determine_shader_index(*material);
        material->id = materials.size();
        materials.push_back(*material);
    }
    models.insert(std::pair<std::string, Model>(name, model));
}

void Renderer::initialise()
{
    glGenVertexArrays(1, &static_VAO);
    glGenBuffers(1, &static_VBO);
    glGenBuffers(1, &static_EBO);

    glBindVertexArray(static_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, static_VBO);
    glBufferData(
        GL_ARRAY_BUFFER,
        static_vertices.size() * sizeof(Vertex),
        &static_vertices[0],
        GL_STATIC_DRAW
    );

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, static_EBO);
    glBufferData( GL_ELEMENT_ARRAY_BUFFER,
        static_indices.size() * sizeof(unsigned short),
        &static_indices[0],
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

void Renderer::add_entity(const Entity& entity)
{
    std::shared_ptr<bool> invalid_flag(new bool);
    *invalid_flag = false;
    entity.set_invalid_flag(invalid_flag);
    // TODO: Handle invalid model names
    const Model &model = models.at(entity.get_model());
    for (std::size_t i = 0; i < model.get_mesh_count(); i++) {
        RenderObject render_object;
        render_object.shader_id = model.get_material(i).shader_index;
        render_object.material_id = model.get_material(i).id;
        render_object.entity_id = entity_id++; // Evaluate then increment
        render_object.mesh_id = model.get_mesh(i).id;
        render_object.entity = &entity;
        render_object.index_count = model.get_mesh(i).indices.size();
        render_object.indices_offset = model.get_mesh(i).indices_offset;
        render_object.vertices_offset = model.get_mesh(i).vertices_offset;
        render_object.invalid_flag = invalid_flag;
        render_objects.insert(render_object);
    }
}

void Renderer::render(const Scene &scene)
{
    glClearColor(0.3f, 0.3f, 0.3f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // In the future, have a set of VAOs, for managing different types
    // of data (ie: static vs dynamic, or different vertex attributes)

    glBindVertexArray(static_VAO);
    std::size_t shader_id = 0;
    std::size_t material_id = 0;
    std::size_t entity_id = 0;

    const Shader *shader;
    glm::mat4 mvp;

    bool first = true;

    // camera.update(); - Add in if necessary

    std::set<RenderObject>::iterator it, remove_it;
    for (it = render_objects.begin(); it != render_objects.end(); it++) {
        while (it->is_invalid()) {
            remove_it = it++;
            render_objects.erase(remove_it);
            printf("Removing\n");
        }
        if (it == render_objects.end()) break;
        if (it->shader_id != shader_id || first) {
            shader_id = it->shader_id;
            shader = &shader_manager.get_shader(shader_id);
            shader->use_program();
            // Just use the first light for now
            shader->use_light(scene.get_lights().cbegin()->second);
            shader->use_mat_v(scene.get_camera().get_view());
        }
        if (it->material_id != material_id || first) {
            material_id = it->material_id;
            shader->use_material(materials[material_id]);
        }
        if (it->entity_id != entity_id || first) {
            entity_id = it->entity_id;
            mvp = scene.get_camera().get_projection() * scene.get_camera().get_view() * it->entity->get_mat_m();
            shader->use_mat_m(it->entity->get_mat_m());
            shader->use_mat_mvp(mvp);
        }
        glDrawElementsBaseVertex(
            GL_TRIANGLES, it->index_count, GL_UNSIGNED_SHORT,
            (void*)it->indices_offset, it->vertices_offset
        );
    }
}

} // namespace mist
