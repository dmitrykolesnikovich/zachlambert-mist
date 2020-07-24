#include "render/renderer.h"


void Renderer::render()
{
    for (auto it = render_objects.cbegin(); it != render_objects.cend(); it++) {
        it->first->use_program();
        it->first->use_mat_v(camera->get_view());
        glm::mat4 mvp;
        it->first->use_mat_mvp(mvp);
        // Set uniforms for light information
        for (auto it2 = it->second.cbegin(); it2 != it->second.cbegin(); it2++) {
            // setup material     
            it->first->use_material(*it2->first);
            for (auto it3 = it2->second.cbegin(); it3 != it2->second.cend(); it3++) {
                it->first->use_mat_m(*it3->mat_m);
                mvp = camera->get_projection() * camera->get_view() * (*it3->mat_m);
                glBindVertexArray(it3->VAO);
                glDrawElements(GL_TRIANGLES, it3->index_count, GL_UNSIGNED_SHORT, 0);
            }
        }
    }
}

void Renderer::load_render_object(const Material *material, const Mesh* mesh, const glm::mat4 *mat_model)
{

}
