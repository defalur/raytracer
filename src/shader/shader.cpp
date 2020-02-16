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
        float shadowCoef = projectShadow(*light, point, scene);
        auto color = hit.object->texture(point) * idotn
                * light->color() * light->intensity(point) * shadowCoef;
        res = res + color;
    }

    return res.toPixColor();
}

float Shader::projectShadow(Light& light, Point3 point, Scene& scene) {
    Line3 lightRay = {light.point, light.direction(point)};
    auto hit = scene.raycast(lightRay);
    if (hit.has_value())
    {
        return hit->point == point ? 1.0f : 0.f;
    }

    return 1.f;
}
