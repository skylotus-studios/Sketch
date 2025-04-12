#include "shader.h"
#include "src/logging/logger.h"

logger LOG;

shader::shader(const char* vertexPath, const char* fragmentPath){

    const std::string vertexFile = readFile(vertexPath);
    const std::string fragmentFile = readFile(fragmentPath);

    if (vertexFile.empty() || fragmentFile.empty()) {
        LOG.error("Shader source empty. Check file paths or contents. \nVertex File Path: {} \nFragment File Path: {}",
                  vertexPath, fragmentPath);
    }

    const char* vertexSource = vertexFile.c_str();
    const char* fragmentSource = fragmentFile.c_str();

    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vertexSource, nullptr);
    glCompileShader(vertex);
    checkCompileErrors(vertex, "VERTEX");

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fragmentSource, nullptr);
    glCompileShader(fragment);
    checkCompileErrors(fragment, "FRAGMENT");

    id = glCreateProgram();
    glAttachShader(id, vertex);
    glAttachShader(id, fragment);
    glLinkProgram(id);
    checkCompileErrors(id, "PROGRAM");

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

std::string shader::readFile(const std::string& filePath) {
    std::ifstream file;
    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        file.open(filePath);
    } catch ([[maybe_unused]] const std::ifstream::failure& e) {
        LOG.error("Could not open shader file at: {} \nPlease check that the file is in the correct directory!", filePath);
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
            LOG.error("ERROR::SHADER_COMPILATION_ERROR FOR {} SHADER:\n{}\n -- --------------------------------------------------- -- ", type, infoLog);
        }
    } else {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shader, 512, nullptr, infoLog);
            LOG.error("ERROR::SHADER_PROGRAM_LINKING_ERROR:\n{}\n -- --------------------------------------------------- -- ", infoLog);
        }
    }
}

void shader::use() const {
    glUseProgram(id);
}

void shader::setBool(const std::string& name, const bool value) const {
    glUniform1i(glGetUniformLocation(id, name.c_str()), static_cast<int>(value));
}

void shader::setInt(const std::string& name, const int value) const {
    glUniform1i(glGetUniformLocation(id, name.c_str()), value);
}

void shader::setFloat(const std::string& name, const float value) const {
    glUniform1f(glGetUniformLocation(id, name.c_str()), value);
}

void shader::setMatrix4(const std::string& name, const float* matrix) const {
    glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_TRUE, matrix);
}
