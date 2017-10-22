//
// Created by debowin on 10/8/17.
//

#ifndef FRAYTRACER_SPHERE_H
#define FRAYTRACER_SPHERE_H


#include <utility>

#include "Material.h"
#include "Ray.h"
#include "HitInfo.h"
#include "Surface.h"

class Sphere : public Surface{
    Vector3D center;
    float r;
public:
    Sphere(const Vector3D &center, float r, Material m);

    const Vector3D &getPosition() const;

    float getR() const;

    HitInfo* intersect(Ray ray, float tMin, float tMax) override;
};


#endif //FRAYTRACER_SPHERE_H
