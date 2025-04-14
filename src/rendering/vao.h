#pragma once
#include <glad/glad.h>
#include "vbo.h"
#include "ebo.h"

// VERTEX ARRAY OBJECT - stores the vertex attribute structure
class vao {
public:
    vao(vbo& VBO, ebo& EBO);
    ~vao();
    void bind() const;
    static void unbind() ;
private:
    vbo& _vbo;
    ebo& _ebo;
    GLuint _id{};
};
