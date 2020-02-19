#ifndef RAYTRACER_SHADERENGINE_H
#define RAYTRACER_SHADERENGINE_H


#include <utils/color.h>
#include "hitcontext.h"
#include "shader.h"

class ShaderEngine {
public:
    MatColor shade(HitContext context);
    void addShader(std::shared_ptr<Shader> shader);
    void addLightShader(std::shared_ptr<LightShader> shader);

private:
    float projectShadow(Light& light, HitContext context) const;

    std::vector<std::shared_ptr<Shader>> shaders_;
    std::vector<std::shared_ptr<LightShader>> lightShaders_;
};


#endif //RAYTRACER_SHADERENGINE_H
