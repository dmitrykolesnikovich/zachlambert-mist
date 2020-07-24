#ifndef WORLD_H
#define WORLD_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "model_manager.h"
#include "texture_manager.h"
#include "shader_manager.h"
#include "entity.h"
#include "camera.h"

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
