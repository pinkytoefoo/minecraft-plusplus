#pragma once

#include <glad/glad.h>
#include <cstddef>

class IndexBuffer {
public:
    IndexBuffer();
    IndexBuffer(const GLuint* indices, std::size_t size);
    ~IndexBuffer();

    IndexBuffer(const IndexBuffer&) = delete;
    IndexBuffer& operator=(const IndexBuffer&) = delete;

    void createBuffer(const GLuint* indices, std::size_t size);
    void bind() const;

    GLuint getId() const noexcept { return id_; }

private:
    GLuint id_ = 0;
};
