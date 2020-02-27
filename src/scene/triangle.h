#ifndef RAYTRACER_TRIANGLE_H
#define RAYTRACER_TRIANGLE_H


#include <utils/vector3.h>
#include <utils/raycastHit.h>
#include <vector>
#include <scene/sceneobject.h>

class Triangle : public SceneObject {
public:
    Triangle(Point3 a, Point3 b, Point3 c, std::shared_ptr<TextureMaterial> mat);

    std::vector<RaycastHit> intersect(Line3 ray) override;
    Vector3 normal(Point3 point, Vector3 ray) const override;
    MatColor texture(Point3 point) const override;
    TextureMaterial::Material material(Point3 point) const override;
    Point3 position() const override;

private:
    Point3 a_;
    Point3 b_;
    Point3 c_;

    Vector3 n_;
    Vector3 u_;
    Vector3 v_;

    std::shared_ptr<TextureMaterial> mat_;
};


#endif //RAYTRACER_TRIANGLE_H
