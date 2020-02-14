#ifndef RAYTRACER_UNIFORMTEXTURE_H
#define RAYTRACER_UNIFORMTEXTURE_H


#include "texturematerial.h"

class UniformTexture : public TextureMaterial
{
public:
    UniformTexture();//simple white diffuse texture
    UniformTexture(MatColor color, Material material = {0,0});
    UniformTexture(PixColor pixcolor, Material material = {0,0});

    MatColor getColor(float, float) const final;
    Material getMaterial(float, float) const final;

private:
    MatColor color;
    Material material;
};


#endif //RAYTRACER_UNIFORMTEXTURE_H
