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

void setXYZ(Vector* vector, float x, float y, float z){
    vector->x = x;
    vector->y = y;
    vector->z = z;
}

float magnitude(Vector vector){
    return (float)sqrt(pow(vector.x, 2) + pow(vector.y, 2) + pow(vector.z, 2));
}

Vector normalize(Vector vector){
    float mag = magnitude(vector);
    return Vector{vector.x/mag, vector.y/mag, vector.z/mag};
}