#ifndef RAYTRACER_COLOR_H
#define RAYTRACER_COLOR_H

#include <cstdint>

struct PixColor
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
};

struct RayColor
{
    float r;
    float g;
    float b;
};

#endif //RAYTRACER_COLOR_H
