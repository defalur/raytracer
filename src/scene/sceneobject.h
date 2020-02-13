#ifndef RAYTRACER_SCENEOBJECT_H
#define RAYTRACER_SCENEOBJECT_H

#include <optional>

#include "utils/vector3.h"
#include "utils/color.h"
#include "texturematerial.h"

class SceneObject
{
    virtual std::vector<Point3> intersect(Line3 ray) const = 0;
    virtual Vector3 normal(Point3 point) const = 0;
    virtual MatColor texture(Point3 point) const = 0;
    virtual TextureMaterial::Material material(Point3 point) const = 0;
};


#endif //RAYTRACER_SCENEOBJECT_H
