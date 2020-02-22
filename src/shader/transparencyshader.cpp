#include "transparencyshader.h"

#include <cmath>
#include <iostream>
#include <utils/utils.h>
#include <shader/shaderengine.h>
#include <utils/vector3.h>

MatColor TransparencyShader::compute(HitContext c) const {
    if (c.hit().object->material(c.point()).transparent
        and c.refractDepth() < reflectionDepth)
    {
        //send ray at the refracted ray direction and return the resulting color
        //compute the refracted ray
        //we only compute the refracted ray here because it costs a lot and just a few
        //objects are transparent

        //cos of theta1
        auto costheta1 = Vector3::dot(c.inputRay(), c.normal());
        //vector with a magnitude of sin theta1 and the correct direction
        auto vecsintheta1 = c.normal() * abs(costheta1) + c.inputRay();
        //compute n2 / n1 because sin theta2 = n2 / n1 * sin theta1
        auto kr1 = 1.f;
        auto kr2 = c.hit().object->material(c.point()).kr;
        auto normal = c.normal();
        if (costheta1 < 0.f)
        {
            //going inside the object
            costheta1 = -costheta1;
        }
        else
        {
            //going out of the object
            std::swap(kr1, kr2);
            normal = -normal;
        }
        auto nr = kr1 / kr2;
        auto k = 1 - nr * nr * (1 - costheta1 * costheta1);
        if (k < 0)
        {
            return c.hit().object->texture(c.point());
        }

        //should not need normalization
        auto refractedRay = c.inputRay().direction * nr + normal *(nr * costheta1 - sqrtf(k));

        std::cout << "Ray: " << c.inputRay().direction << " Out: " << refractedRay
            << " Normal: " << c.normal() << "\n";

        auto refractedHit = c.scene().raycast(Line3{c.point(), refractedRay});
        if (refractedHit.has_value())
        {
            auto context = HitContext{c.scene(), *refractedHit,
                                      Line3{c.point(), refractedRay, kr2},
                                      c.engine(), c.depth(),
                                      c.refractDepth() + 1};
            auto color = c.engine().shade(context);

            return color;
        }

        return {0, 0, 0};
    }

    if (c.refractDepth() == reflectionDepth)
        return c.hit().object->texture(c.point());
    else
        return {0, 0, 0};
}
