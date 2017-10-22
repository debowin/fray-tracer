//
// Created by debowin on 10/21/17.
//

#ifndef FRAYTRACER_TRIANGLE_H
#define FRAYTRACER_TRIANGLE_H


#include "Surface.h"

class Triangle : public Surface {
    Vector3D v1, v2, v3;
    Vector3D n1, n2, n3;
public:
    Triangle(Vector3D &v1, Vector3D &v2, Vector3D &v3, Material m);

    Triangle(Vector3D &v1, Vector3D &v2, Vector3D &v3, Vector3D &n1, Vector3D &n2, Vector3D &n3, Material m);

    HitInfo *intersect(Ray ray, float tMin, float tMax) override;
};


#endif //FRAYTRACER_TRIANGLE_H
