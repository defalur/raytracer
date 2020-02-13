#ifndef RAYTRACER_CAMERA_H
#define RAYTRACER_CAMERA_H


#include <utils/vector3.h>

class Camera
{
public:
    Camera(Point3 position, float xAngle, float yAngle, float zmin);
    Camera(Point3 position, Vector3 forward, float xAngle, float yAngle, float zmin);

    void lookAt(Point3 point);

private:
    Point3 position_;
    Vector3 forward_;
    Vector3 up_;
    Vector3 right_;
    float zmin_;

    void initVectors();
};


#endif //RAYTRACER_CAMERA_H
