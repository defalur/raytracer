#ifndef RAYTRACER_RAYCASTHIT_H
#define RAYTRACER_RAYCASTHIT_H

#include "vector3.h"

class SceneObject;

struct RaycastHit
{
    Point3 point;
    float distance;

    SceneObject *object;
};

#endif //RAYTRACER_RAYCASTHIT_H
