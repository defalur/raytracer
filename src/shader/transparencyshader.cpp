#include "transparencyshader.h"

#include <cmath>
#include <iostream>
#include <utils/utils.h>
#include <shader/shaderengine.h>

MatColor TransparencyShader::compute(HitContext c) const {
    if (c.hit().object->material(c.point()).transparent
        and c.refractDepth() < reflectionDepth)
    {
        //send ray at the refracted ray direction and return the resulting color
        //compute the refracted ray
        //we only compute the refracted ray here because it costs a lot and just a few
        //objects are transparent

        //cos of theta1
        auto costheta1 = Vector3::dot(c.inputRay(), -c.normal());
        //vector with a magnitude of sin theta1 and the correct direction
        auto vecsintheta1 = c.normal() * abs(costheta1) + c.inputRay();
        //compute n2 / n1 because sin theta2 = n2 / n1 * sin theta1
        auto kr = c.hit().object->material(c.point()).kr;
        //going out of the object
        if (costheta1 < 0.f)
        {
            kr = 1.f;
        }
        auto k = kr / c.inputRay().kr;
        auto vecsintheta2 = vecsintheta1 * k;
        auto costheta2 = std::sqrt(1 - vecsintheta2.sqMagnitude());

        //should not need normalization
        auto refractedRay = vecsintheta2 - c.normal() * costheta2;

        auto refractedHit = c.scene().raycast(Line3{c.point(), refractedRay});
        if (refractedHit.has_value())
        {
            auto context = HitContext{c.scene(), *refractedHit,
                                      Line3{c.point(), refractedRay, kr},
                                      c.engine(), c.depth(),
                                      c.refractDepth() + 1};
            auto color = c.engine().shade(context);

            return color;
        }

        return {0, 0, 0};
    }

    //if (c.depth() == reflectionDepth)
    //    return c.hit().object->texture(c.point());
    //else
        return {0, 0, 0};
}
