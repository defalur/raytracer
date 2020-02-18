#ifndef RAYTRACER_REFLECTIONSHADER_H
#define RAYTRACER_REFLECTIONSHADER_H


#include "shader.h"

class ReflectionShader : public Shader {
public:
    MatColor compute(HitContext context) const override;
};


#endif //RAYTRACER_REFLECTIONSHADER_H
