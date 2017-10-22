#include <cstdio>
#include <iostream>
#include <sys/time.h>
#include "Scene.h"

using namespace std;

int main(int argc, char *argv[]){
    struct timeval tvalBefore{}, tvalAfter{};
    gettimeofday(&tvalBefore, nullptr);
    Scene scene;
    string fileName;
    if(argc!=2){
        cout << "Usage: fray-tracer <scene_file.scn>\n";
        return 1;
    }
    fileName = argv[1];
    if(scene.readSceneFile(fileName)!=0)
        return 2;
    scene.rayTrace();
    scene.writeImageResult();
    gettimeofday (&tvalAfter, nullptr);

    cout<<"Time Taken: "<< (tvalAfter.tv_sec-tvalBefore.tv_sec) + (tvalAfter.tv_usec - tvalBefore.tv_usec)/1000000.0f << " seconds." << endl;
    return 0;
}
