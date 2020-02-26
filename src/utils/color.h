#ifndef RAYTRACER_COLOR_H
#define RAYTRACER_COLOR_H

#include <cstdint>
#include <memory>

struct PixColor
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
};

struct MatColor
{
    float r;
    float g;
    float b;

    MatColor();
    MatColor(float r, float g, float b);
    MatColor(std::array<float, 3> color);

    MatColor operator*(float k) const;
    MatColor operator*(MatColor c) const;
    MatColor operator+(MatColor c) const;

    MatColor gamma(float gamma = 2.2f);

    PixColor toPixColor() const;
};

using RayColor = MatColor;

#endif //RAYTRACER_COLOR_H
