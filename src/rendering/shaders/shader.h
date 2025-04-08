#pragma once
#include <glad/glad.h>
#include <iostream>
#include <fstream>
#include <string>

class shader {
public:
    shader(const char* vertexPath, const char* fragmentPath);
    void use() const;
    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
private:
    static std::string readFile(const std::string& filePath);
    static void checkCompileErrors(GLuint shader, const std::string& type);
    GLuint id;
    GLuint vertex;
    GLuint fragment;
};
