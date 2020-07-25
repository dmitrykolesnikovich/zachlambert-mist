#include "scene/scene.h"

namespace mist {

Scene::Scene():
    model_manager("data/models/"),
    texture_manager("data/textures/"),
    shader_manager("data/shaders/")
{
}

void Scene::handle_input(GLFWwindow *window, const int WIDTH, const int HEIGHT)
{
}

void Scene::update(float dt)
{
    camera.update(dt);
    for(std::vector<Entity>::iterator it = entities.begin();
        it != entities.end();
        it++)
    {
        // it->update(dt);
    }

}

void Scene::render()
{
    for(std::vector<Entity>::iterator it = entities.begin();
        it != entities.end();
        it++)
    {
        it->render(camera, light);
    }
}

} // namespace mist
