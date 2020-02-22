#include <utils/utils.h>
#include "shaderengine.h"

MatColor ShaderEngine::shade(HitContext context)
{
    auto res = MatColor{0, 0, 0};

    for (auto& light : context.lights())
    {
        auto color = MatColor{0, 0, 0};
        for (auto shader : lightShaders_)
        {
            color = color + shader->compute(context, light);
        }
        color = color * projectShadow(*light, context);

        res = res + color;
    }

    for (auto shader : shaders_)
    {
        res = res + shader->compute(context);
    }

    return res;
}

float ShaderEngine::projectShadow(Light& light, HitContext c) const {
    Line3 lightRay = {c.point(), -light.direction(c.point())};
    auto hit = c.scene().raycast(lightRay, light.distance(c.point()) + EPSILON);
    if (hit.has_value())
    {
        if (hit->object->material(hit->point).transparent)
        {
            return 0.5f;
        }
        return 0.f;
    }

    return 1.f;
}

void ShaderEngine::addShader(std::shared_ptr<Shader> shader) {
    shaders_.push_back(shader);
}

void ShaderEngine::addLightShader(std::shared_ptr<LightShader> shader) {
    lightShaders_.push_back(shader);
}
