#include <iostream>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <src/rendering/shaders/shader.cpp>
#include <src/rendering/vao.cpp>
#include <src/rendering/vbo.cpp>
#include <src/rendering/ebo.cpp>
#define null nullptr

// settings
constexpr GLuint SCREEN_WIDTH = 3840;
constexpr GLuint SCREEN_HEIGHT = 2160;

constexpr float vertices[] = {
        -0.25f, -0.25f, 0.0f, //position
         0.0f,  0.0f, 0.0f, //color
         //0.0f,  0.0f, 0.0f, //normal
         //0.0f,  0.0f,       //texture
         0.25f, -0.25f, 0.0f, //position
         1.0f,  0.0f, 1.0f, //color
         //0.0f,  0.0f, 0.0f, //normal
         //1.0f,  0.0f,       //texture
         0.25f,  0.25f, 0.0f, //position
         0.0f,  1.0f, 0.0f, //color
         //0.0f,  0.0f, 0.0f, //normal
         //0.0f,  1.0f,       //texture
        -0.25f,  0.25f, 0.0f, //position
         1.0f,  1.0f, 1.0f, //color
         //0.0f,  0.0f, 0.0f, //normal
         //1.0f,  1.0f        //texture
};
GLuint indices[] = {
        0, 1, 2,
        0, 2, 3
};

void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

static void setWindowHints(){
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

void render() {
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}


int main(){
    glfwSetErrorCallback(error_callback);

    // Initialize the library
    if (!glfwInit()) {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    setWindowHints();

    // Create a windowed mode window and its OpenGL context
    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Sketch Engine", null, null);
    if (window == null) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    // Set callbacks for the window
    glfwSetKeyCallback(window, key_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Load GLAD
    if(!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))){
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    const shader shaderProgram("../src/rendering/shaders/triangle.vert", "../src/rendering/shaders/triangle.frag");

    vbo VBO(vertices, sizeof(vertices));
    ebo EBO(indices, sizeof(indices));
    const auto VAO = vao(VBO, EBO);

    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window)) {
        // Render here
        glClearColor(0.3f, 0.4f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        // Draw the quad
        shaderProgram.use();
        VAO.bind();
        render();
        vao::unbind();
        // Swap front and back buffers
        glfwSwapBuffers(window);
        // Poll for and process events
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
