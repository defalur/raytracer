#ifndef RAYTRACER_SPHERE_H
#define RAYTRACER_SPHERE_H


#include "sceneobject.h"

class Sphere : public SceneObject
{
public:
    std::vector<RaycastHit> intersect(Line3 ray) override;
    Vector3 normal(Point3 point) const override;
    MatColor texture(Point3 point) const override;
    TextureMaterial::Material material(Point3 point) const override;

private:
    Point3 center;
    float radius;

    TextureMaterial &mat;
};


#endif //RAYTRACER_SPHERE_H
