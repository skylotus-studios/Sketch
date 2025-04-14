#include "texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

texture::~texture() {
    glDeleteTextures(1, &_id);
}

void texture::bind(GLuint unit) const {
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, _id);
}

bool texture::loadFromBMP(const std::string& filePath) {
    std::ifstream file(filePath, std::ios::binary);
    if (!file) {
        _log.warn("Failed to open BMP file: {}", filePath);
        return false;
    }

    GLubyte header[54];
    file.read(reinterpret_cast<char*>(header), 54);
    if (header[0] != 'B' || header[1] != 'M') {
        _log.warn("Not a valid BMP file: {}", filePath);
        return false;
    }

    GLuint dataOffset = *reinterpret_cast<unsigned int*>(&header[10]);
    GLuint width = *reinterpret_cast<unsigned int*>(&header[18]);
    GLuint height = *reinterpret_cast<unsigned int*>(&header[22]);
    GLuint dataSize = *reinterpret_cast<unsigned int*>(&header[34]);
    if (dataSize == 0) dataSize = width * height * 3;

    std::vector<GLubyte> data(dataSize);
    file.seekg(dataOffset, std::ios::beg);
    file.read(reinterpret_cast<char*>(data.data()), dataSize);
    file.close();

    glGenTextures(1, &_id);
    glBindTexture(GL_TEXTURE_2D, _id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data.data());
    glGenerateMipmap(GL_TEXTURE_2D);

    return true;
}

bool texture::loadFromSTB(const std::string& filePath) {
    int width, height, channels;
    stbi_set_flip_vertically_on_load(true);
    GLubyte* data = stbi_load(filePath.c_str(), &width, &height, &channels, 0);
    if (!data) {
        _log.warn("Failed to load texture from STB: {}", filePath);
        return false;
    }

    GLenum format = (channels == 3) ? GL_RGB : GL_RGBA;

    glGenTextures(1, &_id);
    glBindTexture(GL_TEXTURE_2D, _id);
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    //Texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_image_free(data);
    return true;
}



