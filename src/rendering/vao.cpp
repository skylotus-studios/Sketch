#include "vao.h"

vao::vao(vbo& VBO, ebo& EBO) : VBO(VBO), EBO(EBO) {
    glGenVertexArrays(1, &id);
    bind();
    VBO.bind();
    EBO.bind();
}
vao::~vao() {
    glDeleteVertexArrays(1, &id);
}

void vao::bind() const {
    glBindVertexArray(id);
}

void vao::unbind() {
    glBindVertexArray(0);
}
