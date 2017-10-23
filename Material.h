//
// Created by debowin on 10/8/17.
//

#ifndef FRAYTRACER_MATERIAL_H
#define FRAYTRACER_MATERIAL_H


#include "Basics.h"

class Material {
    Colour ambient;
    Colour diffuse;
    Colour specular;
    Colour transmissive;
    float ns; // Phong cosine power for specular highlights.
    float ior; // Index of refraction
public:
    Material();

    void setMaterial(Colour a, Colour d, Colour s, Colour t, float ns, float ior);

    const Colour &getAmbient() const;

    Colour &getDiffuse();

    Colour &getSpecular();

    Colour &getTransmissive();

    float getNs() const;

    float getIor() const;
};


#endif //FRAYTRACER_MATERIAL_H
