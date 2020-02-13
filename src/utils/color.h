#ifndef RAYTRACER_COLOR_H
#define RAYTRACER_COLOR_H

#include <cstdint>

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

    MatColor operator*(float k) const;
    MatColor operator*(MatColor c) const;

    PixColor toPixColor() const;
};

using RayColor = MatColor;

#endif //RAYTRACER_COLOR_H
