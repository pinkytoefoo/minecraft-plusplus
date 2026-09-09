#pragma once

struct Timestep
{
    float Time = 0.0f;
    operator float() const { return Time; }
};