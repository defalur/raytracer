#ifndef RAYTRACER_UTILS_H
#define RAYTRACER_UTILS_H

#include <cmath>

#define EQEPSILON 0.0001

bool floateq(float a, float b)
{
    return std::abs(a - b) < EQEPSILON;
}

#endif //RAYTRACER_UTILS_H
