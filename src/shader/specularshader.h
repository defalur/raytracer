#ifndef RAYTRACER_SPECULARSHADER_H
#define RAYTRACER_SPECULARSHADER_H


#include "shader.h"

class SpecularShader : public LightShader {
public:
    MatColor compute(HitContext context, std::shared_ptr<Light> light) const override;
};


#endif //RAYTRACER_SPECULARSHADER_H
