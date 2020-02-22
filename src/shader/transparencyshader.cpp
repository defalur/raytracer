#include "transparencyshader.h"

MatColor TransparencyShader::compute(HitContext c) const {
    if (c.hit().object->material(c.point()).transparent)
    {
        //send ray at the refracted ray direction and return the resulting color
        //compute the refracted ray

    }
}
