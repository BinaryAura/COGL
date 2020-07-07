#include <renderer.h>
#include <indexBuffer.h>

template<class T>
IndexBuffer<T>::IndexBuffer(const T *data, uint32_t count) {
    GLCall(glGenBuffers(1, &this->id))
    this->bind();
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(T), data, GL_STATIC_DRAW))
}

template<class T>
IndexBuffer<T>::~IndexBuffer() {
    GLCall(glDeleteBuffers(1, &this->id))
}

template<class T>
inline void IndexBuffer<T>::bind() const {
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->id))
}

template<class T>
inline void IndexBuffer<T>::unbind() const {
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0))
}

template<class T>
uint32_t IndexBuffer<T>::getCount() const {
    return count;
}
