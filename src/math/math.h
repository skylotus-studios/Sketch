#pragma once
#include <iostream>
#include <cmath>

constexpr double PI = 3.14159265358979323846f;

struct vec2 {
    float x, y;

    vec2() : x(0), y(0) {}
    explicit vec2(const float value) : x(value), y(value) {}
    explicit vec2(const int value) : x(static_cast<float>(value)), y(static_cast<float>(value)) {}
    vec2(const float x, const float y) : x(x), y(y) {}
    vec2(const int x, const int y) : x(static_cast<float>(x)), y(static_cast<float>(y)) {}

    vec2 operator*(const vec2& other) const { return { x * other.x, y * other.y }; }
    vec2 operator/(const vec2& other) const { return { x / other.x, y / other.y }; }
    vec2 operator+(const vec2& other) const { return { x + other.x, y + other.y }; }
    vec2 operator-(const vec2& other) const { return { x - other.x, y - other.y }; }
    vec2& operator*=(const vec2& other) { x *= other.x; y *= other.y; return *this; }
    vec2& operator/=(const vec2& other) { x /= other.x; y /= other.y; return *this; }
    vec2& operator+=(const vec2& other) { x += other.x; y += other.y; return *this; }
    vec2& operator-=(const vec2& other) { x -= other.x; y -= other.y; return *this; }
    vec2 operator*(const float scalar) const { return { x * scalar, y * scalar }; }
    vec2 operator/(const float scalar) const { return { x / scalar, y / scalar }; }

    [[nodiscard]] vec2 min(const vec2& other) const { return { std::fmin(x, other.x), std::fmin(y, other.y) }; }

    [[nodiscard]] vec2 max(const vec2& other) const { return { std::fmax(x, other.x), std::fmax(y, other.y) }; }

    [[nodiscard]] vec2 clamp(const vec2& minVal, const vec2& maxVal) const {
        return { fmax(minVal.x, fmin(x, maxVal.x)), fmax(minVal.y, fmin(y, maxVal.y)) };
    }

    [[nodiscard]] float dot(const vec2& other) const { return x * other.x + y * other.y; }

    [[nodiscard]] vec2 cross(const vec2& other) const { return { y * other.x - x * other.y, x * other.y - y * other.x }; }

    [[nodiscard]] float length() const { return std::sqrt(x * x + y * y); }

    [[nodiscard]] float distance(const vec2& other) const { return (*this-other).length(); }

    [[nodiscard]] vec2 normalize() const {
        const float len = length();
        return len != 0 ? (*this) / len : vec2();
    }

    [[nodiscard]] float angle(const vec2& other) const {
        const float dotProduct = dot(other);
        const float lengths = length() * other.length();
        return lengths > 0 ? std::acos(dotProduct / lengths) * (180.0f / PI) : 0;
    }

    [[nodiscard]] vec2 rotate(const float angle) const {
        const float rad = angle * (PI / 180.0f);
        const float cosA = std::cos(rad);
        const float sinA = std::sin(rad);
        return { x * cosA - y * sinA, x * sinA + y * cosA };
    }

    [[nodiscard]] std::string toString() const {
        std::string result;
        result += "\n\nVec2(" + std::to_string(x) + ", " + std::to_string(y)  + ")\n";
        return result;
    }
};

inline vec2 operator*(const float scalar, const vec2& vec) { return vec * scalar; }

struct vec3 {
    float x, y, z;

    vec3() : x(0), y(0), z(0) {}
    explicit vec3(const float value) : x(value), y(value), z(value) {}
    explicit vec3(const int value) : x(static_cast<float>(value)), y(static_cast<float>(value)), z(static_cast<float>(value)) {}
    vec3(const float x, const float y, const float z) : x(x), y(y), z(z) {}
    vec3(const int x, const int y, const int z) : x(static_cast<float>(x)), y(static_cast<float>(y)), z(static_cast<float>(z)) {}

    vec3 operator*(const vec3& other) const { return { x * other.x, y * other.y, z * other.z }; }
    vec3 operator/(const vec3& other) const { return { x / other.x, y / other.y, z / other.z }; }
    vec3 operator+(const vec3& other) const { return { x + other.x, y + other.y, z + other.z }; }
    vec3 operator-(const vec3& other) const { return { x - other.x, y - other.y, z - other.z }; }
    vec3& operator*=(const vec3& other) { x *= other.x; y *= other.y; z *= other.z; return *this; }
    vec3& operator/=(const vec3& other) { x /= other.x; y /= other.y; z /= other.z; return *this; }
    vec3& operator+=(const vec3& other) { x += other.x; y += other.y; z += other.z; return *this; }
    vec3& operator-=(const vec3& other) { x -= other.x; y -= other.y; z -= other.z; return *this; }
    vec3 operator*(const float scalar) const { return { x * scalar, y * scalar, z * scalar }; }
    vec3 operator/(const float scalar) const { return { x / scalar, y / scalar, z / scalar }; }

    static vec3 up() { return { 0, 1, 0 }; }
    static vec3 down() { return { 0, -1, 0 }; }
    static vec3 left() { return { -1, 0, 0 }; }
    static vec3 right() { return { 1, 0, 0 }; }
    static vec3 forward() { return { 0, 0, -1 }; }
    static vec3 back() { return { 0, 0, 1 }; }

    [[nodiscard]] vec3 min() const { return { std::fmin(x, y), std::fmin(y, z), std::fmin(z, x) }; }

    [[nodiscard]] vec3 max() const { return { std::fmax(x, y), std::fmax(y, z), std::fmax(z, x) }; }

    [[nodiscard]] vec3 min(const vec3& other) const { return { std::fmin(x, other.x), std::fmin(y, other.y), std::fmin(z, other.z) }; }

    [[nodiscard]] vec3 max(const vec3& other) const { return { std::fmax(x, other.x), std::fmax(y, other.y), std::fmax(z, other.z) }; }

    [[nodiscard]] vec3 clamp(const vec3& minVal, const vec3& maxVal) const {
        return { fmax(minVal.x, fmin(x, maxVal.x)), fmax(minVal.y, fmin(y, maxVal.y)), fmax(minVal.z, fmin(z, maxVal.z)) };
    }

    [[nodiscard]] float dot(const vec3& other) const { return x * other.x + y * other.y + z * other.z; }

    [[nodiscard]] vec3 cross(const vec3& other) const { return { y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x }; }

    [[nodiscard]] float length() const { return std::sqrt(x * x + y * y + z * z); }

    [[nodiscard]] float distance(const vec3& other) const { return (*this-other).length(); }

    [[nodiscard]] vec3 normalize() const {
        const float len = length();
        return len != 0 ? (*this) / len : vec3();
    }

    [[nodiscard]] float angle(const vec3& other) const {
        const float dotProduct = dot(other);
        const float lengths = length() * other.length();
        return lengths > 0 ? std::acos(dotProduct / lengths) * (180.0f / PI) : 0;
    }

    [[nodiscard]] vec3 rotate(const float angle, const vec3& axis) const {
        const float rad = angle * (PI / 180.0f);
        const float cosA = std::cos(rad);
        const float sinA = std::sin(rad);
        return *this * cosA + axis.cross(*this) * sinA + axis * axis.dot(*this) * (1 - cosA);
    }

    [[nodiscard]] std::string toString() const {
        std::string result;
        result += "\n\nVec3(" + std::to_string(x) + ", " + std::to_string(y)  + ", " + std::to_string(z) + ")\n";
        return result;
    }
};

inline vec3 operator*(const float scalar, const vec3& vec) { return vec * scalar; }

struct vec4 {
    float x, y, z, w;

    vec4() : x(0), y(0), z(0), w(0) {}
    explicit vec4(const float value) : x(value), y(value), z(value), w(value) {}
    explicit vec4(const int value) : x(static_cast<float>(value)), y(static_cast<float>(value)), z(static_cast<float>(value)), w(static_cast<float>(value)) {}
    vec4(const float x, const float y, const float z, const float w) : x(x), y(y), z(z), w(w) {}
    vec4(const int x, const int y, const int z, const int w) : x(static_cast<float>(x)), y(static_cast<float>(y)), z(static_cast<float>(z)), w(static_cast<float>(w)) {}
    vec4(const vec3& vec, const float w) : x(vec.x), y(vec.y), z(vec.z), w(w) {}

    vec4 operator*(const vec4& other) const { return { x * other.x, y * other.y, z * other.z, w * other.w }; }
    vec4 operator/(const vec4& other) const { return { x / other.x, y / other.y, z / other.z, w / other.w }; }
    vec4 operator+(const vec4& other) const { return { x + other.x, y + other.y, z + other.z, w + other.w }; }
    vec4 operator-(const vec4& other) const { return { x - other.x, y - other.y, z - other.z, w - other.w }; }
    vec4& operator*=(const vec4& other) { x *= other.x; y *= other.y; z *= other.z; w *= other.w; return *this; }
    vec4& operator/=(const vec4& other) { x /= other.x; y /= other.y; z /= other.z; w /= other.w; return *this; }
    vec4& operator+=(const vec4& other) { x += other.x; y += other.y; z += other.z; w += other.w; return *this; }
    vec4& operator-=(const vec4& other) { x -= other.x; y -= other.y; z -= other.z; w -= other.w; return *this; }
    vec4 operator*(const float scalar) const { return { x * scalar, y * scalar, z * scalar, w * scalar }; }
    vec4 operator/(const float scalar) const { return { x / scalar, y / scalar, z / scalar, w / scalar }; }

    [[nodiscard]] vec4 min(const vec4& other) const { return { std::fmin(x, other.x), std::fmin(y, other.y), std::fmin(z, other.z), std::fmin(w, other.w) }; }

    [[nodiscard]] vec4 max(const vec4& other) const { return { std::fmax(x, other.x), std::fmax(y, other.y), std::fmax(z, other.z), std::fmax(w, other.w) }; }

    [[nodiscard]] vec4 clamp(const vec4& minVal, const vec4& maxVal) const {
        return { fmax(minVal.x, fmin(x, maxVal.x)), fmax(minVal.y, fmin(y, maxVal.y)), fmax(minVal.z, fmin(z, maxVal.z)), fmax(minVal.w, fmin(w, maxVal.w)) };
    }

    [[nodiscard]] float dot(const vec4& other) const { return x * other.x + y * other.y + z * other.z + w * other.w; }

    [[nodiscard]] float length() const { return std::sqrt(x * x + y * y + z * z + w * w); }

    [[nodiscard]] float distance(const vec4& other) const { return (*this-other).length(); }

    [[nodiscard]] vec4 normalize() const {
        const float len = length();
        return len != 0 ? *this / len : vec4();
    }

    [[nodiscard]] vec3 toRGB() const { return { x, y, z }; }

    [[nodiscard]] float alpha() const { return w; }

    [[nodiscard]] std::string toString() const {
        std::string result;
        result += "\n\nVec4(" + std::to_string(x) + ", " + std::to_string(y)  + ", " + std::to_string(z) + ", " + std::to_string(w) + ")\n";
        return result;
    }
};

inline vec4 operator*(const float scalar, const vec4& vec) { return vec * scalar; }

struct mat4 {
    float m[4][4]{};

    mat4(){
        m[0][0] = 1; m[0][1] = 0; m[0][2] = 0; m[0][3] = 0;
        m[1][0] = 0; m[1][1] = 1; m[1][2] = 0; m[1][3] = 0;
        m[2][0] = 0; m[2][1] = 0; m[2][2] = 1; m[2][3] = 0;
        m[3][0] = 0; m[3][1] = 0; m[3][2] = 0; m[3][3] = 1;
    }

    static mat4 identity(){
        return {};
    }

    static mat4 translation(const vec3& pos){
        mat4 result;
        result.m[0][3] = pos.x;
        result.m[1][3] = pos.y;
        result.m[2][3] = pos.z;
        return result;
    }

    static mat4 scale(const vec3& size){
        mat4 result;
        result.m[0][0] = size.x;
        result.m[1][1] = size.y;
        result.m[2][2] = size.z;
        return result;
    }

    static mat4 rotationX(const float angle){
        mat4 result;
        const float rad = angle * (PI / 180.0f);
        const float cosA = std::cos(rad);
        const float sinA = std::sin(rad);

        result.m[1][1] = cosA;
        result.m[1][2] = -sinA;
        result.m[2][1] = sinA;
        result.m[2][2] = cosA;

        return result;
    }

    static mat4 rotationY(const float angle){
        mat4 result;
        const float rad = angle * (PI / 180.0f);
        const float cosA = std::cos(rad);
        const float sinA = std::sin(rad);

        result.m[0][0] = cosA;
        result.m[0][2] = sinA;
        result.m[2][0] = -sinA;
        result.m[2][2] = cosA;

        return result;
    }

    static mat4 rotationZ(const float angle){
        mat4 result;
        const float rad = angle * (PI / 180.0f);
        const float cosA = std::cos(rad);
        const float sinA = std::sin(rad);

        result.m[0][0] = cosA;
        result.m[0][1] = -sinA;
        result.m[1][0] = sinA;
        result.m[1][1] = cosA;

        return result;
    }

    static mat4 rotation(float angle, const vec3& axis){
        mat4 result;
        const float rad = angle * (PI / 180.0f);
        const float cosA = std::cos(rad);
        const float sinA = std::sin(rad);
        const float oneMinusCos = 1 - cosA;

        result.m[0][0] = cosA + axis.x * axis.x * oneMinusCos;
        result.m[0][1] = axis.x * axis.y * oneMinusCos - axis.z * sinA;
        result.m[0][2] = axis.x * axis.z * oneMinusCos + axis.y * sinA;
        result.m[0][3] = 0;

        result.m[1][0] = axis.y * axis.x * oneMinusCos + axis.z * sinA;
        result.m[1][1] = cosA + axis.y * axis.y * oneMinusCos;
        result.m[1][2] = axis.y * axis.z * oneMinusCos - axis.x * sinA;
        result.m[1][3] = 0;

        result.m[2][0] = axis.z * axis.x * oneMinusCos - axis.y * sinA;
        result.m[2][1] = axis.z * axis.y * oneMinusCos + axis.x * sinA;
        result.m[2][2] = cosA + axis.z * axis.z * oneMinusCos;
        result.m[2][3] = 0;

        result.m[3][0] = 0;
        result.m[3][1] = 0;
        result.m[3][2] = 0;
        result.m[3][3] = 1;

        return result;
    }

    static mat4 perspective(const float fovDeg, const float aspect, const float nearPlane, const float farPlane) {
        const float fovRad = fovDeg * (PI / 180.0f);
        const float f = 1.0f / std::tan(fovRad / 2.0f);
        const float zRange = nearPlane - farPlane;
        mat4 result;
        result.m[0][0] = f / aspect;
        result.m[1][1] = f;
        result.m[2][2] = (nearPlane + farPlane) / zRange;
        result.m[2][3] = -1.0f;
        result.m[3][2] = 2.0f * nearPlane * farPlane / zRange;
        return result;
    }

    static mat4 lookAt(const vec3& cameraPos, const vec3& targetPos) {
        const vec3 f = (cameraPos - targetPos).normalize(); // forward vector - view direction of the camera
        const vec3 s = f.cross(vec3::up()).normalize(); // right vector - perpendicular to the forward vector and world up vector
        const vec3 u = s.cross(f).normalize(); // camera up vector - perpendicular to the forward and right vectors

        mat4 result;
        result.m[0][0] = s.x; result.m[0][1] = u.x; result.m[0][2] = -f.x;
        result.m[1][0] = s.y; result.m[1][1] = u.y; result.m[1][2] = -f.y;
        result.m[2][0] = s.z; result.m[2][1] = u.z; result.m[2][2] = -f.z;
        result.m[3][0] = -s.dot(targetPos); result.m[3][1] = -u.dot(targetPos); result.m[3][2] = f.dot(targetPos);
        return result;
    }

    mat4 operator*(const mat4& other) const {
        mat4 result;
        result.m[0][0] = m[0][0] * other.m[0][0] + m[0][1] * other.m[1][0] + m[0][2] * other.m[2][0] + m[0][3] * other.m[3][0];
        result.m[0][1] = m[0][0] * other.m[0][1] + m[0][1] * other.m[1][1] + m[0][2] * other.m[2][1] + m[0][3] * other.m[3][1];
        result.m[0][2] = m[0][0] * other.m[0][2] + m[0][1] * other.m[1][2] + m[0][2] * other.m[2][2] + m[0][3] * other.m[3][2];
        result.m[0][3] = m[0][0] * other.m[0][3] + m[0][1] * other.m[1][3] + m[0][2] * other.m[2][3] + m[0][3] * other.m[3][3];
        result.m[1][0] = m[1][0] * other.m[0][0] + m[1][1] * other.m[1][0] + m[1][2] * other.m[2][0] + m[1][3] * other.m[3][0];
        result.m[1][1] = m[1][0] * other.m[0][1] + m[1][1] * other.m[1][1] + m[1][2] * other.m[2][1] + m[1][3] * other.m[3][1];
        result.m[1][2] = m[1][0] * other.m[0][2] + m[1][1] * other.m[1][2] + m[1][2] * other.m[2][2] + m[1][3] * other.m[3][2];
        result.m[1][3] = m[1][0] * other.m[0][3] + m[1][1] * other.m[1][3] + m[1][2] * other.m[2][3] + m[1][3] * other.m[3][3];
        result.m[2][0] = m[2][0] * other.m[0][0] + m[2][1] * other.m[1][0] + m[2][2] * other.m[2][0] + m[2][3] * other.m[3][0];
        result.m[2][1] = m[2][0] * other.m[0][1] + m[2][1] * other.m[1][1] + m[2][2] * other.m[2][1] + m[2][3] * other.m[3][1];
        result.m[2][2] = m[2][0] * other.m[0][2] + m[2][1] * other.m[1][2] + m[2][2] * other.m[2][2] + m[2][3] * other.m[3][2];
        result.m[2][3] = m[2][0] * other.m[0][3] + m[2][1] * other.m[1][3] + m[2][2] * other.m[2][3] + m[2][3] * other.m[3][3];
        result.m[3][0] = m[3][0] * other.m[0][0] + m[3][1] * other.m[1][0] + m[3][2] * other.m[2][0] + m[3][3] * other.m[3][0];
        result.m[3][1] = m[3][0] * other.m[0][1] + m[3][1] * other.m[1][1] + m[3][2] * other.m[2][1] + m[3][3] * other.m[3][1];
        result.m[3][2] = m[3][0] * other.m[0][2] + m[3][1] * other.m[1][2] + m[3][2] * other.m[2][2] + m[3][3] * other.m[3][2];
        result.m[3][3] = m[3][0] * other.m[0][3] + m[3][1] * other.m[1][3] + m[3][2] * other.m[2][3] + m[3][3] * other.m[3][3];
        return result;
    }

    [[nodiscard]] std::string toString() const {
        // Convert the matrix to a string representation manually without for loops
        std::string result;
        result += "\n\n| ";
        result += std::to_string(m[0][0]) + ", " + std::to_string(m[0][1]) + ", " + std::to_string(m[0][2]) + ", " + std::to_string(m[0][3]) + " |\n| ";
        result += std::to_string(m[1][0]) + ", " + std::to_string(m[1][1]) + ", " + std::to_string(m[1][2]) + ", " + std::to_string(m[1][3]) + " |\n| ";
        result += std::to_string(m[2][0]) + ", " + std::to_string(m[2][1]) + ", " + std::to_string(m[2][2]) + ", " + std::to_string(m[2][3]) + " |\n| ";
        result += std::to_string(m[3][0]) + ", " + std::to_string(m[3][1]) + ", " + std::to_string(m[3][2]) + ", " + std::to_string(m[3][3]) + " |\n";
        return result;
    }
};