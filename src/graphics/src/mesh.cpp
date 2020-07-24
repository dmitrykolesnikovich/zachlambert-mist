#include "mesh.h"
#include <iostream>
#include <stdio.h>

Vertex::Vertex(glm::vec3 position, glm::vec2 tex_coords, glm::vec3 normal)
{
    // Position straightforward
    this->position = position;
    // Tex coords: Need to convert to normalised ushort
    // If outside the [0, 1] range, clamp coordinates
    this->tex_coords[0] = static_cast<unsigned short>(
        glm::clamp(tex_coords.x, 0.0f, 1.0f) * (float)0xFFFF);
    this->tex_coords[1] = static_cast<unsigned short>(
        glm::clamp(tex_coords.y, 0.0f, 1.0f) * (float)0xFFFF);
    // Normal: Pack normalised 10 bit signed values into an integer
    nx = static_cast<short>(normal.x * (float)0x1FF);
    ny = static_cast<short>(normal.y * (float)0x1FF);
    nz = static_cast<short>(normal.z * (float)0x1FF);
}

Mesh::Mesh(
        const std::vector<Vertex> &vertices_in,
        const std::vector<unsigned short> &indices_in, const Material &material_in): vertices(vertices_in),
    indices(indices_in),
    material(material_in)
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(
        GL_ARRAY_BUFFER,
        vertices.size() * sizeof(Vertex),
        &vertices[0],
        GL_STATIC_DRAW
    );

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData( GL_ELEMENT_ARRAY_BUFFER,
        indices.size() * sizeof(unsigned short),
        &indices[0],
        GL_STATIC_DRAW
    );

    // Attribute 0: Vertex positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(
        0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
        (void*)0
    );

    // Attribute 1: Texture coordinates
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(
        1, 2, GL_UNSIGNED_SHORT, GL_TRUE, sizeof(Vertex),
        (void*)offsetof(Vertex, tex_coords)
    );

    // Attribute 2: Normal
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(
        2, 4, GL_INT_2_10_10_10_REV, GL_TRUE, sizeof(Vertex),
        (void*)offsetof(Vertex, normal_i32)
    );

    glBindVertexArray(0); // Unbind the current VAO
}

void Mesh::render(const Shader &shader)const
{
    shader.use_material(material);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_SHORT, 0);
}
