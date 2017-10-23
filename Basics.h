//
// Created by debowin on 10/9/17.
//

#ifndef FRAYTRACER_COMPONENTS_H
#define FRAYTRACER_COMPONENTS_H

#include <cmath>

struct Colour{
    float r, g, b;

    Colour& operator=(Colour c){
        r = c.r;
        g = c.g;
        b = c.b;
        return *this;
    }

    Colour operator+(Colour c){
        return {r+c.r, g+c.g, b+c.b};
    }

    Colour operator-(Colour c){
        return {r-c.r, g-c.g, b-c.b};
    }

    Colour operator*(Colour c){
        return {r*c.r, g*c.g, b*c.b};
    }

    Colour operator*(float k){
        return {r*k, g*k, b*k};
    }

    Colour operator/(float k){
        return {r/k, g/k, b/k};
    }
};

void setRGB(Colour* colour, float r, float g, float b);

bool isBlack(Colour colour);

struct Vector3D{
    float x, y, z;
    Vector3D& operator=(Vector3D v){
        x = v.x;
        y = v.y;
        z = v.z;
        return *this;
    }

    bool operator==(Vector3D v){
        return x == v.x && y == v.y && z == v.z;
    }

    Vector3D operator+(Vector3D v){
        return {x+v.x, y+v.y, z+v.z};
    }

    Vector3D operator-(Vector3D v){
        return {x-v.x, y-v.y, z-v.z};
    }

    float operator*(Vector3D v){
        // dot product
        return x*v.x + y*v.y + z*v.z;
    }

    Vector3D operator*(float c){
        return {x*c, y*c, z*c};
    }

    Vector3D operator^(Vector3D v){
        // cross product
        return {z*v.y - y*v.z, z*v.x-x*v.z, y*v.x - x*v.y};
    }

    Vector3D operator-(){
        return {-x, -y, -z};
    }
};

void setXYZ(Vector3D* vector, float x, float y, float z);
Vector3D normalize(Vector3D vector);
float magnitude(Vector3D vector);
float angleBetween(Vector3D u, Vector3D v);

// Ray Triangle Intersections
struct Matrix3D{
    float   a, b, c,
            d, e, f,
            g, h, i;
    Matrix3D& operator=(Matrix3D m){
        a = m.a; b = m.b; c = m.c;
        d = m.d; e = m.e; f = m.f;
        g = m.g; h = m.h; i = m.i;
        return *this;
    }
};

Matrix3D setColumn(Matrix3D, Vector3D col, int colId);

float determinant(Matrix3D mat);

struct Light{
    Colour c;
    Vector3D v;
};

struct SpotLight{
    Colour c;
    Vector3D p;
    Vector3D d;
    float angle1, angle2;
};


#endif //FRAYTRACER_COMPONENTS_H
