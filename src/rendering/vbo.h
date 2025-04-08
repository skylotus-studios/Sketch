#pragma once
#include <glad/glad.h>

// VERTEX BUFFER OBJECT - stores vertex data in GPU memory
class vbo {
public:
    explicit vbo(const float* vertices, size_t size);
    ~vbo();
    void bind() const;
private:
    const float* vertices;
    size_t size;
    GLuint id{};
};
