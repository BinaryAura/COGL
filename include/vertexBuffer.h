#ifndef COGL_VERTEXBUFFER_H
#define COGL_VERTEXBUFFER_H

#include <inttypes.h>

class VertexBuffer {
private:
    uint32_t id;
public:
    VertexBuffer(const void* data, uint32_t size);
    ~VertexBuffer();

    void bind() const;
    void unbind() const;
};


#endif //COGL_VERTEXBUFFER_H
