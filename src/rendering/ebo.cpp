#include "ebo.h"

ebo::ebo(GLuint* indices, GLsizeiptr size) : _indices(indices), _size(size) {
    glGenBuffers(1, &_id);
}

ebo::~ebo() {
    glDeleteBuffers(1, &_id);
}

void ebo::bind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, _size, _indices, GL_STATIC_DRAW);
}