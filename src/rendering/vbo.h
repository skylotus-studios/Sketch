#pragma once
#include <glad/glad.h>

// VERTEX BUFFER OBJECT - stores vertex data in GPU memory
class vbo {
public:
    vbo(const float* vertices, GLsizeiptr size);
    ~vbo();
    void bind() const;
private:
    const float* _vertices;
    GLsizeiptr _size;
    GLuint _id{};
};
