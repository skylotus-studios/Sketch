cmake_minimum_required(VERSION 3.24)
project(Sketch)
message("Sketch Compiler: ${CMAKE_CXX_COMPILER}")
# set C++ standard
set(CMAKE_CXX_STANDARD 17)
include_directories(.)
# Set GLFW directory
set(GLFW_DIR ${CMAKE_SOURCE_DIR}/third_party/glfw-3.4)
# Add GLFW
add_subdirectory(${GLFW_DIR} glfw_build)
# Set GLAD directory
set(GLAD_DIR ${CMAKE_SOURCE_DIR}/third_party/glad)
# Include GLFW headers
include_directories(${GLFW_DIR}/include)
# Include GLAD headers
include_directories(${GLAD_DIR}/include)
# Define the Executable (Make sure you specify your source file(s))
add_executable(${PROJECT_NAME} src/main.cpp src/glad.c)
# Link GLFW with your executable
target_link_libraries(${PROJECT_NAME} glfw opengl32)
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(Sketch PRIVATE SKETCH_DEBUG)
endif()
