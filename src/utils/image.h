#ifndef RAYTRACER_IMAGE_H
#define RAYTRACER_IMAGE_H

#include <vector>
#include <string>
#include "color.h"

class Image
{
private:
    unsigned w;
    unsigned h;

    std::vector<PixColor> data;

public:
    Image(unsigned width, unsigned height);
    Image(unsigned width, unsigned height, PixColor base);
    void save(std::string filename);

    unsigned width() const;
    unsigned height() const;

    void set(unsigned x, unsigned y, PixColor color);
};


#endif //RAYTRACER_IMAGE_H
