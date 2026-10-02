#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class IndexBuffer
{
public:
    IndexBuffer(const GLuint* indices, GLsizeiptr size);
    ~IndexBuffer();

    void Bind();
    void Unbind();
    unsigned int GetId() const { return m_Id; }

private:
    unsigned int m_Id;
};
