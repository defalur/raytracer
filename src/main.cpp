#include <iostream>
#include <shader/shader.h>
#include "utils/vector3.h"
#include "utils/color.h"
#include "utils/image.h"
#include <fileutils/scenereader.h>

int main(int argc, char **argv)
{
    if (argc != 5)
    {
        std::cout << "Usage: ./raytracer [input file] [output file] [image width] [image height].\n";
        return 1;
    }

    std::string inputFile = argv[1];
    std::string outputFile = argv[2];
    unsigned width = std::stoi(argv[3]);
    unsigned height = std::stoi(argv[4]);

    auto loadResult = loadScene(inputFile);

    std::shared_ptr<RenderContext> renderContext;
    if (loadResult.has_value())
        renderContext = loadResult.value();
    else
    {
        std::cout << "Could not load scene.\n";
        return 2;
    }

    std::cout << "Hello, World!" << std::endl;
    auto img = Image(width, height);

    renderContext->camera->computeMatrix(img.width(), img.height());

    for (unsigned y = 0; y < img.height(); y++)
    {
        for (unsigned x = 0; x < img.width(); x++)
        {
            auto ray = renderContext->camera->getRay(x, y);

            auto hit = renderContext->scene->raycast(ray);

            if (hit.has_value())
            {
                auto context = HitContext{*renderContext->scene, *hit, ray,
                                          *renderContext->shaderEngine};
                auto pixColor = renderContext->shaderEngine
                        ->shade(context).gamma(2.2).toPixColor();
                //auto pixColor = Shader::shade(*hit, scene, ray).toPixColor();
                img.set(x, y, pixColor);
            }
        }
        //std::cout << "Progress: " << (float)y / img.height() << "\n";
    }
    img.save(outputFile);

    return 0;
}
