#pragma once

#include <string>
#include <cstdint>

class Texture
{
public:
    Texture(const std::string& path);
    ~Texture();

    void bind(uint32_t slot = 0) const;
    void unbind();
private:
    uint32_t id_;
    unsigned char* data_;
    int width_, height_, bpp_;
};
