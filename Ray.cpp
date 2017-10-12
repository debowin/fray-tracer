//
// Created by debowin on 10/9/17.
//

#include "Ray.h"

Ray::Ray(const Vector &origin, const Vector &direction) : origin(origin), direction(direction) {}

Vector Ray::getOrigin() {
    return origin;
}

Vector Ray::getDirection() {
    return direction;
}

Ray::Ray() = default;
