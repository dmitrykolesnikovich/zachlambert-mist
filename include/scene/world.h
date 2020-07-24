#ifndef WORLD_H
#define WORLD_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "data/model_manager.h"
#include "data/texture_manager.h"
#include "data/shader_manager.h"
#include "scene/entity.h"
#include "scene/camera.h"

namespace scene {

class World {
public:
    World();
    ~World() {}
    void handle_input(GLFWwindow *window, const int WIDTH, const int HEIGHT);
    void update(float dt);
    void render();
private:
    data::ModelManager model_manager;
    data::TextureManager texture_manager;
    data::ShaderManager shader_manager;
    scene::Camera camera;
    std::vector<Entity> entities;
    scene::Light light;
};

} // namespace scene

#endif
