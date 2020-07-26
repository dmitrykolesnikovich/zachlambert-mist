#include "scene/scene.h"

namespace mist {

bool Scene::add_entity(std::string name, Entity entity)
{
    return entities.insert(
        std::pair<std::string, Entity>(name, entity)).second;
}

Entity *Scene::find_entity(std::string name)
{
    std::unordered_map<std::string, Entity>::iterator search
        = entities.find(name);
    if (search != entities.end()) {
        return &(search->second);
    } else {
        return nullptr;
    }
}

bool Scene::add_light(std::string name, Light light)
{
    return lights.insert(
        std::pair<std::string, Light>(name, light)).second;
}

Light *Scene::find_light(std::string name)
{
    std::unordered_map<std::string, Light>::iterator search
        = lights.find(name);
    if (search != lights.end()) {
        return &(search->second);
    } else {
        return nullptr;
    }
}

} // namespace mist
