#ifndef RAYTRACER_DIFFUSESHADER_H
#define RAYTRACER_DIFFUSESHADER_H


#include "shader.h"

class DiffuseShader : public LightShader {
public:
    MatColor compute(HitContext context, std::shared_ptr<Light> light) const override;
};


#endif //RAYTRACER_DIFFUSESHADER_H
