#ifndef RAYTRACER_HITCONTEXT_H
#define RAYTRACER_HITCONTEXT_H


#include <scene.h>

class ShaderEngine;

class HitContext {
public:
    HitContext(Scene &scene, RaycastHit hit, Line3 inputRay,
            ShaderEngine &engine, unsigned depth = 0, unsigned refractDepth = 0);

    std::vector<std::shared_ptr<Light>> lights() const;
    Scene& scene() const;
    Vector3 normal() const;
    Vector3 reflectedRay() const;
    Line3 inputRay() const;
    Point3 point() const;
    ShaderEngine& engine() const;
    unsigned depth() const;
    unsigned refractDepth() const;
    RaycastHit hit() const;

private:
    Scene &scene_;
    RaycastHit hit_;
    Vector3 normal_;
    Vector3 reflectedRay_;
    Line3 inputRay_;
    ShaderEngine &engine_;
    unsigned depth_;
    unsigned refractDepth_;
};


#endif //RAYTRACER_HITCONTEXT_H
