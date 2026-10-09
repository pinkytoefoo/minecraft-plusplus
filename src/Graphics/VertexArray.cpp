#include "VertexArray.hpp"

VertexArray::VertexArray() {
    glGenVertexArrays(1, &id_);
}

VertexArray::~VertexArray() {
    if (id_ != 0)
        glDeleteVertexArrays(1, &id_);
}

void VertexArray::bind() const {
    glBindVertexArray(id_);
}

void VertexArray::unbind() {
    glBindVertexArray(0);
}

void VertexArray::linkAttribute(
    GLuint index,
    GLint componentCount,
    GLenum type,
    GLboolean normalized,
    GLsizei stride,
    std::size_t offset
) const {
    glEnableVertexAttribArray(index);

    glVertexAttribPointer(
        index,
        componentCount,
        type,
        normalized,
        stride,
        reinterpret_cast<const void*>(offset)
    );
}
