//
// Created by debowin on 10/9/17.
//

#include "HitInfo.h"

#include <utility>

float HitInfo::getT() const {
    return t;
}

HitInfo::HitInfo(Material material, float t, Vector3D normal, Vector3D point, Vector3D direction) :
        material(std::move(material)), t(t), normal(normal), point(point), d(direction) {
}

Material &HitInfo::getMaterial() {
    return material;
}

Vector3D &HitInfo::getNormal() {
    return normal;
}

Vector3D &HitInfo::getPoint() {
    return point;
}

Vector3D &HitInfo::getD() {
    return d;
}
