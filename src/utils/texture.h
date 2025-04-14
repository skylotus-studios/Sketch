#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <glad/glad.h>
#include <vector>
#include "logging/logger.h"

class texture {
public:
    texture() = default;
    ~texture();
    bool loadFromBMP(const std::string& filePath);
    bool loadFromSTB(const std::string& filePath);
    void bind(GLuint unit = 0) const;
private:
    static inline logger _log;
    GLuint _id{};
};
