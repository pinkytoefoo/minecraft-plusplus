#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "VertexBuffer.hpp"

class VertexArray
{
public:
    VertexArray();
    ~VertexArray();

    void LinkAttribute(GLuint attribIndex, GLuint bindingSlot, GLint size, GLenum type, GLboolean normalized, GLuint relativeOffset);

    void BindVertexBuffer(GLuint bindingSlot, GLuint bufferHandle, GLintptr offset, GLsizei stride);
    void BindIndexBuffer(GLuint indexBufferHandle);
    void Bind();

private:
    unsigned int m_Id{};
};
