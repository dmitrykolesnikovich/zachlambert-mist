#include "scene/scene.h"

namespace mist {

bool Scene::add_entity(std::string name, Entity entity)
{
    return entities.insert(
        std::make_pair<std::string, Entity>(name, entity)->second;
}

Entity *Scene::find_entity(std::string name)
{
    std::unordered_map<std::string, Entity>::iterator search
        = entities.find(name);
    if (search != entities.end()) {
        return search;
    } else {
        return nullptr;
    }
}

void Scene::add_light(std::string name, Light light)
{
    return entities.insert(
        std::make_pair<std::string, Entity)(name, entity)->second;
}

Light *Scene::find_light(std::string name)
{
    std::unordered_map<std::string, Light>::iterator search
        = lights.find(name);
    if (search != lights.end()) {
        return search;
    } else {
        return nullptr;
    }
}

} // namespace mist
