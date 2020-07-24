#ifndef ENTITY_ENTITY_H
#define ENTITY_ENTITY_H

#include <vector>

#include <glm/glm.hpp>

#include "data/shader.h"
#include "scene/light.h"
#include "data/model.h"
#include "data/texture.h"
#include "scene/camera.h"

namespace scene {

class Entity {
public:
    Entity(const data::Model &model, const data::Shader &shader):
        model(model), shader(shader) {}

    void set_scale(float uniform_scale_factor);
    void set_scale(const glm::vec3 &scale_factors);
    void set_orientation(const glm::mat4 &orientation);
    void set_position(const glm::vec3 &vector);

    void render(const Camera &camera, const Light &light);

private:
    const data::Model &model;
    const data::Shader &shader;

    glm::mat4 model_scaling = glm::mat4(1.0f);
    glm::mat4 model_rotation = glm::mat4(1.0f);
    glm::mat4 model_translation = glm::mat4(1.0f);
    glm::mat4 m;
    glm::mat4 mvp;
};

} // namespace scene

#endif
