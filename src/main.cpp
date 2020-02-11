#include <iostream>
#include "vector3.h"
#include "color.h"
#include "image.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    Vector3 v{12, 4.5, 5};
    v = Vector3(1, 2, 3);
    auto img = Image(600, 256, PixColor{50, 255, 100});
    for (unsigned x = 0; x < img.width(); x++)
    {
        for (unsigned y = 0; y < img.height(); y++)
        {
            img.set(x, y, PixColor{static_cast<uint8_t>(y % 256),
                                   static_cast<uint8_t>(y % 256),
                                   static_cast<uint8_t>(y % 256)});
        }
    }
    img.save("test.ppm");
    return 0;
}
