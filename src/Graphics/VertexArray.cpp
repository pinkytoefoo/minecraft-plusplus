#include "VertexArray.hpp"

VertexArray::VertexArray()
{
    glCreateVertexArrays(1, &m_Id);
}

VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &m_Id);
}

void VertexArray::Bind()
{
    glBindVertexArray(m_Id);
}

void VertexArray::LinkAttribute(GLuint attribIndex, GLuint bindingSlot, GLint size, GLenum type, GLboolean normalized, GLuint relativeOffset) {
    glEnableVertexArrayAttrib(m_Id, attribIndex);
    glVertexArrayAttribFormat(m_Id, attribIndex, size, type, normalized, relativeOffset);
    glVertexArrayAttribBinding(m_Id, attribIndex, bindingSlot);
}

void VertexArray::BindVertexBuffer(GLuint bindingSlot, GLuint bufferHandle, GLintptr offset, GLsizei stride)
{
    glVertexArrayVertexBuffer(m_Id, bindingSlot, bufferHandle, offset, stride);
}

void VertexArray::BindIndexBuffer(GLuint indexBufferHandle)
{
    glVertexArrayElementBuffer(m_Id, indexBufferHandle);
}
