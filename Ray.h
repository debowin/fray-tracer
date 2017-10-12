//
// Created by debowin on 10/9/17.
//

#ifndef FRAYTRACER_RAY_H
#define FRAYTRACER_RAY_H


#include "Basics.h"

class Ray {
    Vector origin;
    Vector direction;
public:
    Ray(const Vector &origin, const Vector &direction);

    Ray();

    Vector getOrigin();

    Vector getDirection() ;
};


#endif //FRAYTRACER_RAY_H
