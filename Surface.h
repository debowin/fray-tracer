//
// Created by debowin on 10/21/17.
//

#ifndef FRAYTRACER_SURFACE_H
#define FRAYTRACER_SURFACE_H


#include <utility>

#include "Material.h"
#include "HitInfo.h"
#include "Ray.h"

class Surface {
protected:
    Surface(Material material) : material(std::move(material)) {}
    Material material;
public:
    virtual HitInfo* intersect(Ray ray, float tMin, float tMax) = 0;
};

#endif //FRAYTRACER_SURFACE_H
