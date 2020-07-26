#include "data/resources.h"

namespace mist {

void ModelConfig::set_type(ModelType type)
{
    this->type = type;
}

void ModelConfig::set_dimension(std::string name, float value)
{
    // Overwrite if already present
    dimensions[name] = value;
}

void ModelConfig::set_material(std::string material)
{
    this->material = material;
}


void MaterialConfig::set_color(float r, float g, float b)
{
    color = glm::vec3(r, g, b);
}

void MaterialConfig::set_specularity(float specularity)
{
    this->specularity = specularity;
}


bool Resources::create_model_from_file(std::string name, std::string relative_path)
{
    if (models.find(name) != models.end()) {
        Model model = load_model(base_dir + relative_path);
        models.insert(std::make_pair<std::string, Model>(name, model));
        return true;
    } else {
        return false;
    }
}

bool Resources::create_model_from_config(std::string name, ModelConfig config)
{
    if (models.find(name) != models.end()) {
        Model model = create_model(config);
        models.insert(std::make_pair<std::string, Model>(name, model));
        return true;
    } else {
        return false;
    }
}

bool Resources::create_material_config(std::string name, MaterialConfig config)
{
    if (materials.find(name) != materials.end()) {
        Material material = create_material(config);
        materials.insert(std::make_pair<std::string, Material>(name, material);
        return true;
    } else {
        return false;
    }
}

} // namespace mist
