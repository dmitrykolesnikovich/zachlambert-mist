#include "texture_manager.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

const Texture &TextureManager::get_texture(const std::string &relative_path)
{
    std::unordered_map<std::string, Texture>::const_iterator search
        = textures.find(relative_path);
    if (find != textures.end()) {
        return find->second;
    } else {
        std::pair<std::string, Texture> new_pair(
            relative_path,
            load_texture(root_dir + relative_path)
        );
        return textures.insert(new_pair)->second;
    }
}

Texture load_texture(const std::string &texture_path)
{
    int width, height, num_channels;
    unsigned char *data = stbi_load(texture_path.c_str(), &width, &height, &num_channels, 0);
    if (!data) {
        printf("Failed to load image %s.\n", texture_path.c_str());
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
            case 3: // rgb
                glTexImage2D(
                    GL_TEXTURE_2D, 0, GL_RGB,
                    width, height, 0, GL_RGB,
                    GL_UNSIGNED_BYTE, data);
            case 4: // rgba
                glTexImage2D(
                    GL_TEXTURE_2D, 0, GL_RGBA,
                    width, height, 0, GL_RGBA,
                    GL_UNSIGNED_BYTE, data);
        }
        glGenerateMipmap(GL_TEXTURE_2D);
        // Always repeat the image
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        stbi_image_free(data);
        return Texture{ texture_id };
    }
}(
