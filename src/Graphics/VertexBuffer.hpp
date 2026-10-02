#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class VertexBuffer
{
public:
    VertexBuffer(const void* data, size_t, GLbitfield flags = 0);
    ~VertexBuffer();

    
    void UpdateSubData(GLintptr offset, GLsizeiptr size, const void* data);
    unsigned int GetId() const { return m_Id; }

private:
    unsigned int m_Id{};
};
