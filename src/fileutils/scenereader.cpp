#include <fstream>
#include "scenereader.h"
#include <fileutils/json.hpp>
#include <iostream>
#include <materials/uniformtexture.h>
#include <scene/sphere.h>
#include <scene/triangle.h>

using json = nlohmann::json;

std::shared_ptr<SceneObject> loadObject(json data, const std::shared_ptr<Scene> scene)
{
    auto name = data["name"].get<std::string>();
    auto mat = data["mat"].get<std::string>();
    if (name == "sphere")
    {
        auto center = data["center"].get<std::array<float, 3>>();
        auto radius = data["radius"].get<float>();

        return std::make_shared<Sphere>(center, radius, scene->getMaterial(mat));
    }
    else if (name == "triangle")
    {
        auto a = data["a"].get<std::array<float, 3>>();
        auto b = data["b"].get<std::array<float, 3>>();
        auto c = data["c"].get<std::array<float, 3>>();

        return std::make_shared<Triangle>(a, b, c, mat);
    }
}

std::optional<std::shared_ptr<Scene>> loadScene(std::string path) {
    std::ifstream file(path);

    if (not file.is_open())
        return nullptr;

    json j;
    file >> j;

    auto res = std::make_shared<Scene>();

    auto matArray = j["materials"];
    for (auto mat : matArray)
    {
        std::string name = mat["name"].get<std::string>();
        auto tmp = TextureMaterial::Material{};
        auto matData = mat["mat"];
        tmp.kd = matData["kd"].get<float>();
        tmp.ks = matData["ks"].get<float>();
        tmp.ns = matData["ns"].get<float>();
        bool transparent = matData["transparent"].get<bool>();
        if (transparent)
        {
            tmp.transparent = true;
            tmp.kr = matData["kr"].get<float>();
        }
        auto color = mat["color"];
        if (color.is_array())
        {
            //array means a single color
            //we can create a uniformtexture here and add it to the scene instance
            auto resMat = UniformTexture{MatColor{color.get<std::array<float, 3>>()}, tmp};
            res->addMaterial(name, std::make_shared<UniformTexture>(resMat));
        }
        else
        {
            //use a texture
            throw std::invalid_argument("Wrong color format");
        }
    }

    auto objArray = j["objects"];
    for (auto objData : objArray) {
        if (objData.is_object())
        {
            //create a sceneobject directly (use a factory)
            auto obj = loadObject(objData, res);
            res->addObject(obj);
        }
        else
        {
            //load an obj file to create all necessary triangles
            throw std::runtime_error("Obj files not yet supported.");
        }
    }

    auto camera = j["camera"];


    return res;
}