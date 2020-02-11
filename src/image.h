#ifndef RAYTRACER_IMAGE_H
#define RAYTRACER_IMAGE_H

#include <vector>
#include <string>
#include "color.h"

class Image {
    unsigned width;
    unsigned height;

    std::vector<PixColor> data;

    void save(std::string filename);
};


#endif //RAYTRACER_IMAGE_H
