#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

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
