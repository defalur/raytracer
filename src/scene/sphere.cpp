#include <utils/utils.h>
#include <vector>
#include "sphere.h"

std::vector<Point3> Sphere::intersect(Line3 ray) const
{
    auto rsquare = radius * radius;
    auto oc = ray.origin - center;
    auto b = 2 * Vector3::dot(ray.direction, oc);
    auto c = oc.sqMagnitude() * rsquare;
    auto delta = b * b - 4 * c;//no a because direction is a unit vector
    if (delta < 0.f)
        return std::vector<Point3>();//no points

    auto d = -Vector3::dot(ray.direction, oc);
    if (floateq(delta, 0))
    {
        return {ray.pointAt(d)};
    }
    else
    {
        auto ldotoc = Vector3::dot(ray.direction, oc);
        auto delta2 = sqrtf(ldotoc * ldotoc - (oc.sqMagnitude() - rsquare));
        auto d1 = d - delta2;
        auto d2 = d + delta2;

        if (d1 < d2)
        {
            return {ray.pointAt(d1), ray.pointAt(d2)};
        }
        else
            {
            return {ray.pointAt(d2), ray.pointAt(d2)};
        }
    }
}

Vector3 Sphere::normal(Point3 point) const
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
