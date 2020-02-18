#include "reflectionshader.h"

MatColor ReflectionShader::compute(HitContext c) const {
    if (c.depth() == 0)
    {
        return {0, 0, 0};
    }

    auto reflectedRay = Line3{c.point(), c.reflectedRay()};

    auto reflectHit = c.scene().raycast(reflectedRay);
    if (reflectHit.has_value())
    {
        auto context = HitContext{c.scene(), *reflectHit, reflectedRay.direction,
                                  c.engine(), c.depth() - 1};
        auto color = c.engine().shade(context);

        return color * c.hit().object->material(c.point()).ks;
    }

    return {0, 0, 0};
}
