#include <algorithm>
#include <memory>
#include "scene.h"

void Scene::addObject(std::shared_ptr<SceneObject> obj) {
    objects_.push_back(obj);
}

std::optional<RaycastHit> Scene::raycast(Line3 ray) {
    auto hits = raycast_objects(ray);
    if (hits.size() > 0)
    {
        return hits.front();
    }
    else
    {
        return std::nullopt;
    }
}

std::vector<RaycastHit> Scene::raycast_objects(Line3 ray) {
    std::vector<RaycastHit> hits;

    for (auto& obj : objects_)
    {
        auto tmp = obj->intersect(ray);
        for (auto& hit : tmp)
        {
            if (hit.distance > 0)
            {
                hits.push_back(hit);
            }
        }
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
