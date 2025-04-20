#pragma once

class timestep {
public:
    timestep(float deltaTime = 0.0f) : _deltaTime(deltaTime) {}
    explicit operator float() const { return _deltaTime; } // Implicit conversion to float
private:
    float _deltaTime = 0.0f; // Time since last frame
};

template <>
struct std::formatter<timestep> : std::formatter<float> {
    auto format(const timestep& t, format_context& ctx) const {
        return formatter<float>::format(static_cast<float>(t), ctx);
    }
};