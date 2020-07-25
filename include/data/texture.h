#ifndef TEXTURE_H
#define TEXTURE_H

namespace mist {

// Using a struct for textures, instead of just using the program id
// in case I want to add more information later on.
struct Texture {
    unsigned int id;
};

} // namespace mist

#endif
