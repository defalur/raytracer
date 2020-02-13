#ifndef RAYTRACER_TEXTUREMATERIAL_H
#define RAYTRACER_TEXTUREMATERIAL_H


#include "tools/color.h"

class TextureMaterial
{
public:
    struct Material
    {
        float kd;//diffuse
        float ks;//specular intensity
        float ns;//specular roughness
    };

    virtual MatColor getColor(float x, float y) const = 0;//need 3 dimensions?
    virtual Material getMaterial(float x, float y) const  = 0;//need 3 dimensions?
};


#endif //RAYTRACER_TEXTUREMATERIAL_H
