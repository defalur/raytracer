#include <algorithm>
#include <memory>
#include "scene.h"

void Scene::addObject(std::shared_ptr<SceneObject> obj) {
    objects_.push_back(obj);
}

std::optional<RaycastHit> Scene::raycast(Line3 ray) {
    return raycast_objects(ray).front();
}

std::vector<RaycastHit> Scene::raycast_objects(Line3 ray) {
    std::vector<RaycastHit> hits;

    for (auto& obj : objects_)
    {
        auto tmp = obj->intersect(ray);
        hits.insert(hits.end(), tmp.begin(), tmp.end());
    }

    std::sort(hits.begin(), hits.end(),
            [](RaycastHit a, RaycastHit b)
            {
                return a.distance < b.distance;
            });

    return hits;
}

void Scene::addLight(std::shared_ptr<Light> light) {
    lights_.push_back(light);
}
