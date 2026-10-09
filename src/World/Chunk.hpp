#pragma once

#include <array>
#include <cstdint>

#include <glm.hpp>

#include "Util/FlatArray.hpp"
#include "Graphics/VertexArray.hpp"
#include "Graphics/VertexBuffer.hpp"
#include "Graphics/IndexBuffer.hpp"

enum class BlockType : uint8_t
{
    Air = 0,
    Dirt,
};

enum class FaceDir : uint8_t
{
    Right = 0,
    Left,
    Top,
    Bottom,
    Front,
    Back,
    Count,
};

struct Vertex {
    glm::vec3 position;
    glm::vec2 uv;
};

struct LocalVertex
{
    uint8_t x,y,z;
};

constexpr std::array<std::array<LocalVertex, 4>, 6> faceVertices = {{
    {{ {1,0,1}, {1,0,0}, {1,1,0}, {1,1,1} }}, // right
    {{ {0,0,0}, {0,0,1}, {0,1,1}, {0,1,0} }}, // left
    {{ {0,1,1}, {1,1,1}, {1,1,0}, {0,1,0} }}, // top
    {{ {0,0,0}, {1,0,0}, {1,0,1}, {0,0,1} }}, // bottom
    {{ {0,0,1}, {1,0,1}, {1,1,1}, {0,1,1} }}, // front
    {{ {1,0,0}, {0,0,0}, {0,1,0}, {1,1,0} }}, // back
}};

constexpr std::array<glm::vec2, 4> uvs = {{
    {0.0f, 0.0f},
    {1.0f, 0.0f},
    {1.0f, 1.0f},
    {0.0f, 1.0f}
}};

struct Mesh
{
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;
    bool isDirty = false;

    void reserveExpected(size_t expected_quads) {
        vertices.reserve(expected_quads * 4);
        indices.reserve(expected_quads * 6);
    }

    void addFace(FaceDir faceDir, int x, int y, int z) {
        auto& localVertices = faceVertices[static_cast<size_t>(faceDir)];

        auto preStart = static_cast<uint32_t>(vertices.size());
        for(size_t i{}; i < 4; ++i) {
            uint32_t vx = x + localVertices[i].x;
            uint32_t vy = y + localVertices[i].y;
            uint32_t vz = z + localVertices[i].z;
            
            vertices.emplace_back(glm::vec3{vx, vy, vz}, uvs[i]);
        }

        indices.push_back(preStart);
        indices.push_back(preStart + 1u);
        indices.push_back(preStart + 2u);
        indices.push_back(preStart);
        indices.push_back(preStart + 2u);
        indices.push_back(preStart + 3u);
    }
};

struct Chunk
{
    static constexpr int Size = 16;
    static constexpr int BlockCount = Size * Size * Size;

    explicit Chunk(glm::ivec3 coord = {0, 0, 0})
        : chunkCoord(coord) {}

    glm::vec3 getPosition() const {
        return glm::vec3(chunkCoord * Size);
    }

    BlockType& operator[](size_t x, size_t y, size_t z) {
        return blocks_[x, y, z];
    }

    Mesh buildMesh() const;

private:
    glm::ivec3 chunkCoord;

    using BlockArray = FlatArray<BlockType, Size>;
    BlockArray blocks_;

    BlockType at(int x, int y, int z) const {
        if (x < 0 || x >= Size ||
            y < 0 || y >= Size ||
            z < 0 || z >= Size)
            return BlockType::Air;

        return blocks_[x, y, z];
    }
};
class ChunkRenderer
{
public:
    ChunkRenderer() = default;
    ChunkRenderer(const Mesh& mesh);
    void upload(const Mesh& mesh);

    void draw(size_t count) const;

private:
    VertexBuffer vbo_;
    IndexBuffer ibo_;
    VertexArray vao_;
};
