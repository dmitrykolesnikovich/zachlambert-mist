#include "mesh.h"
#include <iostream>

Mesh::Mesh(
        const std::vector<Vertex> &vertices_in,
        const std::vector<unsigned int> &indices_in,
        const Material &material):
    vertices(vertices_in),
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
        indices.size() * sizeof(unsigned int),
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
        1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
        (void*)offsetof(Vertex, tex_coords)
    );

    // Attribute 2: Normal
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(
        2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
        (void*)offsetof(Vertex, normal)
    );

    glBindVertexArray(0); // Unbind the current VAO
}

void Mesh::render(const Shader &shader)const
{
    // Need to have called shader.use() prior to this
    // For now, I'm assuming there is only one texture
    // of each type
    for(std::size_t i = 0; i < textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i);
        switch (textures[i].type) {
            case TextureType::DIFFUSE:
                shader.set_int("material.diffuse", i);
            case TextureType::SPECULAR:
                shader.set_int("material.specular", i);
        }
        glBindTexture(GL_TEXTURE_2D, textures[i].id);
    }
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}
