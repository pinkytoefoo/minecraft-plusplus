#include <iostream>

#include <glad/glad.h>
#include <glfw/glfw3.h>

#include "VertexBuffer.hpp"

VertexBuffer::VertexBuffer(unsigned int size, const void* data)
{
    glGenBuffers(1, &m_ID);
    glBindBuffer(GL_ARRAY_BUFFER, m_ID);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
    std::cout << "Deleting Vertex Buffer ...\n";
    glDeleteBuffers(1, &m_ID);
}

void VertexBuffer::Bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, m_ID);
}

void VertexBuffer::Unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}