//
// Created by jadunker on 7/7/20.
//

#ifndef COGL_INDEXBUFFER_H
#define COGL_INDEXBUFFER_H

template<class T>
class IndexBuffer {
private:
    uint32_t id;
    uint32_t count;
public:
    IndexBuffer(const T* data, uint32_t count);
    ~IndexBuffer();

    void bind() const;
    void unbind() const;

    uint32_t getCount() const;
};


#endif //COGL_INDEXBUFFER_H
