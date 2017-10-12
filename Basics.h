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

struct Vector{
    float x, y, z;
    Vector& operator=(Vector v){
        x = v.x;
        y = v.y;
        z = v.z;
        return *this;
    }

    Vector operator+(Vector v){
        return {x+v.x, y+v.y, z+v.z};
    }

    Vector operator-(Vector v){
        return {x-v.x, y-v.y, z-v.z};
    }

    float operator*(Vector v){
        // dot product
        return x*v.x + y*v.y + z*v.z;
    }

    Vector operator*(float c){
        return {x*c, y*c, z*c};
    }

    Vector operator^(Vector v){
        // cross product
        return {z*v.y - y*v.z, z*v.x-x*v.z, y*v.x - x*v.y};
    }

    Vector operator-(){
        return {-x, -y, -z};
    }
};

void setXYZ(Vector* vector, float x, float y, float z);
Vector normalize(Vector vector);
float magnitude(Vector vector);

struct Light{
    Colour c;
    Vector v;
};

struct SpotLight{
    Colour c;
    Vector p;
    Vector d;
    float angle1, angle2;
};


#endif //FRAYTRACER_COMPONENTS_H
