#pragma once

#include <GLFW/glfw3.h>
#include <unordered_map>
#include "core/timestep.h"
#include "logging/logger.h"

struct inputState {
    bool isDown = false;  //is the key down
    bool wasDown = false; //was the key down last frame
    float duration = 0.0f; //amount of time key was held down
};

class input {
public:
    static void onKeyEvent(int keyCode, int action) {
        auto& state = _inputStates[keyCode];
        state.isDown = (action == GLFW_PRESS) || (action == GLFW_REPEAT);
    }

    static void onMouseButtonEvent(int button, int action) {
        auto& state = _inputStates[button];
        state.isDown = (action == GLFW_PRESS);
    }

    static void onMouseMoveEvent(float x, float y) {
        _mouseX = x;
        _mouseY = y;
    }

    static void onMouseWheelEvent(float wheel) {
        _mouseScroll = wheel;
    }

    static void update(timestep deltaTime) {
        for (auto& [keyCode, state] : _inputStates) {
            state.duration = state.isDown ? state.duration + static_cast<float>(deltaTime) : 0.0f;
            state.wasDown = state.isDown;
        }
        _mouseScroll = 0.0f; // Reset mouse scroll after processing
    }

    static bool getKey(int keyCode) {
        return _inputStates[keyCode].isDown;
    }

    static bool getKeyDown(int keyCode) {
        const auto& state = _inputStates[keyCode];
        return !state.wasDown && state.isDown; // key was not down last frame but is down now
    }

    static bool getKeyUp(int keyCode) {
        const auto& state = _inputStates[keyCode];
        return state.wasDown && !state.isDown; // key was down last frame but is not down now
    }

    static bool getMouse(int mouseCode) {
        return _inputStates[mouseCode].isDown;
    }

    static bool getMouseDown(int mouseCode) {
        const auto& state = _inputStates[mouseCode];
        return !state.wasDown && state.isDown; // mouse button was not down last frame but is down now
    }

    static bool getMouseUp(int mouseCode) {
        const auto& state = _inputStates[mouseCode];
        return state.wasDown && !state.isDown; // mouse button was down last frame but is not down now
    }

    static vec2 getMousePosition() {
        return { _mouseX, _mouseY };
    }

    static float getMouseScroll() {
        return _mouseScroll;
    }

    static float getDuration(int code) {
        return _inputStates[code].duration;
    }

private:
    static inline std::unordered_map<int, inputState> _inputStates;
    static inline float _mouseX = 0.0f;
    static inline float _mouseY = 0.0f;
    static inline float _mouseScroll = 0.0f;
    static inline logger _log;
};