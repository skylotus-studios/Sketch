#pragma once
#include <glad/glad.h>

//ELEMENT BUFFER OBJECT - determines the order in which vertices are drawn to prevent duplicates
class ebo {
public:
    explicit ebo(GLuint* indices, size_t size);
    ~ebo();
    void bind() const;
private:
    GLuint id{};
    GLuint* indices;
    size_t size;
};
