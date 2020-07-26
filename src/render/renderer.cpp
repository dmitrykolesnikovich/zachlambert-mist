#include "render/renderer.h"

namespace mist {

void render(const Scene &scene, const Resources &resources)
{

}

void Renderer::add_entity(const Entity& entity)
{
    entities.push_back(entity);
}

} // namespace mist
