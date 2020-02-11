#include <fstream>

#include "image.h"

void Image::save(std::string filename)
{
    std::ofstream file(filename, std::ios::out);

    //header
    file << "P6 " << w << " " << h << " " << 255 << '\n';
    for (auto color : data)
    {
        file.write((char*)&color, sizeof(PixColor));
    }
}

Image::Image(unsigned width, unsigned height)
    : w(width), h(height), data(width * height)
{
}

Image::Image(unsigned width, unsigned height, PixColor base)
    : w(width), h(height), data(width * height)
{
    for (auto& pix : data)
    {
        pix = base;
    }
}

void Image::set(unsigned x, unsigned y, PixColor color) {
    data.at(x + y * w) = color;
}

unsigned Image::width() const {
    return w;
}

unsigned Image::height() const {
    return h;
}
