#pragma once

class IndexBuffer
{
public:
    IndexBuffer(GLsizeiptr size, const GLuint* indices);
    ~IndexBuffer();

    void Bind();
    void Unbind();
private:
    unsigned int m_ID;
};