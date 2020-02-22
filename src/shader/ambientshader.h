#ifndef RAYTRACER_AMBIENTSHADER_H
#define RAYTRACER_AMBIENTSHADER_H


#include "shader.h"

class AmbientShader : public Shader {
public:
    AmbientShader(MatColor color);

    MatColor compute(HitContext context) const override;

private:
    MatColor color_;
};


#endif //RAYTRACER_AMBIENTSHADER_H
