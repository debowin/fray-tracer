//
// Created by debowin on 10/8/17.
//

#include <fstream>
#include <iostream>
#include <cmath>
#include "Scene.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "stb_image_write.h"

int Scene::readSceneFile(string fileName) {
    string line;

    // open the file containing the scene description
    ifstream input(fileName);

    // check for errors in opening the file
    if (input.fail()) {
        cout << "Can't open file '" << fileName << "'" << endl;
        return 1;
    }

    Material material;
    output_image = "raytraced.bmp";
    maxDepth = 5;

    //Loop through reading each line
    string command;
    while (input >> command) { //Read first word in the line (i.e., the command type)

        if (command[0] == '#') {
            getline(input, line); //skip rest of line
            cout << "Skipping comment: " << command << line << endl;
            continue;
        }

        if (command == "material") { //If the command is a material command
            Colour a{}, d{}, s{}, t{};
            float ns, ior;
            input >> a.r >> a.g >> a.b >> d.r >> d.g >> d.b >> s.r >> s.g >> s.b >> ns >> t.r >> t.g >> t.b >> ior;
            material.setMaterial(a, d, s, t, ns, ior);
            printf("Material configuration changed to a(%f,%f,%f), d(%f,%f,%f), s(%f,%f,%f), t(%f,%f,%f), ns %f and ior %f.\n",
                   a.r, a.g, a.b, d.r, d.g, d.b, s.r, s.g, s.b, t.r, t.g, t.b, ns, ior);
        } else if (command == "camera") { //If the command is a camera command
            float ha;
            Vector p{}, d{}, u{};
            input >> p.x >> p.y >> p.z >> d.x >> d.y >> d.z >> u.x >> u.y >> u.z >> ha;
            camera.setCamera(p, d, u, ha);
            printf("Camera at position (%f,%f,%f) with view direction (%f,%f,%f), up (%f,%f,%f) and half angle %f.\n",
                   p.x, p.y, p.z, d.x, d.y, d.z, u.x, u.y, u.z, ha);
        } else if (command == "sphere") { //If the command is a sphere command
            float r;
            Vector p{};
            input >> p.x >> p.y >> p.z >> r;
            Sphere sphere(p, r, material);
            spheres.push_back(sphere);
            printf("Sphere at position (%f,%f,%f) with radius %f.\n", p.x, p.y, p.z, r);
        } else if (command == "background") { //If the command is a background command
            float r, g, b;
            input >> r >> g >> b;
            setRGB(&background, r, g, b);
            printf("Background color of (%f,%f,%f).\n", r, g, b);
        } else if (command == "ambient_light") { //If the command is an ambient_light command
            Colour a{};
            input >> a.r >> a.g >> a.b;
            ambientLight.c = a;
            printf("Ambient Light color of (%f,%f,%f).\n", a.r, a.g, a.b);
        } else if (command == "point_light") { //If the command is an point_light command
            Colour c{};
            Vector p{};
            input >> c.r >> c.g >> c.b >> p.x >> p.y >> p.z;
            Light pointLight{c, p};
            pointLights.push_back(pointLight);
            printf("Point Light added at (%f, %f, %f) with color of (%f,%f,%f).\n", p.x, p.y, p.z, c.r, c.g, c.b);
        } else if (command == "output_image") { //If the command is an output_image command
            string outFile;
            input >> outFile;
            output_image = outFile;
            printf("Render to file named: %s\n", outFile.c_str());
        } else if (command == "film_resolution") { //If the command is a film_resolution command
            int width, height;
            input >> width >> height;
            camera.setFilm(width, height);
            printf("Set film resolution as: %d x %d.\n", width, height);
        } else if (command == "max_depth") { //If the command is a max_depth command
            input >> maxDepth;
            printf("Set maximum depth as: %d.\n", maxDepth);
        } else {
            getline(input, line); //skip rest of line
            cout << "WARNING. Do not know command: " << command << endl;
        }
    }
}


void Scene::writeImageResult() {
    stbi_write_bmp(output_image.c_str(), camera.getFilmWidth(), camera.getFilmHeight(), 4, data.raw);
}

void Scene::initializeFilm(Component r, Component g, Component b, Component a) {
    int num_pixels = camera.getFilmWidth() * camera.getFilmHeight();

    data.raw = new uint8_t[num_pixels * 4];
    int byte = 0; // byte to write to
    for (int i = 0; i < camera.getFilmWidth(); ++i) {
        for (int j = 0; j < camera.getFilmHeight(); ++j) {
            data.raw[byte++] = r;
            data.raw[byte++] = g;
            data.raw[byte++] = b;
            data.raw[byte++] = a;
        }
    }
}

void Scene::rayTrace() {
    initializeFilm(0, 0, 0, 255);
    Ray viewingRay;
    for (int j = 0; j < camera.getFilmHeight(); ++j) {
        for (int i = 0; i < camera.getFilmWidth(); ++i) {
            viewingRay = camera.getRay(i, j);
            data.pixels[(camera.getFilmHeight() - 1 - j) * camera.getFilmWidth() + i] = Pixel(getColour(viewingRay, maxDepth));
        }
    }
}

HitInfo* Scene::hit(Ray viewingRay, float tMin, float tMax){
    float tBest = INFINITY;
    HitInfo* hitBest = nullptr;
    for (auto sphere : spheres) {
        HitInfo *hitInfo = sphere.intersect(viewingRay, tMin, tMax);
        if (hitInfo != nullptr && hitInfo->getT() < tBest) {
            hitBest = hitInfo;
            tBest = hitInfo->getT();
        }
    }
    return hitBest;
}


Colour Scene::getColour(Ray viewingRay, int depth) {
    HitInfo *hitBest = hit(viewingRay, 0.01, INFINITY);
    if(hitBest!=nullptr) {
        Colour finalColour = ambientLight.c * hitBest->getMaterial().getAmbient();
        for (auto light : pointLights) {
            Vector lambertian = light.v - hitBest->getPoint();
            HitInfo *shadowHit = hit(Ray(hitBest->getPoint(), normalize(lambertian)), 0.01, magnitude(lambertian));
            if (shadowHit == nullptr) {
                Colour fallOffIntensity = light.c / pow(magnitude(lambertian), 2);
                Vector half = lambertian - hitBest->getD();
                // diffuse shading
                finalColour =
                        finalColour + fallOffIntensity * fmaxf(0.0, normalize(lambertian) * hitBest->getNormal())
                                        * hitBest->getMaterial().getDiffuse();
                // specular shading
                finalColour = finalColour + fallOffIntensity *
                                                  pow(fmaxf(0.0, normalize(half) * hitBest->getNormal()),
                                                      hitBest->getMaterial().getNs())
                                                  * hitBest->getMaterial().getSpecular();
            }
        }
        // ideal specular reflection
        if(!isBlack(hitBest->getMaterial().getSpecular()) && depth > 1) {
            Vector reflected = hitBest->getD() - hitBest->getNormal() * 2 * (hitBest->getD() * hitBest->getNormal());
            finalColour = finalColour + hitBest->getMaterial().getSpecular() *
                                        getColour(Ray(hitBest->getPoint(), normalize(reflected)), depth - 1);
        }
        return finalColour;
    }
    return background;
}
