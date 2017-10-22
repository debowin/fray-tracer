//
// Created by debowin on 10/10/17.
//
#include "Sphere.h"
#include <cmath>

Sphere::Sphere(const Vector3D &center, float r, Material m) : center(center), r(r),
                                                                            Surface(m) {}

const Vector3D &Sphere::getPosition() const {
    return center;
}

float Sphere::getR() const {
    return r;
}

HitInfo *Sphere::intersect(Ray ray, float tMin, float tMax) {
    double discriminant = pow(ray.getDirection()*(ray.getOrigin()-getPosition()), 2)
                          - (ray.getOrigin()-getPosition()) * (ray.getOrigin()-getPosition()) + getR() * getR();
    if(discriminant < 0)
        return nullptr;
    float t1 = -ray.getDirection() * (ray.getOrigin()-getPosition()) + std::sqrt((float)discriminant);
    float t2 = -ray.getDirection() * (ray.getOrigin()-getPosition()) - std::sqrt((float)discriminant);
    if(t1 > t2)
        std::swap(t1, t2);
    if(t1<tMin || t1 > tMax){
        t1 = t2;
        if(t1<tMin || t1 > tMax)
            return nullptr;
    }
    Vector3D p = ray.getOrigin() + ray.getDirection()*t1;
    Vector3D normal = p-center;
    return new HitInfo(material, t1, normalize(normal), p, ray.getDirection());
}
