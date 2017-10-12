#include <cstdio>
#include <iostream>
#include "Scene.h"

using namespace std;

int main(int argc, char *argv[]){
    Scene scene;
    string fileName;
    if(argc!=2){
        cout << "Usage: fray-tracer <scene_file.scn>\n";
        return 1;
    }
    fileName = argv[1];
    if(scene.readSceneFile(fileName)==1)
        return 2;
    scene.rayCast();
    scene.writeImageResult();
    return 0;
}
