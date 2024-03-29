#ifndef RAYTRACER_SCENE_H
#define RAYTRACER_SCENE_H


#include <memory>
#include <scene/sceneobject.h>
#include <vector>
#include <utils/raycastHit.h>
#include <scene/light.h>
#include <map>

class Scene {
public:
    void addObject(std::shared_ptr<SceneObject> obj);
    void addLight(std::shared_ptr<Light> light);

    std::optional<RaycastHit> raycast(Line3 ray,
            float dist = std::numeric_limits<float>::infinity());

    auto getLights() const
    {
        return lights_;
    }

    auto getObject(unsigned index)
    {
        return objects_[index];
    }

private:
    std::vector<std::shared_ptr<SceneObject>> objects_;
    std::vector<std::shared_ptr<Light>> lights_;

    std::vector<RaycastHit> raycast_objects(Line3 ray);
};


#endif //RAYTRACER_SCENE_H
