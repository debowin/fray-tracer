//
// Created by debowin on 10/9/17.
//

#ifndef FRAYTRACER_HITINFO_H
#define FRAYTRACER_HITINFO_H


#include "Material.h"

class HitInfo {
    Material material;
    float t;
    Vector3D d;
    Vector3D normal;
    Vector3D point;
public:
    float getT() const;

    HitInfo(Material material, float t, Vector3D normal, Vector3D point, Vector3D direction);

    Material &getMaterial();

    Vector3D &getNormal();

    Vector3D &getPoint();

    Vector3D &getD();
};


#endif //FRAYTRACER_HITINFO_H
