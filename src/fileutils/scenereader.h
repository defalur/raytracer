#ifndef RAYTRACER_SCENEREADER_H
#define RAYTRACER_SCENEREADER_H


#include <scene.h>
#include <optional>

#include <fileutils/json.hpp>
#include <rendercontext.h>

using json = nlohmann::json;

std::optional<std::shared_ptr<RenderContext>> loadScene(std::string path);

#endif //RAYTRACER_SCENEREADER_H
