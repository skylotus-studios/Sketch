#pragma once
#include "logging/logger.h"
#include "math/math.h"
#include "input/input.h"
#include "input/keycodes.h"
#include "input/mousecodes.h"
#include "core/timestep.h"

class camera {
public:
    camera(vec3 position = {0,0,3}, float yaw = -90.0f, float pitch = 0.0f);
    ~camera(){};
    void update(timestep deltaTime);
    vec3 getPos() const { return _position; }
    vec3 getForward() const { return _forward; }
    vec3 getRight() const { return _right; }
    mat4 getView() const { return mat4::lookAt(_position, _position + _forward);}
private:
    void updateCameraVectors();
    static float radians(float degrees) {
        return degrees * (PI / 180.0f);
    }
    vec3 _position;
    vec3 _forward;
    vec3 _right;

    float _yaw;
    float _pitch;
    float _movementSpeed = 5.0f;
    float _sensitivity = 45.0f;
    static constexpr double PI = 3.14159265358979323846f;
    static inline logger _log;
};
