//
// Created by debowin on 10/21/17.
//

#include "Triangle.h"

Triangle::Triangle(Vector3D &v1, Vector3D &v2, Vector3D &v3, Material m) : v1(v1), v2(v2), v3(v3), Surface(m) {
    n1 = n2 = n3 = (v2-v1)^(v3-v1);
}

Triangle::Triangle(Vector3D &v1, Vector3D &v2, Vector3D &v3, Vector3D &n1, Vector3D &n2,
                   Vector3D &n3, Material m) : v1(v1), v2(v2), v3(v3), n1(n1), n2(n2), n3(n3), Surface(m) {}

HitInfo *Triangle::intersect(Ray ray, float tMin, float tMax) {
    Vector3D d = ray.getDirection(), e = ray.getOrigin();
    Matrix3D mat{v1.x - v2.x, v1.y - v2.y, v1.z - v2.z,
                v1.x - v3.x, v1.y - v3.y, v1.z - v3.z,
                d.x, d.y, d.z};
    Vector3D vec{v1.x - e.x,
                v1.y - e.y,
                v1.z - e.z};
    float M = determinant(mat);
    float t = determinant(setColumn(mat, vec, 2))/M;
    if(t<tMin || t>tMax)
        return nullptr;
    float gamma = determinant(setColumn(mat, vec, 1))/M;
    if(gamma<0 || gamma>1)
        return nullptr;
    float beta = determinant(setColumn(mat, vec, 0))/M;
    if(beta<0 || beta > 1-gamma)
        return nullptr;
    Vector3D normal = n1*(1-beta-gamma) + n2*beta + n3*gamma;
    if(normal*d>0)
        normal = -normal;
    return new HitInfo(material, t, normalize(normal), e+d*t, normalize(d));
}
