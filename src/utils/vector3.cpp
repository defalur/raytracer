#include <cmath>

#include <iostream>
#include <cmath>

#include "vector3.h"

Vector3::Vector3()
{
    x = 0.0f;
    y = 0.0f;
    z = 0.0f;
}

Vector3::Vector3(float x, float y, float z)
    : x(x), y(y), z(z)
{
}

Vector3::Vector3(std::array<float, 3> vec)
    : x(vec[0]), y(vec[1]), z(vec[2])
{
}

Vector3 Vector3::operator*(const float &k) const
{
    return Vector3(x * k, y * k, z * k);
}

Vector3 Vector3::operator+(const Vector3 &v) const
{
    return Vector3(x + v.x, y + v.y, z + v.z);
}

Vector3 Vector3::operator-() const
{
    return Vector3(-x, -y, -z);
}

Vector3 Vector3::operator-(const Vector3 &v) const
{
    return Vector3(x - v.x, y - v.y, z - v.z);
}

std::ostream &operator<<(std::ostream &out, Vector3 &v)
{
    out << '(' << v.x << ", " << v.y << ", " << v.z << ')';
    return out;
}

float Vector3::magnitude() const
{
    return std::sqrt(sqMagnitude());
}

Vector3 Vector3::normalized() const
{
    float mag = magnitude();
    return Vector3(x / mag, y / mag, z / mag);
}

float Vector3::sqMagnitude() const
{
    return dot(*this, *this);
}

float Vector3::dot(const Vector3 &u, const Vector3 &v)
{
    return u.x * v.x + u.y * v.y + u.z * v.z;
}

Vector3 Vector3::cross(const Vector3 &u, const Vector3 &v)
{
    return Vector3(u.y * v.z - u.z * v.y,
                   u.z * v.x - u.x * v.z,
                   u.x * v.y - u.y * v.x);
}

Point3 Line3::pointAt(float d) const
{
    return origin + d * direction;
}
