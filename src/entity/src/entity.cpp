#include "entity.h"
#include <iostream>

void Entity::set_scale(float uniform_scale_factor)
{
    model_scaling = glm::scale(glm::vec3(
        uniform_scale_factor, uniform_scale_factor, uniform_scale_factor
    ));
}
void Entity::set_scale(const glm::vec3 &scale_factors)
{
    model_scaling = glm::scale(scale_factors);
}

void Entity::set_orientation(const glm::mat4 &orientation)
{
    model_rotation = orientation;
}

void Entity::set_position(const glm::vec3 &vector)
{
    model_translation = glm::translate(vector);
}

void Entity::render(const Camera &camera, const Light &light)
{
    m = model_translation * model_rotation * model_scaling;
    mvp = camera.get_projection() * camera.get_view() * m;

    shader.use(mvp, m, camera.get_view(), light);

    model.render(shader);
}
