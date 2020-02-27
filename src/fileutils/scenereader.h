#ifndef RAYTRACER_SCENEREADER_H
#define RAYTRACER_SCENEREADER_H


#include <scene.h>
#include <optional>

#include <fileutils/json.hpp>
using json = nlohmann::json;

std::optional<std::shared_ptr<Scene>> loadScene(std::string path);

template<typename objtype>
std::shared_ptr<objtype> createObject(json j, std::shared_ptr<Scene> scene);

#endif //RAYTRACER_SCENEREADER_H
