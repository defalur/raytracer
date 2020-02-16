#ifndef RAYTRACER_CAMERA_H
#define RAYTRACER_CAMERA_H


#include <utils/Matrix.h>
#include <utils/vector3.h>

class Camera
{
public:
    Camera(Point3 position, float xAngle, float zmin);//forward (0, 1, 0)
    Camera(Point3 position, Vector3 forward, float xAngle, float zmin);

    void computeMatrix(unsigned imageWidth, unsigned imageHeight);

    void lookAt(Point3 point);

    Line3 getRay(unsigned x, unsigned y) const;

private:
    Point3 position_;
    Vector3 forward_;
    Vector3 up_;
    Vector3 right_;
    float zmin_;

    float unitX_;
    float unitY_;

    Matrix3x3 picToCamera_;

    void initVectors();
};


#endif //RAYTRACER_CAMERA_H
