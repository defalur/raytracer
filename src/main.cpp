#include <iostream>
#include <scene/camera.h>
#include <scene/sphere.h>
#include <materials/uniformtexture.h>
#include <scene/pointlight.h>
#include "utils/vector3.h"
#include "utils/color.h"
#include "utils/image.h"
#include "utils/vector4.h"
#include "scene.h"

int main()
{
    auto scene = Scene{};
    auto camera = Camera{Vector3{0, 0, 0}, 90, 0.5f};

    auto cyan = UniformTexture{PixColor{0, 255, 255}};
    auto obj = std::make_shared<Sphere>(Point3{0, 5, 0}, 0.5f, cyan);

    auto light = std::make_shared<PointLight>(10, MatColor{1, 1, 1}, Point3{1, 2, 1});

    scene.addObject(obj);
    scene.addLight(light);

    std::cout << "Hello, World!" << std::endl;
    auto img = Image(800, 600);

    camera.computeMatrix(img.width(), img.height());

    for (unsigned x = 0; x < img.width(); x++)
    {
        for (unsigned y = 0; y < img.height(); y++)
        {
            auto ray = camera.getRay(x, y);

            auto hit = scene.raycast(ray);

            if (hit.has_value())
            {
                auto pixColor = hit->object->texture(hit->point);
                img.set(x, y, pixColor.toPixColor());
            }
        }
    }
    img.save("test.ppm");

    return 0;
}
