#pragma once
#include <glad/glad.h>

//ELEMENT BUFFER OBJECT - determines the order in which vertices are drawn to prevent duplicates
class ebo {
public:
    ebo(GLuint* indices, GLsizeiptr size);
    ~ebo();
    void bind() const;
private:
    GLuint* _indices;
    GLsizeiptr _size;
    GLuint _id{};
};
