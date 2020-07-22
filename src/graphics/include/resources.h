#ifndef RESOURCES_H
#define RESOURCES_H

#include <vector>
#include "shader.h"

struct Resources {
    std::vector<Shader> shaders;
    std::vector<Model> models;
};

#endif
