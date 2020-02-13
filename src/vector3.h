#ifndef RAYTRACER_VECTOR3_H
#define RAYTRACER_VECTOR3_H

#include <array>

struct Vector3 {
    union{
        struct {
            float x;
            float y;
            float z;
        };
        std::array<float, 3> vec;
    };

    Vector3();
    Vector3(float x, float y, float z);
    explicit Vector3(std::array<float, 3> vec);

    Vector3 operator*(const float &k) const;
    Vector3 operator+(const Vector3 &v) const;
    Vector3 operator-() const;
    Vector3 operator-(const Vector3 &v) const;

    [[nodiscard]] float dot(const Vector3 &v) const;
    [[nodiscard]] Vector3 cross(const Vector3 &v) const;

    friend std::ostream&operator<<(std::ostream &out, Vector3 &v);
};

std::ostream& operator<<(std::ostream &out, Vector3 &v);

using Point3 = Vector3;

#endif //RAYTRACER_VECTOR3_H
