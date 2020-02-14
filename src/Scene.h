#ifndef RAYTRACER_SCENE_H
#define RAYTRACER_SCENE_H


#include <scene/sceneobject.h>
#include <vector>
#include <utils/raycastHit.h>

class Scene {
public:
    void addObject(SceneObject* obj);

    RaycastHit raycast(Line3 ray);

private:
    std::vector<std::shared_ptr<SceneObject>> objects_;

    std::vector<RaycastHit> raycast_objects(Line3 ray);
};


#endif //RAYTRACER_SCENE_H
