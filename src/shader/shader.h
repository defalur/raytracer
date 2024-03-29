#ifndef RAYTRACER_SHADER_H
#define RAYTRACER_SHADER_H


#include <utils/color.h>
#include <utils/raycastHit.h>
#include <scene.h>
#include "hitcontext.h"

class Shader {
public:
    virtual MatColor compute(HitContext context) const = 0;

    static MatColor shade(RaycastHit hit, Scene& scene, Line3 ray, unsigned depth = 5);

private:
    static float projectShadow(Light& light, Point3 point, Vector3 normal, Scene& scene);
    static float specularity(Light& light, RaycastHit hit, Vector3 normal, Line3 ray);
    static Vector3 reflectRay(Vector3 rayDir, Vector3 normal);
    static MatColor reflection(RaycastHit hit, Vector3 ray, Vector3 normal,
            Scene& scene, unsigned depth);
};

class LightShader
{
public:
    virtual MatColor compute(HitContext context, std::shared_ptr<Light> light) const = 0;
};


#endif //RAYTRACER_SHADER_H
