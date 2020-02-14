#ifndef RAYTRACER_SCENE_H
#define RAYTRACER_SCENE_H


#include <memory>
#include <scene/sceneobject.h>
#include <vector>
#include <utils/raycastHit.h>
#include <scene/light.h>

class Scene {
public:
    void addObject(std::shared_ptr<SceneObject> obj);
    void addLight(std::shared_ptr<Light> light);

    std::optional<RaycastHit> raycast(Line3 ray);

private:
    std::vector<std::shared_ptr<SceneObject>> objects_;
    std::vector<std::shared_ptr<Light>> lights_;

    std::vector<RaycastHit> raycast_objects(Line3 ray);
};


#endif //RAYTRACER_SCENE_H
