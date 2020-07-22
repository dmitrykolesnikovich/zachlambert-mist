#ifndef MATERIAL_MANAGER_H
#define MATERIAL_MANAGER_H

#include <string>
#include <unordered_map>

/* Currently supported material properties
 * - Diffuse rgb: Texture or constant (used for ambient as well)
 * - Specular value: Texture (grayscale) or constant
 */
struct Material {
    unsigned int diffuse_texture;
    float diffuse_value;
    unsigned int specular_texture;
    float specular_value;
};

class MaterialManager {
public:
    MaterialManager(const std::string &root_dir):root_dir(root_dir) {}
    const Material &get_material(const std::string &name);
private:
    std::string root_dir;
    std::unordered_map<std::string, Material> materials;
};

#endif
