#include <iostream>

#include "VertexArray.hpp"

VertexArray::VertexArray()
{
    glGenVertexArrays(1, &m_ID);
}

VertexArray::~VertexArray()
{
    std::cout << "Deleting Vertex Array ...\n";
    glDeleteBuffers(1, &m_ID);
}

void VertexArray::LinkAttrib(VertexBuffer& VBO, GLuint location, GLuint size, GLuint type, bool normalized, int stride, const void* offset)
{
    VBO.Bind();
    glVertexAttribPointer(location, size, type, normalized, stride, offset);
    glEnableVertexAttribArray(location);
    VBO.Unbind();
}

void VertexArray::Bind()
{
    glBindVertexArray(m_ID);
}

void VertexArray::Unbind()
{
    glBindVertexArray(0);
}
