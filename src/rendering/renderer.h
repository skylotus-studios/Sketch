#pragma once
#include "vao.h"
#include "shaders/shader.h"
#include "math/math.h"
#include "utils/texture.h"

class renderer {
public:
    renderer(shader& shaderProgram, vao& VAO, texture& tex);
    ~renderer() = default;
    void render(const Mat4& model, const Mat4& view, const Mat4& projection);
private:
    shader* _shaderProgram;
    vao* _vao;
    texture* _texture;
    static inline logger _log;
};
