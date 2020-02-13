#include "camera.h"

Camera::Camera(Point3 position, Vector3 forward, float xAngle, float yAngle, float zmin)
{

}

Camera::Camera(Point3 position, float xAngle, float yAngle, float zmin)
{

}

void Camera::initVectors()
{
    forward_ = forward_.normalized();
    //suppose the forward vector is already set
    //compute the right vector
    //if we want the camera to rotate around the forward axis, the rotation should
    //be done separately
    right_ = Vector3(forward_.y, 0.f, -forward_.x).normalized();

    //compute the up vector
    up_ = Vector3::cross(right_, forward_).normalized();
}

void Camera::lookAt(Point3 point)
{

}
