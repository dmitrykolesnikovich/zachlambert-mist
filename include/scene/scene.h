#ifndef WORLD_H
#define WORLD_H

#include <string>
#include <unordered_map>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "scene/entity.h"
#include "scene/camera.h"

namespace mist {

struct Scene {
public:
    bool add_entity(std::string name, Entity entity);
    Entity *find_entity(std::string name);
    bool add_light(std::string name, Light light);
    Light *find_light(std::string name);
    void set_camera(Camera camera){ this->camera = camera; }
    Camera &get_camera() { return camera; }
    const Camera &get_camera()const { return camera; }
    const std::unordered_map<std::string, Entity> &get_entities()const{ return entities; }
    const std::unordered_map<std::string, Light> &get_lights()const{ return lights; }
private:
    Camera camera;
    std::unordered_map<std::string, Entity> entities;
    std::unordered_map<std::string, Light> lights;
friend class Renderer;
};

}; // namespace mist

#endif
