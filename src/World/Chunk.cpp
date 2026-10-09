#include <mdspan>

#include "Chunk.hpp"

using ChunkView = std::mdspan<BlockType, std::dextents<size_t, 3>>;

Mesh Chunk::buildMesh() {
    Mesh m;
    m.reserveExpected(256);
    
    for(int x{}; x < 16; ++x) {
        for(int y{}; y < 16; ++y) {
            for(int z{}; z < 16; ++z) {
                if(blocks_[x, y, z] == BlockType::Air)
                    continue;

                if(at(x + 1, y, z) == BlockType::Air)
                    m.addFace(FaceDir::Right, x, y, z, BlockType::Dirt);
                if(at(x - 1, y, z) == BlockType::Air)
                    m.addFace(FaceDir::Left, x, y, z, BlockType::Dirt);
                if(at(x, y, z + 1) == BlockType::Air)
                    m.addFace(FaceDir::Front, x, y, z, BlockType::Dirt);
                if(at(x, y, z - 1) == BlockType::Air)
                    m.addFace(FaceDir::Back, x, y, z, BlockType::Dirt);
                if(at(x, y + 1, z) == BlockType::Air)
                    m.addFace(FaceDir::Top, x, y, z, BlockType::Dirt);
                if(at(x, y - 1, z) == BlockType::Air)
                    m.addFace(FaceDir::Bottom, x, y, z, BlockType::Dirt);
            }
        }
    }

    return m;
}

ChunkRenderer::ChunkRenderer(const Mesh& mesh) {
    upload(mesh);
}

void ChunkRenderer::upload(const Mesh& mesh) {
    if (mesh.vertices.empty() || mesh.indices.empty())
        return;

    vbo_.createBuffer(
        mesh.vertices.data(),
        mesh.vertices.size() * sizeof(Vertex)
    );

    ibo_.createBuffer(
        mesh.indices.data(),
        mesh.indices.size() * sizeof(uint32_t)
    );

    vao_.bind();

    vbo_.bind();

    vao_.linkAttribute(
        0, 3, GL_FLOAT, GL_FALSE,
        sizeof(Vertex), offsetof(Vertex, position)
    );

    vao_.linkAttribute(
        1, 2, GL_FLOAT, GL_FALSE,
        sizeof(Vertex), offsetof(Vertex, uv)
    );

    ibo_.bind();

    VertexArray::unbind();
}

void ChunkRenderer::draw(size_t count) const {
    if (count == 0)
        return;

    vao_.bind();

    glDrawElements(
        GL_TRIANGLES,
        static_cast<GLsizei>(count),
        GL_UNSIGNED_INT,
        nullptr
    );
}
