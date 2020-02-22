#include "hitcontext.h"
#include "shaderengine.h"

HitContext::HitContext(Scene &scene, RaycastHit hit, Line3 inputRay,
        ShaderEngine &engine, unsigned depth, unsigned refractDepth)
    : scene_{scene}, hit_{hit}, inputRay_{inputRay}, engine_{engine}, depth_{depth},
    refractDepth_{refractDepth}
{
    normal_ = hit.object->normal(hit.point, inputRay);

    reflectedRay_ = inputRay.direction - normal_ * 2 * Vector3::dot(normal_, inputRay);
}

std::vector<std::shared_ptr<Light>> HitContext::lights() const {
    return scene_.getLights();
}

Scene &HitContext::scene() const {
    return scene_;
}

Vector3 HitContext::normal() const {
    return normal_;
}

Vector3 HitContext::reflectedRay() const {
    return reflectedRay_;
}

Line3 HitContext::inputRay() const {
    return inputRay_;
}

Point3 HitContext::point() const {
    return hit_.point;
}

ShaderEngine &HitContext::engine() const {
    return engine_;
}

unsigned HitContext::depth() const {
    return depth_;
}

RaycastHit HitContext::hit() const {
    return hit_;
}

unsigned HitContext::refractDepth() const
{
    return refractDepth_;
}
