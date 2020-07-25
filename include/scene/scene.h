#ifndef WORLD_H
#define WORLD_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "data/model_manager.h"
#include "data/texture_manager.h"
#include "data/shader_manager.h"
#include "scene/entity.h"
#include "scene/camera.h"

namespace mist {

class Scene {
public:
    Scene();
    ~Scene() {}
    void handle_input(GLFWwindow *window, const int WIDTH, const int HEIGHT);
    void update(float dt);
    void render();
private:
    ModelManager model_manager;
    TextureManager texture_manager;
    ShaderManager shader_manager;
    Camera camera;
    std::vector<Entity> entities;
    Light light;
};

} // namespace mist

#endif
