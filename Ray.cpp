//
// Created by debowin on 10/9/17.
//

#include "Ray.h"

Ray::Ray(const Vector3D &origin, const Vector3D &direction) : origin(origin), direction(direction) {}

Vector3D Ray::getOrigin() {
    return origin;
}

Vector3D Ray::getDirection() {
    return direction;
}

Ray::Ray() = default;
