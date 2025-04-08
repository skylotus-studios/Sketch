#include "shader.h"

shader::shader(const char* vertexPath, const char* fragmentPath){

    std::string vertexFile = readFile(vertexPath);
    std::string fragmentFile = readFile(fragmentPath);

    if (vertexFile.empty() || fragmentFile.empty()) {
        std::cerr << "Shader source empty. Check file paths or contents. \nVertex File Path: " << vertexPath << "\nFragment File Path: " << fragmentPath << std::endl;
        exit(1);
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
    } catch (const std::ifstream::failure& e) {
        std::cerr << "Could not open shader file at: " << filePath << "\nPlease check that the file is in the correct directory!" << std::endl;
        exit(1);
    }
    return std::string{(std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>()};
}

void shader::checkCompileErrors(const GLuint shader, const std::string& type) {
    int success;
    char infoLog[512];
    if (type != "PROGRAM") {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, 512, nullptr, infoLog);
            std::cerr << "ERROR::SHADER_COMPILATION_ERROR FOR " << type << " SHADER:\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            exit(1);
        }
    } else {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shader, 512, nullptr, infoLog);
            std::cerr << "ERROR::SHADER_PROGRAM_LINKING_ERROR:\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            exit(1);
        }
    }
}

void shader::use() const {
    glUseProgram(id);
}

void shader::setBool(const std::string& name, bool value) const {
    glUniform1i(glGetUniformLocation(id, name.c_str()), static_cast<int>(value));
}

void shader::setInt(const std::string& name, int value) const {
    glUniform1i(glGetUniformLocation(id, name.c_str()), value);
}

void shader::setFloat(const std::string& name, float value) const {
    glUniform1f(glGetUniformLocation(id, name.c_str()), value);
}
