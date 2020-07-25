#ifndef MODEL_MANAGER_H
#define MODEL_MANAGER_H

#include <string>
#include <unordered_map>

#include "data/model.h"
#include "data/texture_manager.h"

namespace mist {

class ModelManager {
public:
    ModelManager(const std::string &root_dir):root_dir(root_dir) {}
    const Model &get_model(TextureManager &texture_manager, const std::string &relative_path);
private:
    const std::string root_dir;
    std::unordered_map<std::string, Model> models;
};

} // namespace mist

#endif
