#include <fstream>
#include "scenereader.h"
#include <fileutils/json.hpp>
#include <iostream>
#include <materials/uniformtexture.h>
#include <scene/sphere.h>
#include <scene/triangle.h>
#include <rendercontext.h>
#include <scene/pointlight.h>
#include <shader/diffuseshader.h>
#include <shader/specularshader.h>
#include <shader/ambientshader.h>
#include <shader/reflectionshader.h>
#include <shader/transparencyshader.h>

using json = nlohmann::json;

std::shared_ptr<SceneObject> loadObject(json data, std::shared_ptr<RenderContext> context)
{
    auto name = data["name"].get<std::string>();
    auto mat = data["mat"].get<std::string>();
    if (name == "sphere")
    {
        auto center = data["center"].get<std::array<float, 3>>();
        auto radius = data["radius"].get<float>();

        return std::make_shared<Sphere>(Vector3{center},
                radius, context->getMaterial(mat));
    }
    else if (name == "triangle")
    {
        auto a = data["a"].get<std::array<float, 3>>();
        auto b = data["b"].get<std::array<float, 3>>();
        auto c = data["c"].get<std::array<float, 3>>();

        return std::make_shared<Triangle>(Vector3{a},
                Vector3{b}, Vector3{c}, context->getMaterial(mat));
    }

    return nullptr;
}

std::shared_ptr<Light> loadLight(json data)
{
    auto type = data["type"].get<std::string>();
    auto color = data["color"].get<std::array<float, 3>>();
    if (type == "point")
    {
        auto position = data["position"].get<std::array<float, 3>>();
        auto strength = data["strength"].get<float>();

        return std::make_shared<PointLight>(strength, MatColor{color},
                Vector3{position});
    }

    return nullptr;
}

void loadShader(json data, std::shared_ptr<ShaderEngine> engine)
{
    if (data.is_string())
    {
        auto type = data.get<std::string>();
        if (type == "diffuse")
            engine->addLightShader(std::make_shared<DiffuseShader>());
        else if (type == "specular")
            engine->addLightShader(std::make_shared<SpecularShader>());
        else if (type == "reflection")
            engine->addShader(std::make_shared<ReflectionShader>());
        else if (type == "transparent")
            engine->addShader(std::make_shared<TransparencyShader>());
    }
    else if (data.is_object())
    {
        auto type = data["type"].get<std::string>();
        if (type == "ambient")
        {
            auto color = data["color"].get<std::array<float, 3>>();
            engine->addShader(std::make_shared<AmbientShader>(MatColor{color}));
        }
    }
}

std::optional<std::shared_ptr<RenderContext>> loadScene(std::string path) {
    std::ifstream file(path);

    if (not file.is_open())
        return std::nullopt;

    json j;
    file >> j;

    auto context = std::make_shared<RenderContext>();

    auto scene = std::make_shared<Scene>();
    context->scene = scene;

    //Read all materials
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
            context->addMaterial(name, std::make_shared<UniformTexture>(resMat));
        }
        else
        {
            //use a texture
            throw std::invalid_argument("Wrong color format");
        }
    }

    //Read all objects
    auto objArray = j["objects"];
    for (auto objData : objArray) {
        if (objData.is_object())
        {
            //create a sceneobject directly (use a factory)
            auto obj = loadObject(objData, context);
            scene->addObject(obj);
        }
        else
        {
            //load an obj file to create all necessary triangles
            throw std::runtime_error("Obj files not yet supported.");
        }
    }

    //configure the camera
    {
        auto cameraData = j["camera"];
        auto origin = cameraData["origin"].get<std::array<float, 3>>();
        auto xangle = cameraData["xangle"].get<float>();
        auto zmin = cameraData["zmin"].get<float>();

        if (cameraData.find("forward") != cameraData.end())
        {
            //a forward vector exists
            auto forward = cameraData["forward"].get<std::array<float, 3>>();
            context->camera = std::make_shared<Camera>(Vector3{origin},
                                                       Vector3{forward},
                                                       xangle, zmin);
        }
        else
        {
            context->camera = std::make_shared<Camera>(Vector3{origin},
                    xangle, zmin);

            if (cameraData.find("lookat") != cameraData.end())
            {
                auto target = cameraData["lookat"];
                if (target.is_array())
                {
                    auto point = target.get<std::array<float, 3>>();
                    context->camera->lookAt(Vector3{point});
                }
                else if (target.is_number())
                {
                    auto objindex = cameraData["lookat"].get<unsigned>();
                    context->camera->lookAt(scene->getObject(objindex)->position());
                }
            }
        }

    }

    //add the lights
    {
        auto lights = j["lights"];
        for (auto lightData : lights)
        {
            auto light = loadLight(lightData);
            context->scene->addLight(light);
        }
    }

    //configure the shader engine
    {
        auto shaderEngine = std::make_shared<ShaderEngine>();
        auto shaders = j["shaders"];
        for (auto shaderData : shaders)
        {
            loadShader(shaderData, shaderEngine);
        }

        context->shaderEngine = shaderEngine;
    }

    return std::optional(context);
}