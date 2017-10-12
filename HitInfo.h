//
// Created by debowin on 10/9/17.
//

#ifndef FRAYTRACER_HITINFO_H
#define FRAYTRACER_HITINFO_H


#include "Material.h"

class HitInfo {
    Material material;
    float t;
    Vector d;
    Vector normal;
    Vector point;
public:
    float getT() const;

    HitInfo(Material material, float t, Vector normal, Vector point, Vector direction);

    Material &getMaterial();

    Vector &getNormal();

    Vector &getPoint();

    Vector &getD();
};


#endif //FRAYTRACER_HITINFO_H
