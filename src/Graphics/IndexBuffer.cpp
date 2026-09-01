#include <iostream>

#include <glad/glad.h>
#include <glfw/glfw3.h>

#include "IndexBuffer.hpp"

// TODO: fix naming convensions with glfw typedefs
// TODO: move setting buffer data to different function (same with the vertex bufer class)
IndexBuffer::IndexBuffer(GLsizeiptr size, GLuint* indices)
{
	glGenBuffers(1, &m_ID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer()
{
    std::cout << "Deleting Index Buffer ...\n";
    glDeleteBuffers(1, &m_ID);
}

void IndexBuffer::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
}

void IndexBuffer::Unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
