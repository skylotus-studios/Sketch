#include "camera.h"

camera::camera(vec3 position, float yaw, float pitch) : _position(position), _yaw(yaw), _pitch(pitch) {
    updateCameraVectors();
}

void camera::updateCameraVectors() {
    // Calculate the new forward vector
    _forward.x = std::cos(radians(_yaw)) * std::cos(radians(_pitch));
    _forward.y = std::sin(radians(_pitch));
    _forward.z = std::sin(radians(_yaw)) * std::cos(radians(_pitch));
    _forward = _forward.normalize();
    _right = _forward.cross(vec3::up()).normalize();
}

void camera::update(timestep deltaTime) {
    float velocity = _movementSpeed * (float)deltaTime;
    _log.info("Camera position: {}", _position.toString());
    _log.info("Camera look at: {}", (_position + _forward).toString());
    if (input::getKey(key.w)) _position += _forward * velocity;
    if (input::getKey(key.s)) _position -= _forward * velocity;
    if (input::getKey(key.a)) _position -= _right * velocity;
    if (input::getKey(key.d)) _position += _right * velocity;

    if(input::getMouse(mouse.right)) {
        const vec2 mousePos = input::getMousePosition();
        _yaw += mousePos.x * _sensitivity * (float)deltaTime;
        _pitch -= mousePos.y * _sensitivity * (float)deltaTime;
        if (_pitch > 89.0f) _pitch = 89.0f;
        if (_pitch < -89.0f) _pitch = -89.0f;
        updateCameraVectors();
    }
}