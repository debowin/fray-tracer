//
// Created by debowin on 10/9/17.
//

#ifndef FRAYTRACER_RAY_H
#define FRAYTRACER_RAY_H


#include "Basics.h"

class Ray {
    Vector3D origin;
    Vector3D direction;
public:
    Ray(const Vector3D &origin, const Vector3D &direction);

    Ray();

    Vector3D getOrigin();

    Vector3D getDirection() ;
};


#endif //FRAYTRACER_RAY_H
