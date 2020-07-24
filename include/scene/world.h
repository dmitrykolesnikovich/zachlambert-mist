#ifndef WORLD_H
#define WORLD_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "resources/model_manager.h"
#include "resources/texture_manager.h"
#include "resources/shader_manager.h"
#include "scene/entity.h"
#include "scene/camera.h"

class World {
public:
    World();
    ~World() {}
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

#endif
