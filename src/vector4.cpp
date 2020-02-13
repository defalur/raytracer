#include <iostream>

#include "vector4.h"

#include "vector3.h"

Vector4::Vector4()
    : x(0), y(0), z(0), w(1)
{
}

Vector4::Vector4(float x, float y, float z, float w)
{
    if (x == 0 and y == 0 and z == 0 and w == 0)
        throw std::invalid_argument("Vector cannot be 0");
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
}

Vector4::Vector4(float x, float y, float z)
    : x(x), y(y), z(z), w(1)
{

}

Vector4::Vector4(std::array<float, 4> vec)
    : Vector4(vec[0], vec[1], vec[2], vec[3])
{
}

Vector4 Vector4::operator*(const float &k) const {
    return Vector4(x * k, y * k, z * k, w * k);
}

Vector4 Vector4::operator+(const Vector4 &v) const {
    return Vector4(x + v.x, y + v.y, z + v.z, w + v.w);
}

Vector4 Vector4::operator-(const Vector4 &v) const {
    return Vector4(x - v.x, y - v.y, z - v.z, w - v.w);
}

float Vector4::dot(const Vector4 &v) const {
    return x * v.x + y * v.y + z * v.z + w * v.w;
}

/*Vector4 cross(Vector4 v, Vector4 w, Vector4 t)
{
    return Vector4(
            Vector3(w.y, w.z, w.w).cross(Vector3(t.y, t.z, t.w)).dot(Vector3(v.y, v.z, v.w)),
            Vector3(w.x, w.z, w.w).cross(Vector3(t.x, t.z, t.w)).dot(Vector3(v.x, v.z, v.w)),
            Vector3(w.x, w.y, w.w).cross(Vector3(t.x, t.y, t.w)).dot(Vector3(v.x, v.y, v.w)),
            Vector3(w.x, w.y, w.z).cross(Vector3(t.x, t.y, t.z)).dot(Vector3(v.x, v.y, v.z)));
}*/

std::ostream &operator<<(std::ostream &out, Vector4 &v) {
    out << '(' << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ')';
    return out;
}

Vector4 Vector4::euclid() const {
    if (w != 0)
        return Vector4(x / w, y / w, z / w, 1);
    return Vector4(x, y, z, w);
}
