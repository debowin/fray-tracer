//
// Created by debowin on 10/8/17.
//

#ifndef FRAYTRACER_SCENE_H
#define FRAYTRACER_SCENE_H

#include <string>
#include <vector>
#include "Camera.h"
#include "Sphere.h"
#include "Basics.h"
#include "Material.h"
#include "Pixel.h"
#include "HitInfo.h"

using namespace std;



class Scene {
    union PixelData{
        Pixel *pixels;
        uint8_t *raw;
    };

    PixelData data;
    Camera camera;
    string output_image;
    Colour background;
    vector<Sphere> spheres;
    vector<Light> directionalLights;
    vector<Light> pointLights;
    vector<SpotLight> spotLights;
    Light ambientLight;
    int maxDepth;

public:
    int readSceneFile(string fileName);
    void initializeFilm(Component r, Component g, Component b, Component a);
    void writeImageResult();
    void rayCast();
    HitInfo* hit(Ray viewingRay, float tMin, float fMax);

    Colour getColour(Ray viewingRay, int depth);
};


#endif //FRAYTRACER_SCENE_H
