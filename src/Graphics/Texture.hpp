#pragma once

#include <string>

class Texture
{
public:
    Texture(const std::string& path);
    ~Texture();

    void Bind(uint32_t slot = 0) const;
    void Unbind();
private:
    uint32_t m_RendererID;
    unsigned char* m_Data;
    int m_Width, m_Height, m_BPP;
};