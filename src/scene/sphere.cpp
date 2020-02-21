#include <utils/utils.h>
#include <vector>
#include "sphere.h"


Sphere::Sphere(Point3 center, float radius, TextureMaterial &mat)
    : center(center), radius(radius), mat(mat)
{

}

std::vector<RaycastHit> Sphere::intersect(Line3 ray)
{
    auto rsquare = radius * radius;
    auto oc = ray.origin - center;
    auto b = 2 * Vector3::dot(ray.direction, oc);
    auto c = oc.sqMagnitude() - rsquare;
    auto delta = b * b - 4 * c;//no a because direction is a unit vector
    if (delta < 0.f)
        return std::vector<RaycastHit>();//no points

    auto d = -Vector3::dot(ray.direction, oc);
    if (floateq(delta, 0))
    {
        auto hit = RaycastHit{ray.pointAt(d), d, this};
        return {hit};
    }
    else
    {
        auto ldotoc = Vector3::dot(ray.direction, oc);
        auto delta2 = sqrtf(ldotoc * ldotoc - (oc.sqMagnitude() - rsquare));
        auto d1 = d - delta2;
        auto d2 = d + delta2;

        auto hit1 = RaycastHit{ray.pointAt(d1), d1, this};
        auto hit2 = RaycastHit{ray.pointAt(d2), d2, this};

        return {hit1, hit2};
    }
}

Vector3 Sphere::normal(Point3 point, Vector3) const
{
    return (point - center).normalized();
}

MatColor Sphere::texture(Point3 point) const
{
    return mat.getColor(0.f, 0.f);//simple solutions for the start
}

TextureMaterial::Material Sphere::material(Point3 point) const
{
    return mat.getMaterial(0.f, 0.f);
}

Point3 Sphere::position() const
{
    return center;
}

