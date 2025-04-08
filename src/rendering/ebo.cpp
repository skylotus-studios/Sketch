#include "ebo.h"

ebo::ebo(GLuint* indices, size_t size) : indices(indices), size(size) {
    glGenBuffers(1, &id);
}

ebo::~ebo() {
    glDeleteBuffers(1, &id);
}

void ebo::bind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}