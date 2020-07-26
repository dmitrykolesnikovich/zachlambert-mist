#include "create_model.h"

#include <math.h>

#include <glm/glm.hpp>
#include "data/mesh.h"

namespace mist {

Mesh create_sphere(const ModelConfig &config)
{
    std::vector<glm::vec3> positions;
    std::vector<glm::vec3> normals;
    const static int N = 8;
    
    float phi, theta;
    float x, y, z;
    positions.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
    normals.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
    for (size_t i = 1; i < N; i++) {
        phi = (M_PI*i)/N;
        z = cos(phi);
        for (size_t j = 0; j < N; j++) {
            theta = (2*M_PI*i)/N; 
            x = sin(phi) * cos(theta);
            y = sin(phi) * sin(theta);
            positions.push_back(glm::vec3(x, y, z));
            normals.push_back(glm::vec3(x, y, z));
        }
    }
    positions.push_back(glm::vec3(0.0f, 0.0f, -1.0f));
    normals.push_back(glm::vec3(0.0f, 0.0f, -1.0f));

    std::vector<Vertex> vertices;
    float r = config.get_dimension("radius", 1.0);
    for (size_t i = 0; i < positions.size(); i++) {
        vertices.push_back(Vertex(
            glm::vec3(
                r * positions[i].x,
                r * positions[i].y,
                r * positions[i].z
            ),
            glm::vec2(0.0f, 0.0f), // tex_coords unused
            normals[i]
        ));
    }

    std::vector<unsigned short> indices;
    // Top strip, common vertex = top
    for (size_t j = 0; j < N; j++) {
        indices.push_back(0);
        indices.push_back(1+j);
        if (j < N-1)
            indices.push_back(2+j);
        else
            indices.push_back(1);
    }
    // Bottom strip, common vertex = bottom
    size_t bot = vertices.size() - 1;
    for (size_t j = 0; j < N; j++) {
        indices.push_back(bot);
        indices.push_back(bot-1-j);
        if (j < N-1)
            indices.push_back(bot-2-j);
        else
            indices.push_back(bot-1);
    }
    // Remaining strips, made up of rectangles between
    size_t strip_1_start, strip_2_start;
    for (size_t i = 1; i < N-1; i++) {
        strip_1_start = 1 + N*i;
        strip_2_start = 1 + N*(i+1);
        for (size_t j = 0; j < N; j++) {
            // First triangle of rectangle
            indices.push_back(strip_1_start + j);
            indices.push_back(strip_2_start + j);
            if (j < N-1) {
                indices.push_back(strip_2_start + j + 1);
            } else {
                indices.push_back(strip_2_start);
            }
            // Second triangle of rectangle
            if (j < N-1) { 
                indices.push_back(strip_2_start + j + 1);
                indices.push_back(strip_1_start + j + 1);
            } else {
                indices.push_back(strip_2_start);
                indices.push_back(strip_1_start);
            }
            indices.push_back(strip_1_start + j);
        }
    }

    return Mesh(vertices, indices);
}

Mesh create_box(const ModelConfig &config)
{
    static const std::vector<glm::vec3> positions = {
        // -X face
        glm::vec3(-1.0f, -1.0f, -1.0f),
        glm::vec3(-1.0f, -1.0f,  1.0f),
        glm::vec3(-1.0f,  1.0f, -1.0f),
        glm::vec3(-1.0f,  1.0f,  1.0f),
        // +X face
        glm::vec3(1.0f, -1.0f, -1.0f),
        glm::vec3(1.0f, -1.0f,  1.0f),
        glm::vec3(1.0f,  1.0f, -1.0f),
        glm::vec3(1.0f,  1.0f,  1.0f),
        // -Y face
        glm::vec3(-1.0f, -1.0f, -1.0f),
        glm::vec3(-1.0f, -1.0f,  1.0f),
        glm::vec3( 1.0f, -1.0f, -1.0f),
        glm::vec3( 1.0f, -1.0f,  1.0f),
        // +Y face
        glm::vec3(-1.0f, 1.0f, -1.0f),
        glm::vec3(-1.0f, 1.0f,  1.0f),
        glm::vec3( 1.0f, 1.0f, -1.0f),
        glm::vec3( 1.0f, 1.0f,  1.0f),
        // -Z face
        glm::vec3(-1.0f, -1.0f, -1.0f),
        glm::vec3(-1.0f,  1.0f, -1.0f),
        glm::vec3( 1.0f, -1.0f, -1.0f),
        glm::vec3( 1.0f,  1.0f, -1.0f),
        // +Z face
        glm::vec3(-1.0f, -1.0f, 1.0f),
        glm::vec3(-1.0f,  1.0f, 1.0f),
        glm::vec3( 1.0f, -1.0f, 1.0f),
        glm::vec3( 1.0f,  1.0f, 1.0f),
    };

    static const std::vector<glm::vec3> normals = {
        // -X face
        glm::vec3(-1.0f, 0.0f, 0.0f),
        glm::vec3(-1.0f, 0.0f, 0.0f),
        glm::vec3(-1.0f, 0.0f, 0.0f),
        glm::vec3(-1.0f, 0.0f, 0.0f),
        // +X face
        glm::vec3(1.0f, 0.0f, 0.0f),
        glm::vec3(1.0f, 0.0f, 0.0f),
        glm::vec3(1.0f, 0.0f, 0.0f),
        glm::vec3(1.0f, 0.0f, 0.0f),
        // -Y face
        glm::vec3(0.0f, -1.0f, 0.0f),
        glm::vec3(0.0f, -1.0f, 0.0f),
        glm::vec3(0.0f, -1.0f, 0.0f),
        glm::vec3(0.0f, -1.0f, 0.0f),
        // +Y face
        glm::vec3(0.0f, 1.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f),
        // -Z face
        glm::vec3(0.0f, 0.0f, -1.0f),
        glm::vec3(0.0f, 0.0f, -1.0f),
        glm::vec3(0.0f, 0.0f, -1.0f),
        glm::vec3(0.0f, 0.0f, -1.0f),
        // +Z face
        glm::vec3(0.0f, 0.0f, 1.0f),
        glm::vec3(0.0f, 0.0f, 1.0f),
        glm::vec3(0.0f, 0.0f, 1.0f),
        glm::vec3(0.0f, 0.0f, 1.0f),
    };

    std::vector<Vertex> vertices;
    float w = config.get_dimension("width", 1.0);
    float h = config.get_dimension("height", 1.0);
    float d = config.get_dimension("depth", 1.0);
    for (size_t i = 0; i < positions.size(); i++) {
        vertices.push_back(Vertex(
            glm::vec3(
                w/2 * positions[i].x,
                h/2 * positions[i].y,
                d/2 * positions[i].z
            ),
            glm::vec2(0.0f, 0.0f), // tex_coords unused
            normals[i]
        ));
    }

    static const std::vector<unsigned short> indices = {
        0, 1, 2, // -X face
        2, 1, 3,
        4, 5, 6, // +X face
        6, 5, 7,
        8, 9, 10, // +Y face
        10, 9, 11,
        12, 13, 14, // -Y face
        14, 13, 15,
        16, 17, 18, // +Z face
        18, 17, 19,
        20, 21, 22, // -Z face
        22, 21, 23
    };
    return Mesh(vertices, indices);
}

Mesh create_mesh(const ModelConfig &config)
{
    switch (config.get_type()) {
        case ModelType::SPHERE:
            return create_sphere(config);
        case ModelType::BOX:
            return create_box(config);
    }
}

Model create_model(const ModelConfig &config)
{
    Model model;
    Mesh mesh = create_mesh(config);
    return model;
}

} // namespace mist
