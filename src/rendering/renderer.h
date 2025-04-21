#pragma once
#include "vao.h"
#include "shaders/shader.h"
#include "math/math.h"
#include "utils/texture.h"

class renderer {
public:
    renderer(shader& shaderProgram, vao& VAO, texture& tex);
    ~renderer() = default;
    void render(const mat4& model, const mat4& view, const mat4& projection);
private:
    shader* _shaderProgram;
    vao* _vao;
    texture* _texture;
    static inline logger _log;
};
