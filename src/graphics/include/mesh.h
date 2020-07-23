#ifndef MESH_H
#define MESH_H

#include <string>
#include <vector>
#include <glm/glm.hpp>

#include "shader.h"

// A vector or array of Vertexes will have the data laid out
// in the desired order for our VBO, since a struct is just a collection
// of variables, which are laid out sequentially in memory
struct Vertex {
    glm::vec3 position;
    glm::vec2 tex_coords;
    glm::vec3 normal;
};


struct Material {
    unsigned int diffuse_texture;
    glm::vec3 diffuse_color;
    unsigned int specular_texture;
    glm::vec3 specular_color;
};

class Mesh {
public:
    Mesh(
        const std::vector<Vertex> &vertices,
        const std::vector<unsigned int> &indices,
        const Material &material);
    void render(const Shader &shader)const;
    // Raw mesh data
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    Material material;
private:
    // Render data
    unsigned int VAO, VBO, EBO;
};

#endif
