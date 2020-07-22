#include "material_manager.h"

const Material &MaterialManager::get_material(const std::string &name)
{
    std::unordered_map<std::string, Material>::const_iterator search
        = materials.find(name);
    if (find != materials.end()) {
        return find->second;
    } else {

    }
}
