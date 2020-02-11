#include <iostream>

#include "vector3.h"

Vector3::Vector3() {
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

Vector3 Vector3::operator*(const float &k) const {
    return Vector3(x * k, y * k, z * k);
}

Vector3 Vector3::operator+(const Vector3 &v) const {
    return Vector3(x + v.x, y + v.y, z + v.z);
}

Vector3 Vector3::operator-() const {
    return Vector3(-x, -y, -z);
}

Vector3 Vector3::operator-(const Vector3 &v) const {
    return Vector3(x - v.x, y - v.y, z - v.z);
}

float Vector3::dot(const Vector3 &v) const {
    return x * v.x + y * v.y + z * v.z;
}

Vector3 Vector3::cross(const Vector3 &v) const {
    return Vector3(y * v.z - z * v.y,
                   z * v.x - x * v.z,
                   x * v.y - y * v.x);
}

std::ostream &operator<<(std::ostream &out, Vector3 &v) {
    out << '(' << v.x << ", " << v.y << ", " << v.z << ')';
    return out;
}
