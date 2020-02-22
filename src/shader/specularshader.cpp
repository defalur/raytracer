#include <cmath>
#include "specularshader.h"

MatColor SpecularShader::compute(HitContext c, std::shared_ptr<Light> light) const {
    auto mat = c.hit().object->material(c.point());
    float dot = std::max(Vector3::dot(c.reflectedRay(), -light->direction(c.point())), 0.f);

    float specularity = /*std::max(*/mat.ks * light->intensity(c.point())
            * powf(dot, mat.ns);//, 0.f);

    return light->color() * specularity;
}
