#ifndef RAYTRACER_SHADER_H
#define RAYTRACER_SHADER_H


#include <utils/color.h>
#include <utils/raycastHit.h>
#include <scene.h>

class Shader {
public:
    static PixColor shade(RaycastHit hit, Scene& scene);
};


#endif //RAYTRACER_SHADER_H
