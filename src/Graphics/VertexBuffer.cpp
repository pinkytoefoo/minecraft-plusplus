#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "VertexBuffer.hpp"

VertexBuffer::VertexBuffer(const void* data, size_t size, GLbitfield flags)
{
    glCreateBuffers(1, &m_Id);
    glNamedBufferStorage(m_Id, static_cast<GLsizeiptr>(size), data, flags);
}

VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &m_Id);
}

void VertexBuffer::UpdateSubData(GLintptr offset, GLsizeiptr size, const void* data)
{
    glNamedBufferSubData(m_Id, offset, size, data);
}

