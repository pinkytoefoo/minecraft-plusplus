#pragma once

class Timestep {
public:
    Timestep(float time = 0.0f) : time_(time) {}

    float GetSeconds() const { return time_; }
    float GetMilliseconds() const { return time_ * 1000.0f; }

    operator float() const { return time_; }

private:
    float time_;
};
