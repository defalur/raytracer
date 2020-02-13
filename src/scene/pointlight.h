#ifndef RAYTRACER_POINTLIGHT_H
#define RAYTRACER_POINTLIGHT_H


#include <utils/color.h>
#include "light.h"

class PointLight : public Light
{
public:
    MatColor color() const override;
    float intensity(Point3 point) const override;
    Vector3 direction(Point3 point) const override;

private:
    float strength_;
    MatColor color_;
    Point3 position_;
};


#endif //RAYTRACER_POINTLIGHT_H
