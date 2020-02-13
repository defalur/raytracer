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
        std::array<float, 4> vec{};
    };

    Vector4();
    Vector4(float x, float y, float z, float w);
    Vector4(float x, float y, float z);
    explicit Vector4(std::array<float, 4> vec);

    Vector4 operator*(const float &k) const;
    Vector4 operator+(const Vector4 &v) const;
    //Vector4 operator-() const;
    Vector4 operator-(const Vector4 &v) const;

    [[nodiscard]] Vector4 euclid() const;

    [[nodiscard]] float dot(const Vector4 &v) const;
    //is the cross product possible? Do I use it on 3 vector4 or 2 vector3?
    //if using 3 vector4, what kind of object is the result?
    //friend Vector4 cross(Vector4 v, Vector4 w, Vector4 t);

    friend std::ostream&operator<<(std::ostream &out, Vector4 &v);
};

//Vector4 cross(Vector4 v, Vector4 w, Vector4 t);
std::ostream&operator<<(std::ostream &out, Vector4 &v);

using Point4 = Vector4;

#endif //RAYTRACER_VECTOR4_H
