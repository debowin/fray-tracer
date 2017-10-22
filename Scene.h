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
    vector<Surface*> surfaces;
    vector<Light> directionalLights;
    vector<Light> pointLights;
    vector<SpotLight> spotLights;
    Light ambientLight;
    int maxDepth;
    int maxVertices;
    int maxNormals;
    vector<Vector3D> vertices;
    vector<Vector3D> normals;
    int samplingRate;
    enum SamplingMethod{
        BASIC=0,
        REGULAR=1,
        RANDOM=2,
        JITTERED=3
    } samplingMethod;

public:
    int readSceneFile(string fileName);
    void initializeFilm(Component r, Component g, Component b, Component a);
    void writeImageResult();
    void rayTrace();
    HitInfo* hit(Ray viewingRay, float tMin, float fMax);

    Colour getColour(Ray viewingRay, int depth);

    Colour basicSampling(int i, int j);

    Colour regularSampling(int i, int j);

    Colour randomSampling(int i, int j);

    Colour jitteredSampling(int i, int j);
};


#endif //FRAYTRACER_SCENE_H
