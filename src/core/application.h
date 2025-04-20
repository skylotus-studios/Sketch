#pragma once
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include "rendering/renderer.h"
#include "math/math.h"
#include "logging/logger.h"
#include "rendering/shaders/shader.h"
#include "rendering/vao.h"
#include "rendering/vbo.h"
#include "rendering/ebo.h"
#include "utils/texture.h"
#include "timestep.h"
#include "input/input.h"
#include "input/keycodes.h"
#include "input/mousecodes.h"

class application {
public:
    void start();
private:
    void init();
    void run();
    void cleanup() const;
    static void errorCallback(int code, const char* msg);
    static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
    static void mouseMoveCallback(GLFWwindow* window, double x, double y);
    static void mouseWheelCallback(GLFWwindow* window, double xOffset, double yOffset);
    static void setWindowHints();

    GLFWwindow* _window = nullptr;
    renderer* _renderer = nullptr;
    static inline logger _log;

    static constexpr GLuint SCREEN_WIDTH = 3840;
    static constexpr GLuint SCREEN_HEIGHT = 2160;
    static constexpr GLfloat ASPECT_RATIO = 16.0f / 9.0f;
    float _currentTime = 0;
    float _lastFrameTime = 0;

    Mat4 _model;
    Mat4 _view;
    Mat4 _projection;

    std::unique_ptr<vao> _vao;
    std::unique_ptr<vbo> _vbo;
    std::unique_ptr<ebo> _ebo;
    std::unique_ptr<shader> _shaderProgram = nullptr;
    std::unique_ptr<texture> _texture = nullptr;
};
