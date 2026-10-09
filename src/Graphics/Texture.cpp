#include <iostream>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "Texture.hpp"

// TODO: simplify texture count into atlas

Texture::Texture(const std::string& path)
{
    stbi_set_flip_vertically_on_load(1);
    data_ = stbi_load(path.c_str(), &width_, &height_, &bpp_, 0);
    std::cout << bpp_ << '\n';
    if (!data_)
    {
        std::cerr << "Failed to load texture: "
                << path << "\n"
                << stbi_failure_reason() << '\n';
        return;
    }

    glGenTextures(1, &id_);
    
    glBindTexture(GL_TEXTURE_2D, id_);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width_, height_, 0, GL_RGB, GL_UNSIGNED_BYTE, data_);
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);

    if(data_)
        stbi_image_free(data_);
}

Texture::~Texture()
{
    glDeleteTextures(1, &id_);
}

void Texture::bind(uint32_t slot) const
{
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, id_);
}

void Texture::unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}
