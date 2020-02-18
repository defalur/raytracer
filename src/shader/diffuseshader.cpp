#include "diffuseshader.h"

MatColor DiffuseShader::compute(HitContext c, std::shared_ptr<Light> light) const {
    auto idotn = std::max(Vector3::dot(c.normal(),
            -light->direction(c.point())), 0.f);
    return c.hit().object->texture(c.point()) * c.hit().object->material(c.point()).kd
        * light->color() * light->intensity(c.point()) * idotn;
}
