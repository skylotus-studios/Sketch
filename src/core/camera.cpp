#include "camera.h"

camera::camera(vec3 position, float yaw, float pitch) : _position(position), _yaw(yaw), _pitch(pitch) {
    updateCameraVectors();
}

void camera::updateCameraVectors() {
    // Calculate the forward vector
    _forward.x = std::cos(radians(_yaw)) * std::cos(radians(_pitch));
    _forward.y = std::sin(radians(_pitch));
    _forward.z = std::sin(radians(_yaw)) * std::cos(radians(_pitch));
    _forward = _forward.normalize();
    
    // Calculate the right vector
    _right = _forward.cross(vec3::up()).normalize();
}

void camera::update(timestep deltaTime) {
    float velocity = _movementSpeed * (float)deltaTime;
    _log.info("Camera position: {}", _position.toString());
    _log.info("Camera look at: {}", (_position + _forward).toString());
    
    // Forward/backward movement (W/S)
    if (input::getKey(key.w)) {
        _position += _forward * velocity;
    }
    if (input::getKey(key.s)) {
        _position -= _forward * velocity;
    }
    
    // Left/right movement (A/D)
    if (input::getKey(key.a)) {
        _position -= _right * velocity;
    }
    if (input::getKey(key.d)) {
        _position += _right * velocity;
    }

    // Mouse look
    if(input::getMouse(mouse.right)) {
        const vec2 mousePos = input::getMousePosition();
        // Convert screen coordinates to normalized coordinates (-1 to 1)
        const float normalizedX = (mousePos.x / 1920.0f) * 2.0f - 1.0f;
        const float normalizedY = (mousePos.y / 1080.0f) * 2.0f - 1.0f;
        
        _yaw += normalizedX * _sensitivity * (float)deltaTime;
        _pitch -= normalizedY * _sensitivity * (float)deltaTime;
        
        // Clamp pitch to prevent gimbal lock
        if (_pitch > 89.0f) _pitch = 89.0f;
        if (_pitch < -89.0f) _pitch = -89.0f;
        
        updateCameraVectors();
    }
}