#pragma once
#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include "logging/logger.h"

class shader {
public:
    shader(const char* vertexPath, const char* fragmentPath);
    void use() const;
    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
    void setMatrix4(const std::string& name, const float* matrix) const;
private:
    static std::string readFile(const std::string& filePath);
    static void checkCompileErrors(GLuint shader, const std::string& type);
    static inline logger _log;
    GLuint _vertex;
    GLuint _fragment;
    GLuint _id;
};
