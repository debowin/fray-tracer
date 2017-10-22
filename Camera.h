//
// Created by debowin on 10/8/17.
//

#ifndef FRAYTRACER_CAMERA_H
#define FRAYTRACER_CAMERA_H

#include "Basics.h"
#include "Ray.h"

class Camera {
    Vector3D position;
    Vector3D towards;
    Vector3D up;
    Vector3D right;
    float ha; // Half angle for height of viewing frustum.
    float wa; // Half angle for width of viewing frustum.
    float focalLength;
    int filmWidth;
public:
    int getFilmWidth() const;

    int getFilmHeight() const;

private:
    int filmHeight;

public:
    Camera();
    void setCamera(Vector3D p, Vector3D d, Vector3D u, float ha);
    void setFilm(int width, int height);
    Ray getRay(float ix, float iy);
};


#endif //FRAYTRACER_CAMERA_H
