#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <unordered_map>

#include "data/texture.h"

namespace mist {

class TextureManager{
public:
    TextureManager(std::string base_dir):base_dir(base_dir) {}
    const Texture &get_texture(const std::string &relative_path);
private:
    std::string base_dir;
    std::unordered_map<std::string, Texture> textures;
};

} // namespace mist

#endif
