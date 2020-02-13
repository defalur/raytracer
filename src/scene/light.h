#ifndef RAYTRACER_LIGHT_H
#define RAYTRACER_LIGHT_H


#include <utils/vector3.h>
#include <utils/color.h>

class Light
{
public:
    virtual MatColor color() const = 0;
    virtual float intensity(Point3 point) const = 0;
    virtual Vector3 direction(Point3 point) const = 0;
};


#endif //RAYTRACER_LIGHT_H
