#ifndef RAYTRACER_SCENEOBJECT_H
#define RAYTRACER_SCENEOBJECT_H

#include <optional>
#include <vector>
#include <utils/raycastHit.h>

#include "utils/vector3.h"
#include "utils/color.h"
#include "materials/texturematerial.h"

class SceneObject
{
public:
    virtual std::vector<RaycastHit> intersect(Line3 ray) = 0;
    virtual Vector3 normal(Point3 point) const = 0;
    virtual MatColor texture(Point3 point) const = 0;
    virtual TextureMaterial::Material material(Point3 point) const = 0;
    virtual Point3 position() const = 0;
};


#endif //RAYTRACER_SCENEOBJECT_H
