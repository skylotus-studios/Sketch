#include "renderer.h"

renderer::renderer(shader& shaderProgram, vao& VAO, texture& tex) : _shaderProgram(&shaderProgram), _vao(&VAO), _texture(&tex) {}

void renderer::render(const Mat4& model, const Mat4& view, const Mat4& projection) {
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.1f, 0.3f, 0.4f, 0.9f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    _shaderProgram->use();
    _shaderProgram->setInt("texture1", 0);
    _shaderProgram->setMatrix4("model", &model.m[0][0]);
    _shaderProgram->setMatrix4("view", &view.m[0][0]);
    _shaderProgram->setMatrix4("projection", &projection.m[0][0]);
    _texture->bind(0);
    _vao->bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    vao::unbind();
}
