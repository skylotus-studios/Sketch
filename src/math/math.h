#pragma once
#include <iostream>
#include <cmath>

const double PI = 3.14159265358979323846f;

struct Vec2 {
    float x, y;

    Vec2() : x(0), y(0) {}
    Vec2(float value) : x(value), y(value) {}
    Vec2(int value) : x(static_cast<float>(value)), y(static_cast<float>(value)) {}
    Vec2(float x, float y) : x(x), y(y) {}
    Vec2(int x, int y) : x(static_cast<float>(x)), y(static_cast<float>(y)) {}

    Vec2 operator+(const Vec2& other) const { return { x + other.x, y + other.y }; }
    Vec2 operator-(const Vec2& other) const { return { x - other.x, y - other.y }; }
    Vec2 operator*(const Vec2& other) const { return { x * other.x, y * other.y }; }
    Vec2 operator/(const Vec2& other) const { return { x / other.x, y / other.y }; }
    Vec2& operator+=(const Vec2& other) { x += other.x; y += other.y; return *this; }
    Vec2& operator-=(const Vec2& other) { x -= other.x; y -= other.y; return *this; }
    Vec2& operator*=(const Vec2& other) { x *= other.x; y *= other.y; return *this; }
    Vec2& operator/=(const Vec2& other) { x /= other.x; y /= other.y; return *this; }
    Vec2 operator*(float scalar) const { return { x * scalar, y * scalar }; }
    Vec2 operator/(float scalar) const { return { x / scalar, y / scalar }; }

    Vec2 min(const Vec2& other) const { return { std::fmin(x, other.x), std::fmin(y, other.y) }; }

    Vec2 max(const Vec2& other) const { return { std::fmax(x, other.x), std::fmax(y, other.y) }; }

    Vec2 clamp(const Vec2& minVal, const Vec2& maxVal) const {
        return { fmax(minVal.x, fmin(x, maxVal.x)), fmax(minVal.y, fmin(y, maxVal.y)) };
    }

    float dot(const Vec2& other) const { return x * other.x + y * other.y; }

    Vec2 cross(const Vec2& other) const { return { y * other.x - x * other.y, x * other.y - y * other.x }; }

    float length() const { return std::sqrt(x * x + y * y); }

    float distance(const Vec2& other) const { return (*this-other).length(); }

    Vec2 normalize() const {
        float len = length();
        return len != 0 ? (*this) / len : Vec2();
    }

    float angle(const Vec2& other) const {
        float dotProduct = dot(other);
        float lengths = length() * other.length();
        return lengths > 0 ? std::acos(dotProduct / lengths) * (180.0f / PI) : 0;
    }

    Vec2 rotate(float angle) const {
        float rad = angle * (PI / 180.0f);
        float cosA = std::cos(rad);
        float sinA = std::sin(rad);
        return Vec2( x * cosA - y * sinA, x * sinA + y * cosA );
    }

    void print() const { std::cout << "Vec2(" << x << ", " << y << ")\n" << std::endl;}
};

inline Vec2 operator*(float scalar, const Vec2& vec) { return vec * scalar; }

struct Vec3 {
    float x, y, z;

    Vec3() : x(0), y(0), z(0) {}
    Vec3(float value) : x(value), y(value), z(value) {}
    Vec3(int value) : x(static_cast<float>(value)), y(static_cast<float>(value)), z(static_cast<float>(value)) {}
    Vec3(float x, float y, float z) : x(x), y(y), z(z) {}
    Vec3(int x, int y, int z) : x(static_cast<float>(x)), y(static_cast<float>(y)), z(static_cast<float>(z)) {}

    Vec3 operator+(const Vec3& other) const { return { x + other.x, y + other.y, z + other.z }; }
    Vec3 operator-(const Vec3& other) const { return { x - other.x, y - other.y, z - other.z }; }
    Vec3 operator*(const Vec3& other) const { return { x * other.x, y * other.y, z * other.z }; }
    Vec3 operator/(const Vec3& other) const { return { x / other.x, y / other.y, z / other.z }; }
    Vec3& operator+=(const Vec3& other) { x += other.x; y += other.y; z += other.z; return *this; }
    Vec3& operator-=(const Vec3& other) { x -= other.x; y -= other.y; z -= other.z; return *this; }
    Vec3& operator*=(const Vec3& other) { x *= other.x; y *= other.y; z *= other.z; return *this; }
    Vec3& operator/=(const Vec3& other) { x /= other.x; y /= other.y; z /= other.z; return *this; }
    Vec3 operator*(float scalar) const { return { x * scalar, y * scalar, z * scalar }; }
    Vec3 operator/(float scalar) const { return { x / scalar, y / scalar, z / scalar }; }

    Vec3 min(const Vec3& other) const { return { std::fmin(x, other.x), std::fmin(y, other.y), std::fmin(z, other.z) }; }

    Vec3 max(const Vec3& other) const { return { std::fmax(x, other.x), std::fmax(y, other.y), std::fmax(z, other.z) }; }

    Vec3 clamp(const Vec3& minVal, const Vec3& maxVal) const {
        return { fmax(minVal.x, fmin(x, maxVal.x)), fmax(minVal.y, fmin(y, maxVal.y)), fmax(minVal.z, fmin(z, maxVal.z)) };
    }

    float dot(const Vec3& other) const { return x * other.x + y * other.y + z * other.z; }

    Vec3 cross(const Vec3& other) const { return { y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x }; }

    float length() const { return std::sqrt(x * x + y * y + z * z); }

    float distance(const Vec3& other) const { return (*this-other).length(); }

    Vec3 normalize() const {
        float len = length();
        return len != 0 ? (*this) / len : Vec3();
    }

    float angle(const Vec3& other) const {
        float dotProduct = dot(other);
        float lengths = length() * other.length();
        return lengths > 0 ? std::acos(dotProduct / lengths) * (180.0f / PI) : 0;
    }

    Vec3 rotate(float angle, const Vec3& axis) const {
        float rad = angle * (PI / 180.0f);
        float cosA = std::cos(rad);
        float sinA = std::sin(rad);
        return (*this) * cosA + axis.cross(*this) * sinA + axis * axis.dot(*this) * (1 - cosA);
    }

    void print() const { std::cout << "Vec3(" << x << ", " << y << ", " << z << ")\n" << std::endl;}
};

inline Vec3 operator*(float scalar, const Vec3& vec) { return vec * scalar; }

struct Vec4 {
    float x, y, z, w;

    Vec4() : x(0), y(0), z(0), w(0) {}
    Vec4(float value) : x(value), y(value), z(value), w(value) {}
    Vec4(int value) : x(static_cast<float>(value)), y(static_cast<float>(value)), z(static_cast<float>(value)), w(static_cast<float>(value)) {}
    Vec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
    Vec4(int x, int y, int z, int w) : x(static_cast<float>(x)), y(static_cast<float>(y)), z(static_cast<float>(z)), w(static_cast<float>(w)) {}
    Vec4(const Vec3& vec, float w) : x(vec.x), y(vec.y), z(vec.z), w(w) {}

    Vec4 operator+(const Vec4& other) const { return { x + other.x, y + other.y, z + other.z, w + other.w }; }
    Vec4 operator-(const Vec4& other) const { return { x - other.x, y - other.y, z - other.z, w - other.w }; }
    Vec4 operator*(const Vec4& other) const { return { x * other.x, y * other.y, z * other.z, w * other.w }; }
    Vec4 operator/(const Vec4& other) const { return { x / other.x, y / other.y, z / other.z, w / other.w }; }
    Vec4& operator+=(const Vec4& other) { x += other.x; y += other.y; z += other.z; w += other.w; return *this; }
    Vec4& operator-=(const Vec4& other) { x -= other.x; y -= other.y; z -= other.z; w -= other.w; return *this; }
    Vec4& operator*=(const Vec4& other) { x *= other.x; y *= other.y; z *= other.z; w *= other.w; return *this; }
    Vec4& operator/=(const Vec4& other) { x /= other.x; y /= other.y; z /= other.z; w /= other.w; return *this; }
    Vec4 operator*(float scalar) const { return { x * scalar, y * scalar, z * scalar, w * scalar }; }
    Vec4 operator/(float scalar) const { return { x / scalar, y / scalar, z / scalar, w / scalar }; }

    Vec4 min(const Vec4& other) const { return { std::fmin(x, other.x), std::fmin(y, other.y), std::fmin(z, other.z), std::fmin(w, other.w) }; }

    Vec4 max(const Vec4& other) const { return { std::fmax(x, other.x), std::fmax(y, other.y), std::fmax(z, other.z), std::fmax(w, other.w) }; }

    Vec4 clamp(const Vec4& minVal, const Vec4& maxVal) const {
        return { fmax(minVal.x, fmin(x, maxVal.x)), fmax(minVal.y, fmin(y, maxVal.y)), fmax(minVal.z, fmin(z, maxVal.z)), fmax(minVal.w, fmin(w, maxVal.w)) };
    }

    float dot(const Vec4& other) const { return x * other.x + y * other.y + z * other.z + w * other.w; }

    float length() const { return std::sqrt(x * x + y * y + z * z + w * w); }

    float distance(const Vec4& other) const { return (*this-other).length(); }

    Vec4 normalize() const {
        float len = length();
        return len != 0 ? (*this) / len : Vec4();
    }

    Vec3 toRGB() const { return Vec3(x, y, z); }

    float alpha() const { return w; }

    void print() const { std::cout << "Vec4(" << x << ", " << y << ", " << z << ", " << w << ")\n" << std::endl; }
};

inline Vec4 operator*(float scalar, const Vec4& vec) { return vec * scalar; }

struct Mat4 {
    float m[4][4];

    Mat4(){
        m[0][0] = 1; m[0][1] = 0; m[0][2] = 0; m[0][3] = 0;
        m[1][0] = 0; m[1][1] = 1; m[1][2] = 0; m[1][3] = 0;
        m[2][0] = 0; m[2][1] = 0; m[2][2] = 1; m[2][3] = 0;
        m[3][0] = 0; m[3][1] = 0; m[3][2] = 0; m[3][3] = 1;
    }

    static Mat4 identity(){
        return Mat4();
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

    static Mat4 rotationX(float angle){
        Mat4 result;
        float rad = angle * (PI / 180.0f);
        float cosA = std::cos(rad);
        float sinA = std::sin(rad);

        result.m[1][1] = cosA;
        result.m[1][2] = -sinA;
        result.m[2][1] = sinA;
        result.m[2][2] = cosA;

        return result;
    }

    static Mat4 rotationY(float angle){
        Mat4 result;
        float rad = angle * (PI / 180.0f);
        float cosA = std::cos(rad);
        float sinA = std::sin(rad);

        result.m[0][0] = cosA;
        result.m[0][2] = sinA;
        result.m[2][0] = -sinA;
        result.m[2][2] = cosA;

        return result;
    }

    static Mat4 rotationZ(float angle){
        Mat4 result;
        float rad = angle * (PI / 180.0f);
        float cosA = std::cos(rad);
        float sinA = std::sin(rad);

        result.m[0][0] = cosA;
        result.m[0][1] = -sinA;
        result.m[1][0] = sinA;
        result.m[1][1] = cosA;

        return result;
    }

    static Mat4 rotation(float angle, const Vec3& axis){
        Mat4 result;
        float rad = angle * (PI / 180.0f);
        float cosA = std::cos(rad);
        float sinA = std::sin(rad);
        float oneMinusCos = 1 - cosA;

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

    void print() const {
        std::cout << m[0][0] << " " << m[0][1] << " " << m[0][2] << " " << m[0][3] << "\n"
                  << m[1][0] << " " << m[1][1] << " " << m[1][2] << " " << m[1][3] << "\n"
                  << m[2][0] << " " << m[2][1] << " " << m[2][2] << " " << m[2][3] << "\n"
                  << m[3][0] << " " << m[3][1] << " " << m[3][2] << " " << m[3][3] << "\n";
    }
};