#include "uniformtexture.h"
UniformTexture::UniformTexture()
    : color{1, 1, 1}, material{1,0, 0}
{
}

UniformTexture::UniformTexture(MatColor color, TextureMaterial::Material material)
    : color(color), material(material)
{
}

UniformTexture::UniformTexture(PixColor pixcolor, TextureMaterial::Material material)
    : color{(float)pixcolor.r / 255.0f,
            (float)pixcolor.g / 255.0f,
            (float)pixcolor.b / 255.0f},
    material(material)
{
}

MatColor UniformTexture::getColor(float, float) const
{
    return color;
}

TextureMaterial::Material UniformTexture::getMaterial(float, float) const
{
    return material;
}

