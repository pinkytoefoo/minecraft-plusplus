#include "VertexBuffer.hpp"

VertexBuffer::VertexBuffer() {
    glGenBuffers(1, &id_);
}

VertexBuffer::VertexBuffer(const void* data, std::size_t size)
    : VertexBuffer{}
{
    createBuffer(data, size);
}

VertexBuffer::~VertexBuffer() {
    if (id_ != 0)
        glDeleteBuffers(1, &id_);
}

void VertexBuffer::createBuffer(const void* data, std::size_t size) {
    glBindBuffer(GL_ARRAY_BUFFER, id_);
    glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(size), data, GL_STATIC_DRAW);
}

void VertexBuffer::bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, id_);
}

void VertexBuffer::unbind() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

