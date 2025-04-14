# ────────────────────────────────────────────────────────────────
# General Configuration
# ────────────────────────────────────────────────────────────────
# Set the minimum required version of CMake
cmake_minimum_required(VERSION 3.24)
# Set the project name
project(Sketch)
# Set the C++ compiler
message("Sketch Compiler: ${CMAKE_CXX_COMPILER}")
# set C++ standard
set(CMAKE_CXX_STANDARD 23)
# Avoid Windows macro conflicts
add_definitions(-DNOMINMAX)

# ────────────────────────────────────────────────────────────────
# Set Variables
# ────────────────────────────────────────────────────────────────
# Set third party directory variable
set(THIRD_PARTY ${CMAKE_SOURCE_DIR}/third_party)
# Set GLFW directory variable
set(GLFW_DIR ${THIRD_PARTY}/glfw-3.4)
# Set GLAD directory variable
set(GLAD_DIR ${THIRD_PARTY}/glad)
# Set STB Image directory variable
set(STB_IMAGE_DIR ${THIRD_PARTY}/stb-image)

# ────────────────────────────────────────────────────────────────
# Include Directories
# ────────────────────────────────────────────────────────────────
include_directories(
    ${CMAKE_SOURCE_DIR}/src
    ${GLFW_DIR}/include
    ${GLAD_DIR}/include
    ${STB_IMAGE_DIR}
)

# ────────────────────────────────────────────────────────────────
# External Libraries (used for multiple CMAKE files)
# ────────────────────────────────────────────────────────────────
# Add GLFW
add_subdirectory(${GLFW_DIR} glfw_build)

# ────────────────────────────────────────────────────────────────
# Source Files
# ────────────────────────────────────────────────────────────────
# Use globbing to automatically include all .cpp files in src
file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS
        ${CMAKE_SOURCE_DIR}/src/*.cpp
        ${CMAKE_SOURCE_DIR}/src/*.c
)

# ────────────────────────────────────────────────────────────────
# Define Executable
# ────────────────────────────────────────────────────────────────
add_executable(${PROJECT_NAME} ${SRC_FILES})

# ────────────────────────────────────────────────────────────────
# Link Libraries
# ────────────────────────────────────────────────────────────────
target_link_libraries(${PROJECT_NAME}
        glfw        # Linked via add_subdirectory
        opengl32    # Native OpenGL library on Windows
)

# ────────────────────────────────────────────────────────────────
# Debug Flags
# ────────────────────────────────────────────────────────────────
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(Sketch PRIVATE SKETCH_DEBUG)
endif()

