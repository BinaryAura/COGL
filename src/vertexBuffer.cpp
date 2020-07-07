#include <renderer.h>
#include <vertexBuffer.h>

VertexBuffer::VertexBuffer(const void *data, uint32_t size) {
    GLCall(glGenBuffers(1, &this->id))
    this->bind();
    GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW))
}

VertexBuffer::~VertexBuffer() {
    GLCall(glDeleteBuffers(1, &this->id))
}

inline void VertexBuffer::bind() const {
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, this->id))
}

inline void VertexBuffer::unbind() const {
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0))
}
