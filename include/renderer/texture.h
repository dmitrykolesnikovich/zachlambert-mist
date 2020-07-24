#ifndef TEXTURE_H
#define TEXTURE_H

// Using a struct for textures, instead of just using the program id
// in case I want to add more information later on.
struct Texture {
    unsigned int id;
};

#endif
