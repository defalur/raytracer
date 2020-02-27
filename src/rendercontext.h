#ifndef RAYTRACER_RENDERCONTEXT_H
#define RAYTRACER_RENDERCONTEXT_H


#include <scene/camera.h>
#include <shader/shaderengine.h>
#include "scene.h"

struct RenderContext {
    std::shared_ptr<Scene> scene;
    std::shared_ptr<Camera> camera;
    std::shared_ptr<ShaderEngine> shaderEngine;

    void addMaterial(std::string name, std::shared_ptr<TextureMaterial> mat)
    {
        materials_.emplace(name, mat);
    }

    std::shared_ptr<TextureMaterial> getMaterial(std::string name)
    {
        return materials_[name];
    }

private:
    std::map<std::string, std::shared_ptr<TextureMaterial>> materials_;
};


#endif //RAYTRACER_RENDERCONTEXT_H
