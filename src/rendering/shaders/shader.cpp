#include "shader.h"

shader::shader(const char* vertexPath, const char* fragmentPath){

    const std::string vertexFile = readFile(vertexPath);
    const std::string fragmentFile = readFile(fragmentPath);

    if (vertexFile.empty() || fragmentFile.empty()) {
        _log.error("Shader source empty. Check file paths or contents. \nVertex File Path: {} \nFragment File Path: {}",
                  vertexPath, fragmentPath);
    }

    const char* vertexSource = vertexFile.c_str();
    const char* fragmentSource = fragmentFile.c_str();

    _vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(_vertex, 1, &vertexSource, nullptr);
    glCompileShader(_vertex);
    checkCompileErrors(_vertex, "VERTEX");

    _fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(_fragment, 1, &fragmentSource, nullptr);
    glCompileShader(_fragment);
    checkCompileErrors(_fragment, "FRAGMENT");

    _id = glCreateProgram();
    glAttachShader(_id, _vertex);
    glAttachShader(_id, _fragment);
    glLinkProgram(_id);
    checkCompileErrors(_id, "PROGRAM");

    glDeleteShader(_vertex);
    glDeleteShader(_fragment);
}

std::string shader::readFile(const std::string& filePath) {
    std::ifstream file;
    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        file.open(filePath);
    } catch ([[maybe_unused]] const std::ifstream::failure& e) {
        _log.error("Could not open shader file at: {} \nPlease check that the file is in the correct directory!",
                   filePath);
    }
    return std::string{(std::istreambuf_iterator(file)), std::istreambuf_iterator<char>()};
}

void shader::checkCompileErrors(const GLuint shader, const std::string& type) {
    int success;
    char infoLog[512];
    if (type != "PROGRAM") {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, 512, nullptr, infoLog);
            _log.error(
                "ERROR::SHADER_COMPILATION_ERROR FOR {} SHADER:\n{}\n -- --------------------------------------------------- -- ",
                type, infoLog);
        }
    } else {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shader, 512, nullptr, infoLog);
            _log.error(
                "ERROR::SHADER_PROGRAM_LINKING_ERROR:\n{}\n -- --------------------------------------------------- -- ",
                infoLog);
        }
    }
}

void shader::use() const {
    glUseProgram(_id);
}

void shader::setBool(const std::string& name, const bool value) const {
    glUniform1i(glGetUniformLocation(_id, name.c_str()), static_cast<int>(value));
}

void shader::setInt(const std::string& name, const int value) const {
    glUniform1i(glGetUniformLocation(_id, name.c_str()), value);
}

void shader::setFloat(const std::string& name, const float value) const {
    glUniform1f(glGetUniformLocation(_id, name.c_str()), value);
}

void shader::setMatrix4(const std::string& name, const float* matrix) const {
    glUniformMatrix4fv(glGetUniformLocation(_id, name.c_str()), 1, GL_TRUE, matrix);
}
