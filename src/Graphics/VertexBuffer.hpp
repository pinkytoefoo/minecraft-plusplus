#pragma once

class VertexBuffer
{
public:
    VertexBuffer(unsigned int size, const void* data);
    ~VertexBuffer();

    void Bind();
    void Unbind();
private:
    unsigned int m_ID;
};