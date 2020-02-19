#ifndef RAYTRACER_HITCONTEXT_H
#define RAYTRACER_HITCONTEXT_H


#include <scene.h>

class ShaderEngine;

class HitContext {
public:
    HitContext(Scene &scene, RaycastHit hit, Vector3 inputRay,
            ShaderEngine &engine, unsigned depth = 5);

    std::vector<std::shared_ptr<Light>> lights() const;
    Scene& scene() const;
    Vector3 normal() const;
    Vector3 reflectedRay() const;
    Vector3 inputRay() const;
    Point3 point() const;
    ShaderEngine& engine() const;
    unsigned depth() const;
    RaycastHit hit() const;

private:
    Scene &scene_;
    RaycastHit hit_;
    Vector3 normal_;
    Vector3 reflectedRay_;
    Vector3 inputRay_;
    ShaderEngine &engine_;
    unsigned depth_;
};


#endif //RAYTRACER_HITCONTEXT_H
