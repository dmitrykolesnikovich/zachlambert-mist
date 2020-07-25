#include "render/renderer.h"

namespace mist {

void Renderer::render()
{
    glm::mat4 mvp;
    for (std::list<Entity*>::const_iterator it = entities.cbegin();
        it != entities.cend(); it++)
    {
        (*it)->get_shader().use_program();
        if (light)
        j   (*it)->get_shader().use_light(*light);
        (*it)->get_shader().use_material((*it)->get_material());
        (*it)->get_shader().use_mat_v(camera->get_view());
        mvp = camera->get_projection() * camera->get_view() * (*it)->get_mat_m();

        glBindVertexArray(it3->VAO);
        glDrawElements(GL_TRIANGLES, it3->index_count, GL_UNSIGNED_SHORT, 0);
    }
}

void Renderer::load_render_object(const Material *material, const Mesh* mesh, const glm::mat4 *mat_model)
{

}

} // namespace mist
