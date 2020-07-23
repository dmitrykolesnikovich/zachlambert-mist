#include "texture_manager.h"

#include <iostream>

#include <GL/glew.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


unsigned int load_texture(const std::string &texture_path)
{
    int width, height, num_channels;
    unsigned char *data = stbi_load(texture_path.c_str(), &width, &height, &num_channels, 0);
    if (!data) {
        return 0;
    } else {
        GLuint texture_id;
        glGenTextures(1, &texture_id);
        glBindTexture(GL_TEXTURE_2D, texture_id);
        switch (num_channels) {
            case 1: // depth (eg: specular or normal map)
                glTexImage2D(
                    GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT,
                    width, height, 0, GL_DEPTH_COMPONENT,
                    GL_UNSIGNED_BYTE, data);
                break;
            case 3: // rgb
                glTexImage2D(
                    GL_TEXTURE_2D, 0, GL_RGB,
                    width, height, 0, GL_RGB,
                    GL_UNSIGNED_BYTE, data);
                break;
            case 4: // rgba
                glTexImage2D(
                    GL_TEXTURE_2D, 0, GL_RGBA,
                    width, height, 0, GL_RGBA,
                    GL_UNSIGNED_BYTE, data);
                break;
            default:
                return 0;
        }
        glGenerateMipmap(GL_TEXTURE_2D);
        // Avoid repeating images. Only works if tex_coords are allowed
        // outside the [0, 1] range, which isn't allowed when using
        // normalised values (which is more efficient)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
  		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        stbi_image_free(data);
        return texture_id;
    }
}


const Texture &TextureManager::get_texture(const std::string &relative_path)
{
    std::unordered_map<std::string, Texture>::const_iterator search
        = textures.find(relative_path);
    if (search != textures.end()) {
        return search->second;
    } else {
        std::pair<std::string, Texture> new_pair(
            relative_path,
            { load_texture(root_dir + relative_path) }
        );
        return textures.insert(new_pair).first->second;
    }
}
