#include "application.h"

constexpr float vertices[] = {
    -0.25f, -0.25f, 0.0f, //position
     0.0f,  0.0f, 0.0f, //color
     0.0f,  0.0f, 1.0f, //normal
     1.0f,  0.0f,       //texture
     0.25f, -0.25f, 0.0f, //position
     1.0f,  0.0f, 1.0f, //color
     0.0f,  0.0f, 1.0f, //normal
     0.0f,  0.0f,       //texture
     0.25f,  0.25f, 0.0f, //position
     0.0f,  1.0f, 0.0f, //color
     0.0f,  0.0f, 1.0f, //normal
     0.0f,  1.0f,       //texture
    -0.25f,  0.25f, 0.0f, //position
     1.0f,  1.0f, 1.0f, //color
     0.0f,  0.0f, 1.0f, //normal
     1.0f,  1.0f        //texture
};
GLuint indices[] = {
    0, 1, 2,
    0, 2, 3
};

void application::errorCallback(int code, const char* msg) {
    _log.error("GLFW Error {}:\n{}\n", code, msg);
}

void application::framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void application::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    input::onKeyEvent(key, action);
}

void application::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    input::onMouseButtonEvent(button, action);
}

void application::mouseMoveCallback(GLFWwindow* window, double x, double y) {
    input::onMouseMoveEvent(x, y);
}

void application::mouseWheelCallback(GLFWwindow* window, double xOffset, double yOffset) {
    input::onMouseWheelEvent(yOffset);
}

void application::setWindowHints() {
    // window hints
    // https://www.glfw.org/docs/latest/window.html#window_hints
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
    glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
}

void application::init() {
    _currentTime = glfwGetTime();
    _log.init();
    glfwSetErrorCallback(errorCallback);
    // Initialize the library
    if (!glfwInit()) {
        _log.error("Failed to initialize GLFW!");
    }
    setWindowHints();
    // Create a windowed mode window and its OpenGL context
    _window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Sketch Engine", nullptr, nullptr);
    if (_window == nullptr) {
        glfwTerminate();
        _log.error("Failed to create GLFW window");
    }
    // Make the window's context current
    glfwMakeContextCurrent(_window);

    //Set VSync
    glfwSwapInterval(1);

    // Set callbacks for the window
    glfwSetKeyCallback(_window, keyCallback);
    glfwSetMouseButtonCallback(_window, mouseButtonCallback);
    glfwSetCursorPosCallback(_window, mouseMoveCallback);
    glfwSetScrollCallback(_window, mouseWheelCallback);
    glfwSetFramebufferSizeCallback(_window, framebufferSizeCallback);

    // Load GLAD
    if(!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))){
        _log.error("Failed to initialize GLAD");
    }

    _shaderProgram = std::make_unique<shader>("../src/rendering/shaders/triangle.vert", "../src/rendering/shaders/triangle.frag");
    _texture = std::make_unique<texture>();
    _texture->loadFromSTB("../src/assets/test.png");

    _model = mat4::translation({0.0f, 0.0f, 0.0f });
    _view = mat4::lookAt({0, 0, -5}, {0, 0, 0});
    _projection = mat4::perspective(60.0f, ASPECT_RATIO, 0.1f, 100.0f);

    _vbo = std::make_unique<vbo>(vertices, sizeof(vertices));
    _ebo = std::make_unique<ebo>(indices, sizeof(indices));
    _vao = std::make_unique<vao>(*_vbo, *_ebo);
    _texture->bind();
    _renderer = new renderer(*_shaderProgram, *_vao, *_texture);
}

void application::run() {
    while (!glfwWindowShouldClose(_window)) {
        _currentTime = glfwGetTime();
        const timestep deltaTime = _currentTime - _lastFrameTime;
        _lastFrameTime = _currentTime;

        // Render loop
        _renderer->render(_model, _view, _projection);
        glfwSwapBuffers(_window);
        glfwPollEvents();
        if (input::getKey(key.escape)) {
            glfwSetWindowShouldClose(_window, GLFW_TRUE);
        }
        input::update(deltaTime);
    }
}

void application::cleanup() const {
    delete _renderer;
    glfwDestroyWindow(_window);
    glfwTerminate();
}

void application::start() {
    init();
    run();
    cleanup();
}

