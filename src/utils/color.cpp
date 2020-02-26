#include <algorithm>

#include "color.h"

#include <cmath>

MatColor::MatColor()
    : r{0}, g{0}, b{0}
{}

MatColor::MatColor(float r, float g, float b)
    : r{r}, g{g}, b{b}
{}

//used in the scene parser. Converts pixcolor to matcolor if necessary
MatColor::MatColor(std::array<float, 3> color)
    : r{color[0]}, g{color[1]}, b{color[2]}
{
    if (r > 1.f or g > 1.f or b > 1.f) {
        r = r / 255.f;
        g = g / 255.f;
        b = b / 255.f;
    }
}

MatColor MatColor::operator*(float k) const
{
    return MatColor{r * k, g * k, b * k};
}

MatColor MatColor::operator*(MatColor c) const
{
    return MatColor{r * c.r, g * c.g, b * c.b};
}

PixColor MatColor::toPixColor() const
{
    return PixColor{(uint8_t)(r * 255.f), (uint8_t)(g * 255.f), (uint8_t)(b * 255.f)};
}

MatColor MatColor::gamma(float gamma)
{
    auto correction = 1.f/gamma;
    return MatColor{powf(r, correction), powf(g, correction), powf(b, correction)};
}

MatColor MatColor::operator+(MatColor c) const
{
    return MatColor{std::min(r + c.r, 1.f),
                    std::min(g + c.g, 1.f),
                    std::min(b + c.b, 1.f)};
}
