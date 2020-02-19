#include <algorithm>

#include "color.h"

#include <cmath>

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
