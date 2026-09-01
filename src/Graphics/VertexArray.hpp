#pragma once

#include <glad/glad.h>
#include <glfw/glfw3.h>

#include "VertexBuffer.hpp"

class VertexArray
{
public:
    VertexArray();
    ~VertexArray();

    // using GLuint because 'unsigned int' is too long
    void LinkAttrib(VertexBuffer& VBO, GLuint location, GLuint size, GLuint type, bool normalized, int stride, const void* offset);

    void Bind();
    void Unbind();
private:
    unsigned int m_ID;
};