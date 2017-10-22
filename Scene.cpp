//
// Created by debowin on 10/8/17.
//

#include <fstream>
#include <iostream>
#include <cmath>
#include <random>
#include "Scene.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "stb_image_write.h"
#include "Triangle.h"

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
    maxNormals = -1;
    maxVertices = -1;
    samplingMethod = JITTERED;
    samplingRate = 3;

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
            printf("Material configuration changed to a(%f, %f, %f), d(%f, %f, %f), s(%f, %f, %f), t(%f, %f, %f), ns %f and ior %f.\n",
                   a.r, a.g, a.b, d.r, d.g, d.b, s.r, s.g, s.b, t.r, t.g, t.b, ns, ior);
        } else if (command == "camera") { //If the command is a camera command
            float ha;
            Vector3D p{}, d{}, u{};
            input >> p.x >> p.y >> p.z >> d.x >> d.y >> d.z >> u.x >> u.y >> u.z >> ha;
            camera.setCamera(p, d, u, ha);
            printf("Camera at position (%f, %f, %f) with view direction (%f, %f, %f), up (%f, %f, %f) and half angle %f.\n",
                   p.x, p.y, p.z, d.x, d.y, d.z, u.x, u.y, u.z, ha);
        } else if (command == "sphere") { //If the command is a sphere command
            float r;
            Vector3D p{};
            input >> p.x >> p.y >> p.z >> r;
            auto sphere = (Surface*)new Sphere(p, r, material);
            surfaces.push_back(sphere);
            printf("Sphere at position (%f, %f, %f) with radius %f.\n", p.x, p.y, p.z, r);
        } else if (command == "triangle") { //If the command is a triangle command
            int v1, v2, v3;
            input >> v1 >> v2 >> v3;
            auto triangle = (Surface*)new Triangle(vertices[v1], vertices[v2], vertices[v3], material);
            surfaces.push_back(triangle);
            printf("Triangle using vertices (%d, %d, %d).\n", v1, v2, v3);
        } else if (command == "normal_triangle") { //If the command is a normal_triangle command
            int v1, v2, v3, n1, n2, n3;
            input >> v1 >> v2 >> v3 >> n1 >> n2 >> n3;
            auto triangle = (Surface*)new Triangle(vertices[v1], vertices[v2], vertices[v3],
                              normals[n1], normals[n2], normals[n3], material);
            surfaces.push_back(triangle);
            printf("Triangle using vertices (%d, %d, %d) and normals (%d, %d, %d).\n", v1, v2, v3, n1, n2, n3);
        } else if (command == "vertex") { //If the command is a vertex command
            if (maxVertices < 0) {
                cout << "max_vertices should be specified before vertex." << endl;
                return 2;
            }
            Vector3D p{};
            input >> p.x >> p.y >> p.z;
            vertices.push_back(p);
            printf("Vertex #%ld at position (%f, %f, %f).\n", vertices.size(), p.x, p.y, p.z);
        } else if (command == "normal") { //If the command is a normal command
            if (maxNormals < 0) {
                cout << "max_normals should be specified before normal." << endl;
                return 2;
            }
            Vector3D d{};
            input >> d.x >> d.y >> d.z;
            normals.push_back(d);
            printf("Normal #%ld in direction (%f, %f, %f).\n", normals.size(), d.x, d.y, d.z);
        } else if (command == "background") { //If the command is a background command
            float r, g, b;
            input >> r >> g >> b;
            setRGB(&background, r, g, b);
            printf("Background color of (%f, %f, %f).\n", r, g, b);
        } else if (command == "ambient_light") { //If the command is an ambient_light command
            Colour a{};
            input >> a.r >> a.g >> a.b;
            ambientLight.c = a;
            printf("Ambient Light color of (%f, %f, %f).\n", a.r, a.g, a.b);
        } else if (command == "point_light") { //If the command is a point_light command
            Colour c{};
            Vector3D p{};
            input >> c.r >> c.g >> c.b >> p.x >> p.y >> p.z;
            Light pointLight{c, p};
            pointLights.push_back(pointLight);
            printf("Point Light added at (%f, %f, %f) with color of (%f, %f, %f).\n", p.x, p.y, p.z, c.r, c.g, c.b);
        } else if (command == "directional_light") { //If the command is a directional_light command
            Colour c{};
            Vector3D v{};
            input >> c.r >> c.g >> c.b >> v.x >> v.y >> v.z;
            Light directionalLight{c, v};
            directionalLights.push_back(directionalLight);
            printf("Directional Light added in direction (%f, %f, %f) with color of (%f, %f, %f).\n", v.x, v.y, v.z,
                   c.r, c.g, c.b);
        } else if (command == "spot_light") { //If the command is a spot_light command
            Colour c{};
            Vector3D v{};
            Vector3D p{};
            float a1, a2;
            input >> c.r >> c.g >> c.b >> p.x >> p.y >> p.z >> v.x >> v.y >> v.z >> a1 >> a2;
            SpotLight spotLight{c, p, v, a1, a2};
            spotLights.push_back(spotLight);
            printf("Spot Light added at (%f, %f, %f) in direction (%f, %f, %f) with color of (%f, %f, %f) and angles (%f, %f).\n",
                   p.x, p.y, p.z, v.x, v.y, v.z, c.r, c.g, c.b, a1, a2);
        } else if (command == "max_vertices"){ // If the command is a max_vertices command
            input >> maxVertices;
        } else if (command == "max_normals"){ // If the command is a max_normals command
            input >> maxNormals;
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
    return 0;
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
#pragma omp parallel for
    for (int j = 0; j < camera.getFilmHeight(); ++j) {
        for (int i = 0; i < camera.getFilmWidth(); ++i) {
            Colour pixelColour{};
            switch (samplingMethod) {
                case BASIC:
                    pixelColour = basicSampling(i, j);
                    break;
                case REGULAR:
                    pixelColour = regularSampling(i, j);
                    break;
                case RANDOM:
                    pixelColour = randomSampling(i, j);
                    break;
                case JITTERED:
                    pixelColour = jitteredSampling(i, j);
                    break;
            }
            data.pixels[(camera.getFilmHeight() - 1 - j) * camera.getFilmWidth() + i] = Pixel(pixelColour);
        }
    }
}

HitInfo *Scene::hit(Ray viewingRay, float tMin, float tMax) {
    float tBest = INFINITY;
    HitInfo *hitBest = nullptr;
    for (const auto &surface : surfaces) {
        HitInfo *hitInfo = surface->intersect(viewingRay, tMin, tMax);
        if (hitInfo != nullptr && hitInfo->getT() < tBest) {
            hitBest = hitInfo;
            tBest = hitInfo->getT();
        }
    }
    return hitBest;
}


Colour Scene::getColour(Ray viewingRay, int depth) {
    HitInfo *hitBest = hit(viewingRay, 0.01, INFINITY);
    if (hitBest != nullptr) {
        Colour finalColour = ambientLight.c * hitBest->getMaterial().getAmbient();
        for (auto light : pointLights) {
            Vector3D lambertian = light.v - hitBest->getPoint();
            HitInfo *shadowHit = hit(Ray(hitBest->getPoint(), normalize(lambertian)), 0.01, magnitude(lambertian));
            if (shadowHit == nullptr) {
                // quadratic falloff
                Colour fallOffIntensity = light.c / pow(magnitude(lambertian), 2);
                Vector3D half = lambertian - hitBest->getD();
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
        for (auto light: directionalLights) {
            Vector3D lambertian = -light.v;
            HitInfo *shadowHit = hit(Ray(hitBest->getPoint(), normalize(lambertian)), 0.01, INFINITY);
            if (shadowHit == nullptr) {
                // no falloff
                Vector3D half = lambertian - hitBest->getD();
                // diffuse shading
                finalColour =
                        finalColour + light.c * fmaxf(0.0, normalize(lambertian) * hitBest->getNormal())
                                      * hitBest->getMaterial().getDiffuse();
                // specular shading
                finalColour = finalColour + light.c *
                                            pow(fmaxf(0.0, normalize(half) * hitBest->getNormal()),
                                                hitBest->getMaterial().getNs())
                                            * hitBest->getMaterial().getSpecular();
            }
        }
        for(auto light: spotLights){
            Vector3D lambertian = light.p - hitBest->getPoint();
            HitInfo *shadowHit = hit(Ray(hitBest->getPoint(), normalize(lambertian)), 0.01, magnitude(lambertian));
            if (shadowHit == nullptr) {
                // angle based linear falloff
                float angle = angleBetween(-lambertian, light.d);
                Colour fallOffIntensity = light.c;
                if(angle>light.angle2)
                    continue;
                else if(angle>=light.angle1){
                    float factor = 1 - (angle-light.angle1)/(light.angle2-light.angle1);
                    fallOffIntensity = fallOffIntensity * factor;
                }
                fallOffIntensity = fallOffIntensity / pow(magnitude(lambertian), 2);
                Vector3D half = lambertian - hitBest->getD();
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
        if (!isBlack(hitBest->getMaterial().getSpecular()) && depth > 1) {
            Vector3D reflected = hitBest->getD() - hitBest->getNormal() * 2 * (hitBest->getD() * hitBest->getNormal());
            finalColour = finalColour + hitBest->getMaterial().getSpecular() *
                                        getColour(Ray(hitBest->getPoint(), normalize(reflected)), depth - 1);
        }
        return finalColour;
    }
    return background;
}

Colour Scene::basicSampling(int i, int j) {
    Ray viewingRay = camera.getRay(i + 0.5f, j + 0.5f);
    return getColour(viewingRay, maxDepth);
}

Colour Scene::regularSampling(int i, int j) {
    Colour c{0.0f, 0.0f, 0.0f};
    for (int p = 0; p < samplingRate; p++) {
        for (int q = 0; q < samplingRate; q++) {
            Ray viewingRay = camera.getRay(i + (p + 0.5f) / samplingRate, j + (q + 0.5f) / samplingRate);
            c = c + getColour(viewingRay, maxDepth);
        }
    }
    return c / pow(samplingRate, 2);
}

Colour Scene::randomSampling(int i, int j) {
    Colour c{0.0f, 0.0f, 0.0f};
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<float> dist(0.0, 1.0);
    for (int p = 0; p < pow(samplingRate, 2); p++) {
        Ray viewingRay = camera.getRay(i + dist(mt), j + dist(mt));
        c = c + getColour(viewingRay, maxDepth);
    }
    return c / pow(samplingRate, 2);
}

Colour Scene::jitteredSampling(int i, int j) {
    Colour c{0.0f, 0.0f, 0.0f};
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<float> dist(0.0, 1.0);
#pragma omp parallel for
    for (int p = 0; p < samplingRate; p++) {
        for (int q = 0; q < samplingRate; q++) {
            Ray viewingRay = camera.getRay(i + (p + dist(mt)) / samplingRate, j + (q + dist(mt)) / samplingRate);
            c = c + getColour(viewingRay, maxDepth);
        }
    }
    return c / pow(samplingRate, 2);
}
