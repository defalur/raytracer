#include <iostream>
#include <scene/camera.h>
#include <scene/sphere.h>
#include <materials/uniformtexture.h>
#include <scene/pointlight.h>
#include <shader/shader.h>
#include "utils/vector3.h"
#include "utils/color.h"
#include "utils/image.h"
#include "utils/vector4.h"
#include "scene.h"

int main()
{
    auto scene = Scene{};
    auto camera = Camera{Vector3{0, 0, 4}, 90, 0.5f};

    auto cyan = UniformTexture{PixColor{0, 255, 255}};
    auto red = UniformTexture{PixColor{255, 0, 0}};
    auto white = UniformTexture();
    auto obj = std::make_shared<Sphere>(Point3{0, 5, 0}, 0.5f, cyan);
    auto obj2 = std::make_shared<Sphere>(Point3{1, 4, 0}, 0.7f, red);
    auto ground = std::make_shared<Sphere>(Point3{0, 0, -201}, 200, white);

    auto light = std::make_shared<PointLight>(5, MatColor{1, 1, 1}, Point3{1, 2, 1});

    camera.lookAt(obj->position());

    scene.addObject(obj);
    scene.addObject(obj2);
    scene.addLight(light);
    scene.addObject(ground);

    std::cout << "Hello, World!" << std::endl;
    auto img = Image(800, 600);

    camera.computeMatrix(img.width(), img.height());

    for (unsigned y = 0; y < img.height(); y++)
    {
        for (unsigned x = 0; x < img.width(); x++)
        {
            auto ray = camera.getRay(x, y);

            auto hit = scene.raycast(ray);

            if (hit.has_value())
            {
                auto pixColor = Shader::shade(*hit, scene);
                img.set(x, y, pixColor);
            }
        }
        std::cout << "Progress: " << (float)y / img.height() << "\n";
    }
    img.save("test.ppm");

    return 0;
}
