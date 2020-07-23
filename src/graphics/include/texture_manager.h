#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <string>
#include <unordered_map>

class TextureManager {
public:
    TextureManager(const std::string &root_dir):root_dir(root_dir) {}
    const unsigned int get_texture(const std::string &relative_path);
    unsigned int load_texture(const std::string &relative_path);
private:
    const std::string root_dir;
    std::unordered_map<std::string, unsigned int> textures;
};

#endif
