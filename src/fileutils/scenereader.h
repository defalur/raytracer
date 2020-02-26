#ifndef RAYTRACER_SCENEREADER_H
#define RAYTRACER_SCENEREADER_H


#include <scene.h>
#include <optional>

std::optional<std::shared_ptr<Scene>> loadScene(std::string path);


#endif //RAYTRACER_SCENEREADER_H
