#include <math.h>

#include "camera.h"

Camera::Camera(Point3 position, Vector3 forward, float xAngle, float zmin)
    : position_(position), forward_(forward), zmin_(zmin)
{
    auto radxAngle = static_cast<float>(180.f / M_PI * xAngle);
    unitY_ = unitX_ = zmin * tan(radxAngle / 2.f);
    initVectors();
}

Camera::Camera(Point3 position, float xAngle, float zmin)
    : Camera(position, Vector3{0, 1, 0}, xAngle, zmin)
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
    forward_ = forward_ * zmin_;
}



void Camera::lookAt(Point3 point)
{
    forward_ = (point - position_);
    initVectors();
}

void Camera::computeMatrix(unsigned imageWidth, unsigned imageHeight) {
    picToCamera_.set(0, 0, -2.f / (float)imageWidth);
    picToCamera_.set(1, 1, 2.f / (float)imageHeight);
    picToCamera_.set(2, 2, 1);
    picToCamera_.set(0, 2, 1);
    picToCamera_.set(1, 2, -1);

    float ratio = (float)imageHeight / (float)imageWidth;
    unitY_ *= ratio;
}

Line3 Camera::getRay(unsigned x, unsigned y) const {
    //converting to homogeneous coordinates
    Vector3 imagePos = {(float)x, (float)y, 1};

    //applying the transformation matrix
    std::array<float, 3> screenPos = picToCamera_ * imagePos.vec;
    auto tmp = Vector3{screenPos};

    //std::cout << "In: " << imagePos << " Out: " << tmp << "\n";

    //computing ray
    auto ray = forward_ + up_ * unitY_ * screenPos[1] + right_ * unitX_ * screenPos[0];

    //std::cout << "Ray: " << ray << "\n";

    return Line3{position_, ray.normalized()};
}
