#include "IndexBuffer.hpp"

IndexBuffer::IndexBuffer() {
    glGenBuffers(1, &id_);
}

IndexBuffer::IndexBuffer(const GLuint* indices, std::size_t size)
    : IndexBuffer{}
{
    createBuffer(indices, size);
}

IndexBuffer::~IndexBuffer() {
    if (id_ != 0)
        glDeleteBuffers(1, &id_);
}

void IndexBuffer::createBuffer(const GLuint* indices, std::size_t size) {
    glBindBuffer(GL_ARRAY_BUFFER, id_);
    glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(size), indices, GL_STATIC_DRAW);
}

void IndexBuffer::bind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_);
}

