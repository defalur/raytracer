#ifndef RAYTRACER_SHADERENGINE_H
#define RAYTRACER_SHADERENGINE_H


#include <utils/color.h>
#include "hitcontext.h"
#include "shader.h"

class ShaderEngine {
public:
    MatColor shade(HitContext context);
    void addShader(Shader shader);
    void addLightShader(LightShader shader);

private:
    float projectShadow(Light& light, HitContext context) const;

    std::vector<Shader> shaders_;
    std::vector<LightShader> lightShaders_;
};


#endif //RAYTRACER_SHADERENGINE_H
