#include "data/mesh.h"
#include <iostream>
#include <stdio.h>

namespace mist {

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

}
