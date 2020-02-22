#include <iostream>
#include <scene/camera.h>
#include <scene/sphere.h>
#include <materials/uniformtexture.h>
#include <scene/pointlight.h>
#include <shader/shader.h>
#include <shader/diffuseshader.h>
#include <shader/specularshader.h>
#include <shader/reflectionshader.h>
#include "utils/vector3.h"
#include "utils/color.h"
#include "utils/image.h"
#include "utils/vector4.h"
#include "scene.h"
#include <shader/shaderengine.h>
#include <scene/triangle.h>

int main()
{
    auto scene = Scene{};
    auto camera = Camera{Vector3{1, 2, 1.5}, 90, 0.5f};

    auto cyan = UniformTexture{PixColor{0, 255, 255},
                               TextureMaterial::Material{0.1,0.9, 5}};
    auto red = UniformTexture{PixColor{255, 0, 0},
                              TextureMaterial::Material{0.8,0.2, 10}};
    auto green = UniformTexture{PixColor{10, 255, 50},
                                TextureMaterial::Material{0.2,0.8, 8}};
    auto groundMat = UniformTexture{MatColor{0.8, 0.6, 1},
                                TextureMaterial::Material{0.3,0.7, 10}};
    auto obj = std::make_shared<Sphere>(Point3{0, 5, 0}, 0.5f, cyan);
    auto obj2 = std::make_shared<Sphere>(Point3{1.5, 4, 0}, 0.5f, red);
    auto obj3 = std::make_shared<Sphere>(Point3{-1.3, 4, 0}, 0.5f, green);
    auto ground = std::make_shared<Sphere>(Point3{0, 0, -200.5f}, 200, groundMat);

    auto triangle = std::make_shared<Triangle>(Point3{0, 5, 0}, Point3(1.5, 4, 0),
            Point3{-1.3, 4, 0}, red);

    auto light = std::make_shared<PointLight>(30, MatColor{1, 1, 1}, Point3{-1.5, 2, 20});
    auto light2 = std::make_shared<PointLight>(9, MatColor{1, 0.8, 1}, Point3{0, 3, 2});

    camera.lookAt(obj->position());

    scene.addObject(obj);
    scene.addObject(obj2);
    scene.addObject(obj3);
    //scene.addObject(triangle);
    scene.addLight(light);
    scene.addLight(light2);
    scene.addObject(ground);

    auto shaderEngine = ShaderEngine();
    shaderEngine.addLightShader(std::make_shared<DiffuseShader>());
    shaderEngine.addLightShader(std::make_shared<SpecularShader>());
    shaderEngine.addShader(std::make_shared<ReflectionShader>());

    std::cout << "Hello, World!" << std::endl;
    auto img = Image(1920, 1080);

    camera.computeMatrix(img.width(), img.height());

    for (unsigned y = 0; y < img.height(); y++)
    {
        for (unsigned x = 0; x < img.width(); x++)
        {
            auto ray = camera.getRay(x, y);

            auto hit = scene.raycast(ray);

            if (hit.has_value())
            {
                auto context = HitContext{scene, *hit, ray.direction, shaderEngine};
                auto pixColor = shaderEngine.shade(context).gamma(2.2).toPixColor();
                //auto pixColor = Shader::shade(*hit, scene, ray).toPixColor();
                img.set(x, y, pixColor);
            }
        }
        //std::cout << "Progress: " << (float)y / img.height() << "\n";
    }
    img.save("test.ppm");

    return 0;
}
