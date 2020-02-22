#ifndef RAYTRACER_TRANSPARENCYSHADER_H
#define RAYTRACER_TRANSPARENCYSHADER_H


#include "shader.h"

class TransparencyShader : public Shader {
public:
    MatColor compute(HitContext context) const override;
};


#endif //RAYTRACER_TRANSPARENCYSHADER_H
