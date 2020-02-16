#ifndef RAYTRACER_SHADER_H
#define RAYTRACER_SHADER_H


#include <utils/color.h>
#include <utils/raycastHit.h>
#include <scene.h>

class Shader {
public:
    static PixColor shade(RaycastHit hit, Scene& scene, Line3 ray);

private:
    static float projectShadow(Light& light, Point3 point, Vector3 normal, Scene& scene);
    static float specularity(Light& light, RaycastHit hit, Vector3 normal, Line3 ray);
};


#endif //RAYTRACER_SHADER_H
