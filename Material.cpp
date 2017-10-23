//
// Created by debowin on 10/8/17.
//

#include "Material.h"

Material::Material() {
    setRGB(&ambient, 0, 0, 0);
    setRGB(&diffuse, 1, 1, 1);
    setRGB(&specular, 0, 0, 0);
    setRGB(&transmissive, 0, 0, 0);
    ns = 5;
    ior = 1;
}

void Material::setMaterial(Colour a, Colour d, Colour s, Colour t, float ns_, float ior_) {
    ambient = a;
    diffuse = d;
    specular = s;
    transmissive = t;
    ns = ns_;
    ior = ior_;
}

const Colour &Material::getAmbient() const {
    return ambient;
}

Colour &Material::getDiffuse() {
    return diffuse;
}

Colour &Material::getSpecular() {
    return specular;
}

Colour &Material::getTransmissive() {
    return transmissive;
}

float Material::getNs() const {
    return ns;
}

float Material::getIor() const {
    return ior;
}
