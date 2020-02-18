#include "shader.h"
#include "hitcontext.h"
#include <scene/sceneobject.h>
#include <scene.h>
#include <algorithm>
#include <cmath>
#include <utils/utils.h>

MatColor Shader::shade(RaycastHit hit, Scene& scene, Line3 ray, unsigned depth) {
    auto lights = scene.getLights();

    auto res = MatColor{0, 0, 0};

    auto point = hit.point;
    auto normal = hit.object->normal(point);

    for (auto& light : lights)
    {
        auto idotn = std::max(Vector3::dot(normal, -light->direction(point)), 0.f);
        float shadowCoef = projectShadow(*light, point, normal, scene);
        auto color = (hit.object->texture(point) * idotn
                * light->color() * light->intensity(point) * hit.object->material(point).kd
                + light->color() * specularity(*light, hit, normal, ray)) * shadowCoef;
        res = res + color;
    }

    res = res + reflection(hit, reflectRay(ray.direction, normal), normal, scene, depth);

    return res;
}

float Shader::projectShadow(Light& light, Point3 point, Vector3 normal, Scene& scene) {
    Line3 lightRay = {point, -light.direction(point)};
    auto hit = scene.raycast(lightRay, light.distance(point) + EPSILON);
    if (hit.has_value())
    {
        return 0.f;
    }

    return 1.f;
}

float Shader::specularity(Light &light, RaycastHit hit, Vector3 normal, Line3 ray)
{
    auto reflectDir = reflectRay(ray.direction, normal);

    auto mat = hit.object->material(hit.point);
    float dot = std::max(Vector3::dot(reflectDir, -light.direction(hit.point)), 0.f);
    float result = mat.ks * light.intensity(hit.point) *
            powf(dot, mat.ns);

    return std::max(result, 0.f);
}

Vector3 Shader::reflectRay(Vector3 rayDir, Vector3 normal)
{
    auto reflectRay = rayDir - normal * 2 * Vector3::dot(normal, rayDir);

    return reflectRay.normalized();
}

MatColor Shader::reflection(RaycastHit hit, Vector3 ray, Vector3 normal,
        Scene &scene, unsigned depth)
{
    if (depth == 0)
    {
        return {0, 0, 0};
    }

    auto reflectedRay = Line3{hit.point, ray};

    auto reflectHit = scene.raycast(reflectedRay);
    if (reflectHit.has_value())
    {
        auto color = shade(reflectHit.value(), scene, reflectedRay, depth - 1);
        return (color /** std::min((1.f / (hit.distance * hit.distance)), 1.f)*/)
               * hit.object->material(hit.point).ks;//does it need a falloff?
    }

    return {0, 0, 0};//return ambient light when implemented
}
