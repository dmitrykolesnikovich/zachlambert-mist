#include "renderer.h"


void Renderer::render()
{
    for (auto it = render_objects.cbegin(); it != render_objects.cend(); it++) {
        it->first->use_program();
        // Set uniforms for light information
        for (auto it2 = it->second.cbegin(); it2 != it->second.cbegin(); it2++) {
            // setup material     
            it->first->use_material(*it2->first);
            for (auto it3 = it2->second.cbegin(); it3 != it2->second.cend(); it3++) {
                glBindVertexArray(it3->VAO);
                glDrawElements(GL_TRIANGLES, it3->index_count, GL_UNSIGNED_SHORT, 0);
            }
        }
    }
}
