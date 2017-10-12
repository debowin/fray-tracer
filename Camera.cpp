//
// Created by debowin on 10/8/17.
//

#include <cmath>
#include "Camera.h"

Camera::Camera() {
    setXYZ(&position, 0, 0, 0);
    setXYZ(&towards, 0, 0, 1);
    setXYZ(&up, 0, 1, 0);
    ha = 45;
    filmWidth = 640;
    filmHeight = 480;
    // focal length
    focalLength = filmHeight/(2 * std::tan(ha*(float)M_PI/180));
    //width angle
    wa = (float)(atan2(filmWidth/2, focalLength) * 180/M_PI);
    // right vector
    right = towards ^ up;
}

void Camera::setCamera(Vector p, Vector d, Vector u, float ha_) {
    position = p;
    towards = d;
    up = u;
    ha = ha_;
    // focal length
    focalLength = filmHeight/(2 * std::tan(ha*(float)M_PI/180));
    //width angle
    wa = (float)(atan2(filmWidth/2, focalLength) * 180/M_PI);
    // right vector
    right = towards ^ up;
}

void Camera::setFilm(int width, int height){
    filmWidth = width;
    filmHeight = height;
    // focal length
    focalLength = filmHeight/(2 * std::tan(ha*(float)M_PI/180));
    //width angle
    wa = (float)(atan2(filmWidth/2, focalLength) * 180/M_PI);
}

int Camera::getFilmWidth() const {
    return filmWidth;
}

int Camera::getFilmHeight() const {
    return filmHeight;
}

Ray Camera::getRay(int ix, int iy) {
    Vector direction{};
    Vector u{}, v{};

    Vector pRight{}, pLeft{}, pTop{}, pBottom{};

    pLeft = position + towards * focalLength - right * (filmWidth/2);
    pRight = position + towards * focalLength + right * (filmWidth/2);

    pBottom = position + towards * focalLength - up * (filmHeight/2);
    pTop = position + towards * focalLength + up * (filmHeight/2);

    u = pLeft + (pRight - pLeft)*((ix+0.5f)/filmWidth);
    v = pBottom + (pTop - pBottom)*((iy+0.5f)/filmHeight);

    // d = s - p
    direction = u + v - towards*focalLength - position;

    return {position, normalize(direction)};
}
