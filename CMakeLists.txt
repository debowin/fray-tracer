cmake_minimum_required(VERSION 3.5)
project(FrayTracer)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        main.cpp
        stb_image.h
        stb_image_write.h
        main.cpp
        Scene.cpp
        Scene.h
        Sphere.h
        Sphere.cpp
        Camera.cpp
        Camera.h
        Material.cpp
        Material.h
        Basics.h
        Basics.cpp
        Pixel.h
        Ray.cpp
        Ray.h
        HitInfo.cpp
        HitInfo.h)

add_executable(fray-tracer ${SOURCE_FILES})