#pragma once

#include <glad/glad.h>
#include <cstddef>

class VertexBuffer {
public:
    VertexBuffer();
    VertexBuffer(const void* data, std::size_t size);
    ~VertexBuffer();

    VertexBuffer(const VertexBuffer&) = delete;
    VertexBuffer& operator=(const VertexBuffer&) = delete;

    void createBuffer(const void* data, std::size_t size);
    void bind() const;
    static void unbind();

    GLuint getId() const noexcept { return id_; }

private:
    GLuint id_ = 0;
};
