#pragma once

class IndexBuffer
{
public:
    IndexBuffer(GLsizeiptr size, GLuint* indices);
    ~IndexBuffer();

    void Bind();
    void Unbind();
private:
    unsigned int m_ID;
};