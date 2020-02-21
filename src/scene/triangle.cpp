#include <utils/utils.h>
#include "triangle.h"



Triangle::Triangle(Point3 a, Point3 b, Point3 c, TextureMaterial &mat)
    : a_{a}, b_{b}, c_{c}, mat_{mat}
{
    u_ = (b_ - a_).normalized();
    v_ = (c_ - a_).normalized();

    n_ = Vector3::cross(u_, v_).normalized();
}

std::vector<RaycastHit> Triangle::intersect(Line3 ray) {
    auto dot  = Vector3::dot(n_, ray.direction);
    if (floateq(dot, 0.f))//no intersection with the plane
    {
        return std::vector<RaycastHit>();
    }
    else
    {
        auto OA = a_ - ray.origin;
        auto k = Vector3::dot(n_, OA) / Vector3::dot(n_, ray.direction);
        auto point = ray.pointAt(k);

        auto cross1 = Vector3::cross(b_ - a_, point - a_);
        auto cross2 = Vector3::cross(c_ - b_, point - b_);
        auto cross3 = Vector3::cross(a_ - c_, point - c_);

        if (Vector3::dot(n_, cross1) < 0.f
        or Vector3::dot(n_, cross2) < 0.f
        or Vector3::dot(n_, cross3) < 0.f)
        {
            return std::vector<RaycastHit>();
        }
        return {RaycastHit{point, k, this}};
    }
}

Vector3 Triangle::normal(Point3 point, Vector3 ray) const {
    auto dot = Vector3::dot(n_, ray);
    if (dot < 0.0f)
        return n_;
    else
        return -n_;
}

MatColor Triangle::texture(Point3 point) const {
    return mat_.getColor(0.f, 0.f);
}

TextureMaterial::Material Triangle::material(Point3 point) const {
    return mat_.getMaterial(0.f, 0.f);
}

Point3 Triangle::position() const {
    return a_;//do that for now
}
