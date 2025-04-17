#pragma once
#include <iostream>
#include <cmath>

constexpr double PI = 3.14159265358979323846f;

struct Vec2 {
    float x, y;

    Vec2() : x(0), y(0) {}
    explicit Vec2(const float value) : x(value), y(value) {}
    explicit Vec2(const int value) : x(static_cast<float>(value)), y(static_cast<float>(value)) {}
    Vec2(const float x, const float y) : x(x), y(y) {}
    Vec2(const int x, const int y) : x(static_cast<float>(x)), y(static_cast<float>(y)) {}

    Vec2 operator*(const Vec2& other) const { return { x * other.x, y * other.y }; }
    Vec2 operator/(const Vec2& other) const { return { x / other.x, y / other.y }; }
    Vec2 operator+(const Vec2& other) const { return { x + other.x, y + other.y }; }
    Vec2 operator-(const Vec2& other) const { return { x - other.x, y - other.y }; }
    Vec2& operator*=(const Vec2& other) { x *= other.x; y *= other.y; return *this; }
    Vec2& operator/=(const Vec2& other) { x /= other.x; y /= other.y; return *this; }
    Vec2& operator+=(const Vec2& other) { x += other.x; y += other.y; return *this; }
    Vec2& operator-=(const Vec2& other) { x -= other.x; y -= other.y; return *this; }
    Vec2 operator*(const float scalar) const { return { x * scalar, y * scalar }; }
    Vec2 operator/(const float scalar) const { return { x / scalar, y / scalar }; }

    [[nodiscard]] Vec2 min(const Vec2& other) const { return { std::fmin(x, other.x), std::fmin(y, other.y) }; }

    [[nodiscard]] Vec2 max(const Vec2& other) const { return { std::fmax(x, other.x), std::fmax(y, other.y) }; }

    [[nodiscard]] Vec2 clamp(const Vec2& minVal, const Vec2& maxVal) const {
        return { fmax(minVal.x, fmin(x, maxVal.x)), fmax(minVal.y, fmin(y, maxVal.y)) };
    }

    [[nodiscard]] float dot(const Vec2& other) const { return x * other.x + y * other.y; }

    [[nodiscard]] Vec2 cross(const Vec2& other) const { return { y * other.x - x * other.y, x * other.y - y * other.x }; }

    [[nodiscard]] float length() const { return std::sqrt(x * x + y * y); }

    [[nodiscard]] float distance(const Vec2& other) const { return (*this-other).length(); }

    [[nodiscard]] Vec2 normalize() const {
        const float len = length();
        return len != 0 ? (*this) / len : Vec2();
    }

    [[nodiscard]] float angle(const Vec2& other) const {
        const float dotProduct = dot(other);
        const float lengths = length() * other.length();
        return lengths > 0 ? std::acos(dotProduct / lengths) * (180.0f / PI) : 0;
    }

    [[nodiscard]] Vec2 rotate(const float angle) const {
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

inline Vec2 operator*(const float scalar, const Vec2& vec) { return vec * scalar; }

struct Vec3 {
    float x, y, z;

    Vec3() : x(0), y(0), z(0) {}
    explicit Vec3(const float value) : x(value), y(value), z(value) {}
    explicit Vec3(const int value) : x(static_cast<float>(value)), y(static_cast<float>(value)), z(static_cast<float>(value)) {}
    Vec3(const float x, const float y, const float z) : x(x), y(y), z(z) {}
    Vec3(const int x, const int y, const int z) : x(static_cast<float>(x)), y(static_cast<float>(y)), z(static_cast<float>(z)) {}

    Vec3 operator*(const Vec3& other) const { return { x * other.x, y * other.y, z * other.z }; }
    Vec3 operator/(const Vec3& other) const { return { x / other.x, y / other.y, z / other.z }; }
    Vec3 operator+(const Vec3& other) const { return { x + other.x, y + other.y, z + other.z }; }
    Vec3 operator-(const Vec3& other) const { return { x - other.x, y - other.y, z - other.z }; }
    Vec3& operator*=(const Vec3& other) { x *= other.x; y *= other.y; z *= other.z; return *this; }
    Vec3& operator/=(const Vec3& other) { x /= other.x; y /= other.y; z /= other.z; return *this; }
    Vec3& operator+=(const Vec3& other) { x += other.x; y += other.y; z += other.z; return *this; }
    Vec3& operator-=(const Vec3& other) { x -= other.x; y -= other.y; z -= other.z; return *this; }
    Vec3 operator*(const float scalar) const { return { x * scalar, y * scalar, z * scalar }; }
    Vec3 operator/(const float scalar) const { return { x / scalar, y / scalar, z / scalar }; }

    static Vec3 up() { return { 0, 1, 0 }; }
    static Vec3 down() { return { 0, -1, 0 }; }
    static Vec3 left() { return { -1, 0, 0 }; }
    static Vec3 right() { return { 1, 0, 0 }; }
    static Vec3 forward() { return { 0, 0, -1 }; }
    static Vec3 back() { return { 0, 0, 1 }; }

    [[nodiscard]] Vec3 min() const { return { std::fmin(x, y), std::fmin(y, z), std::fmin(z, x) }; }

    [[nodiscard]] Vec3 max() const { return { std::fmax(x, y), std::fmax(y, z), std::fmax(z, x) }; }

    [[nodiscard]] Vec3 min(const Vec3& other) const { return { std::fmin(x, other.x), std::fmin(y, other.y), std::fmin(z, other.z) }; }

    [[nodiscard]] Vec3 max(const Vec3& other) const { return { std::fmax(x, other.x), std::fmax(y, other.y), std::fmax(z, other.z) }; }

    [[nodiscard]] Vec3 clamp(const Vec3& minVal, const Vec3& maxVal) const {
        return { fmax(minVal.x, fmin(x, maxVal.x)), fmax(minVal.y, fmin(y, maxVal.y)), fmax(minVal.z, fmin(z, maxVal.z)) };
    }

    [[nodiscard]] float dot(const Vec3& other) const { return x * other.x + y * other.y + z * other.z; }

    [[nodiscard]] Vec3 cross(const Vec3& other) const { return { y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x }; }

    [[nodiscard]] float length() const { return std::sqrt(x * x + y * y + z * z); }

    [[nodiscard]] float distance(const Vec3& other) const { return (*this-other).length(); }

    [[nodiscard]] Vec3 normalize() const {
        const float len = length();
        return len != 0 ? (*this) / len : Vec3();
    }

    [[nodiscard]] float angle(const Vec3& other) const {
        const float dotProduct = dot(other);
        const float lengths = length() * other.length();
        return lengths > 0 ? std::acos(dotProduct / lengths) * (180.0f / PI) : 0;
    }

    [[nodiscard]] Vec3 rotate(const float angle, const Vec3& axis) const {
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

inline Vec3 operator*(const float scalar, const Vec3& vec) { return vec * scalar; }

struct Vec4 {
    float x, y, z, w;

    Vec4() : x(0), y(0), z(0), w(0) {}
    explicit Vec4(const float value) : x(value), y(value), z(value), w(value) {}
    explicit Vec4(const int value) : x(static_cast<float>(value)), y(static_cast<float>(value)), z(static_cast<float>(value)), w(static_cast<float>(value)) {}
    Vec4(const float x, const float y, const float z, const float w) : x(x), y(y), z(z), w(w) {}
    Vec4(const int x, const int y, const int z, const int w) : x(static_cast<float>(x)), y(static_cast<float>(y)), z(static_cast<float>(z)), w(static_cast<float>(w)) {}
    Vec4(const Vec3& vec, const float w) : x(vec.x), y(vec.y), z(vec.z), w(w) {}

    Vec4 operator*(const Vec4& other) const { return { x * other.x, y * other.y, z * other.z, w * other.w }; }
    Vec4 operator/(const Vec4& other) const { return { x / other.x, y / other.y, z / other.z, w / other.w }; }
    Vec4 operator+(const Vec4& other) const { return { x + other.x, y + other.y, z + other.z, w + other.w }; }
    Vec4 operator-(const Vec4& other) const { return { x - other.x, y - other.y, z - other.z, w - other.w }; }
    Vec4& operator*=(const Vec4& other) { x *= other.x; y *= other.y; z *= other.z; w *= other.w; return *this; }
    Vec4& operator/=(const Vec4& other) { x /= other.x; y /= other.y; z /= other.z; w /= other.w; return *this; }
    Vec4& operator+=(const Vec4& other) { x += other.x; y += other.y; z += other.z; w += other.w; return *this; }
    Vec4& operator-=(const Vec4& other) { x -= other.x; y -= other.y; z -= other.z; w -= other.w; return *this; }
    Vec4 operator*(const float scalar) const { return { x * scalar, y * scalar, z * scalar, w * scalar }; }
    Vec4 operator/(const float scalar) const { return { x / scalar, y / scalar, z / scalar, w / scalar }; }

    [[nodiscard]] Vec4 min(const Vec4& other) const { return { std::fmin(x, other.x), std::fmin(y, other.y), std::fmin(z, other.z), std::fmin(w, other.w) }; }

    [[nodiscard]] Vec4 max(const Vec4& other) const { return { std::fmax(x, other.x), std::fmax(y, other.y), std::fmax(z, other.z), std::fmax(w, other.w) }; }

    [[nodiscard]] Vec4 clamp(const Vec4& minVal, const Vec4& maxVal) const {
        return { fmax(minVal.x, fmin(x, maxVal.x)), fmax(minVal.y, fmin(y, maxVal.y)), fmax(minVal.z, fmin(z, maxVal.z)), fmax(minVal.w, fmin(w, maxVal.w)) };
    }

    [[nodiscard]] float dot(const Vec4& other) const { return x * other.x + y * other.y + z * other.z + w * other.w; }

    [[nodiscard]] float length() const { return std::sqrt(x * x + y * y + z * z + w * w); }

    [[nodiscard]] float distance(const Vec4& other) const { return (*this-other).length(); }

    [[nodiscard]] Vec4 normalize() const {
        const float len = length();
        return len != 0 ? *this / len : Vec4();
    }

    [[nodiscard]] Vec3 toRGB() const { return { x, y, z }; }

    [[nodiscard]] float alpha() const { return w; }

    [[nodiscard]] std::string toString() const {
        std::string result;
        result += "\n\nVec4(" + std::to_string(x) + ", " + std::to_string(y)  + ", " + std::to_string(z) + ", " + std::to_string(w) + ")\n";
        return result;
    }
};

inline Vec4 operator*(const float scalar, const Vec4& vec) { return vec * scalar; }

struct Mat4 {
    float m[4][4]{};

    Mat4(){
        m[0][0] = 1; m[0][1] = 0; m[0][2] = 0; m[0][3] = 0;
        m[1][0] = 0; m[1][1] = 1; m[1][2] = 0; m[1][3] = 0;
        m[2][0] = 0; m[2][1] = 0; m[2][2] = 1; m[2][3] = 0;
        m[3][0] = 0; m[3][1] = 0; m[3][2] = 0; m[3][3] = 1;
    }

    static Mat4 identity(){
        return {};
    }

    static Mat4 translation(const Vec3& pos){
        Mat4 result;
        result.m[0][3] = pos.x;
        result.m[1][3] = pos.y;
        result.m[2][3] = pos.z;
        return result;
    }

    static Mat4 scale(const Vec3& size){
        Mat4 result;
        result.m[0][0] = size.x;
        result.m[1][1] = size.y;
        result.m[2][2] = size.z;
        return result;
    }

    static Mat4 rotationX(const float angle){
        Mat4 result;
        const float rad = angle * (PI / 180.0f);
        const float cosA = std::cos(rad);
        const float sinA = std::sin(rad);

        result.m[1][1] = cosA;
        result.m[1][2] = -sinA;
        result.m[2][1] = sinA;
        result.m[2][2] = cosA;

        return result;
    }

    static Mat4 rotationY(const float angle){
        Mat4 result;
        const float rad = angle * (PI / 180.0f);
        const float cosA = std::cos(rad);
        const float sinA = std::sin(rad);

        result.m[0][0] = cosA;
        result.m[0][2] = sinA;
        result.m[2][0] = -sinA;
        result.m[2][2] = cosA;

        return result;
    }

    static Mat4 rotationZ(const float angle){
        Mat4 result;
        const float rad = angle * (PI / 180.0f);
        const float cosA = std::cos(rad);
        const float sinA = std::sin(rad);

        result.m[0][0] = cosA;
        result.m[0][1] = -sinA;
        result.m[1][0] = sinA;
        result.m[1][1] = cosA;

        return result;
    }

    static Mat4 rotation(float angle, const Vec3& axis){
        Mat4 result;
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

    static Mat4 perspective(const float fovDeg, const float aspect, const float nearPlane, const float farPlane) {
        const float fovRad = fovDeg * (PI / 180.0f);
        const float f = 1.0f / std::tan(fovRad / 2.0f);
        const float zRange = nearPlane - farPlane;
        Mat4 result;
        result.m[0][0] = f / aspect;
        result.m[1][1] = f;
        result.m[2][2] = (nearPlane + farPlane) / zRange;
        result.m[2][3] = -1.0f;
        result.m[3][2] = 2.0f * nearPlane * farPlane / zRange;
        return result;
    }

    static Mat4 lookAt(const Vec3& targetPos, const Vec3& cameraPos) {
        const Vec3 f = (cameraPos - targetPos).normalize(); // forward vector - view direction of the camera
        const Vec3 s = f.cross(Vec3::up()).normalize(); // right vector - perpendicular to the forward vector and world up vector
        const Vec3 u = s.cross(f).normalize(); // camera up vector - perpendicular to the forward and right vectors

        Mat4 result;
        result.m[0][0] = s.x; result.m[0][1] = u.x; result.m[0][2] = -f.x;
        result.m[1][0] = s.y; result.m[1][1] = u.y; result.m[1][2] = -f.y;
        result.m[2][0] = s.z; result.m[2][1] = u.z; result.m[2][2] = -f.z;
        result.m[3][0] = -s.dot(targetPos); result.m[3][1] = -u.dot(targetPos); result.m[3][2] = f.dot(targetPos);
        return result;
    }

    Mat4 operator*(const Mat4& other) const {
        Mat4 result;
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