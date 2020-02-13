#include "pointlight.h"

MatColor PointLight::color() const
{
    return color_;
}

float PointLight::intensity(Point3 point) const
{
    return strength_ / (position_ - point).sqMagnitude();
}

Vector3 PointLight::direction(Point3 point) const
{
    return (point - position_).normalized();
}
