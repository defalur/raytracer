#ifndef RAYTRACER_VECTOR4_H
#define RAYTRACER_VECTOR4_H

#include <array>

struct Vector4 {
    union{
        struct {
            float x;
            float y;
            float z;
            float w;
        };
        std::array<float, 4> vec;
    };
};

using Point4 = Vector4;

#endif //RAYTRACER_VECTOR4_H
