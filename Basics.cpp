//
// Created by debowin on 10/9/17.
//

#include <cmath>
#include "Basics.h"

void setRGB(Colour* colour, float r, float g, float b){
    colour->r = r;
    colour->g = g;
    colour->b = b;
}

bool isBlack(Colour colour){
    return colour.r == 0 && colour.g == 0 && colour.b == 0;
}

void setXYZ(Vector3D* vector, float x, float y, float z){
    vector->x = x;
    vector->y = y;
    vector->z = z;
}

float magnitude(Vector3D vector){
    return (float)sqrt(pow(vector.x, 2) + pow(vector.y, 2) + pow(vector.z, 2));
}

Vector3D normalize(Vector3D vector){
    float mag = magnitude(vector);
    return Vector3D{vector.x/mag, vector.y/mag, vector.z/mag};
}

float angleBetween(Vector3D u, Vector3D v){
    return std::acos((u*v)/(magnitude(u)*magnitude(v)))*180/(float)M_PI;
}

float determinant(Matrix3D mat){
    return mat.a*(mat.e*mat.i-mat.h*mat.f) -
           mat.b*(mat.d*mat.i-mat.g*mat.f) +
           mat.c*(mat.d*mat.h-mat.e*mat.g);
}

Matrix3D setColumn(Matrix3D mat, Vector3D col, int colId){
    Matrix3D newMat = mat;
    switch(colId){
        case 0:
            newMat.a = col.x;
            newMat.b = col.y;
            newMat.c = col.z;
            break;
        case 1:
            newMat.d = col.x;
            newMat.e = col.y;
            newMat.f = col.z;
            break;
        case 2:
            newMat.g = col.x;
            newMat.h = col.y;
            newMat.i = col.z;
            break;
        default:
            break;
    }
    return newMat;
}