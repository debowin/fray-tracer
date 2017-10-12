//
// Created by debowin on 10/9/17.
//

#include "HitInfo.h"

#include <utility>

float HitInfo::getT() const {
    return t;
}

HitInfo::HitInfo(Material material, float t, Vector normal, Vector point) :
        material(std::move(material)), t(t), normal(normal), point(point) {
}

Material &HitInfo::getMaterial() {
    return material;
}

Vector &HitInfo::getNormal() {
    return normal;
}

Vector &HitInfo::getPoint() {
    return point;
}
