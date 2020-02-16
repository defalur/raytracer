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
        auto normal = hit.object->normal(point);
        auto idotn = std::max(Vector3::dot(normal, -light->direction(point)), 0.f);
        float shadowCoef = projectShadow(*light, point, normal, scene);
        auto color = hit.object->texture(point) * idotn
                * light->color() * light->intensity(point) * shadowCoef;
        res = res + color;
    }

    return res.toPixColor();
}

float Shader::projectShadow(Light& light, Point3 point, Vector3 normal, Scene& scene) {
    Line3 lightRay = {point + normal * 0.0001f, -light.direction(point)};
    auto hit = scene.raycast(lightRay, light.distance(point) + 0.001f);
    if (hit.has_value())
    {
        return 0.f;
    }

    return 1.f;
}
