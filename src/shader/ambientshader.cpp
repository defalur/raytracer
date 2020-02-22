#include "ambientshader.h"


AmbientShader::AmbientShader(MatColor color)
    : color_{color}
{
}

MatColor AmbientShader::compute(HitContext context) const {
    return color_ * context.hit().object->texture(context.point()) *
        context.hit().object->material(context.point()).kd;
}

