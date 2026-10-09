#pragma once

#include <glad/glad.h>
#include <cstddef>

class VertexArray {
public:
    VertexArray();
    ~VertexArray();

    VertexArray(const VertexArray&) = delete;
    VertexArray& operator=(const VertexArray&) = delete;

    void bind() const;
    static void unbind();

    void linkAttribute(
        GLuint index,
        GLint componentCount,
        GLenum type,
        GLboolean normalized,
        GLsizei stride,
        std::size_t offset
    ) const;

private:
    GLuint id_ = 0;
};
