#include "shader.h"
#include <scene/sceneobject.h>
#include <scene.h>
#include <algorithm>

PixColor Shader::shade(RaycastHit hit, Scene& scene) {
    auto lights = scene.getLights();

    auto res = MatColor{0, 0, 0};

    for (auto& light : lights)
    {
        auto point = hit.point;
        auto idotn = std::max(Vector3::dot(hit.object->normal(point), -light->direction(point)), 0.f);
        auto color = hit.object->texture(point) * idotn * light->color() * light->intensity(point);
        res = res + color;
    }

    return res.toPixColor();
}
