#include "vao.h"

vao::vao(vbo& VBO, ebo& EBO) : _vbo(VBO), _ebo(EBO) {
    glGenVertexArrays(1, &_id);
    bind();
    VBO.bind();
    EBO.bind();
}
vao::~vao() {
    glDeleteVertexArrays(1, &_id);
}

void vao::bind() const {
    glBindVertexArray(_id);
}

void vao::unbind() {
    glBindVertexArray(0);
}
