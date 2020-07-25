#ifndef ENTITY_ENTITY_H
#define ENTITY_ENTITY_H

#include <vector>

#include <glm/glm.hpp>

#include "data/shader.h"
#include "scene/light.h"
#include "data/model.h"
#include "data/texture.h"
#include "scene/camera.h"

namespace mist {

class Entity {
public:
    Entity(const Model &model): model(model) {}

    void set_scale(float uniform_scale_factor);
    void set_scale(const glm::vec3 &scale_factors);
    void set_orientation(const glm::mat4 &orientation);
    void set_position(const glm::vec3 &vector);

    const Model &get_model()const{ return model; }
    const glm::mat4 get_mat_m()const{ return mvp; }

private:
    const Model &model;

    glm::mat4 model_scaling = glm::mat4(1.0f);
    glm::mat4 model_rotation = glm::mat4(1.0f);
    glm::mat4 model_translation = glm::mat4(1.0f);
    glm::mat4 m;
    glm::mat4 mvp;
};

} // namespace mist

#endif
