//
// Created by debowin on 10/8/17.
//

#ifndef FRAYTRACER_SPHERE_H
#define FRAYTRACER_SPHERE_H


#include <utility>

#include "Material.h"
#include "Ray.h"
#include "HitInfo.h"

class Sphere {
    Vector center;
    float r;
    Material material;
public:
    Sphere(const Vector &center, float r, Material material);

    const Vector &getPosition() const;

    float getR() const;

    const Material &getMaterial() const;

    HitInfo* intersect(Ray ray, float fMin, float fMax);
};


#endif //FRAYTRACER_SPHERE_H
