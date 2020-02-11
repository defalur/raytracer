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

    Vector4();
    Vector4(float x, float y, float z, float w);
    explicit Vector4(std::array<float, 4> vec);

    Vector4 operator*(const float &k) const;
    Vector4 operator+(const Vector4 &v) const;
    Vector4 operator-() const;
    Vector4 operator-(const Vector4 &v) const;

    float dot(const Vector4 &v) const;
};

using Point4 = Vector4;

#endif //RAYTRACER_VECTOR4_H
