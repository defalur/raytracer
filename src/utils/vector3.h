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
    explicit Vector3(std::array<float, 3U> vec);

    Vector3 operator*(const float &k) const;
    Vector3 operator+(const Vector3 &v) const;
    Vector3 operator-() const;
    Vector3 operator-(const Vector3 &v) const;

    bool operator==(const Vector3& v) const;

    static float dot(const Vector3 &u, const Vector3 &v);
    static Vector3 cross(const Vector3 &u, const Vector3 &v);

    float sqMagnitude() const;
    float magnitude() const;
    Vector3 normalized() const;

    friend std::ostream&operator<<(std::ostream &out, Vector3 &v);
};

std::ostream& operator<<(std::ostream &out, Vector3 &v);

using Point3 = Vector3;

struct Line3
{
    Point3 origin;
    Vector3 direction;
    float kr = 1.f;//refraction index of current medium

    Point3 pointAt(float d) const;

    //used by hitcontext to provide either a Vector3 or a Line3 for getinputray
    operator Vector3() const
    {
        return direction;
    }
};

#endif //RAYTRACER_VECTOR3_H
