cmake_minimum_required(VERSION 3.16)
project(raytracer)

set(CMAKE_CXX_STANDARD 17)


add_executable(raytracer src/main.cpp
        src/utils/color.h
        src/utils/vector3.cpp
        src/utils/vector3.h
        src/utils/vector4.cpp
        src/utils/vector4.h
        src/utils/image.cpp
        src/utils/image.h
        src/texturematerial.h
        src/uniformtexture.cpp
        src/uniformtexture.h
        src/utils/color.cpp
        src/scene/sceneobject.h
        src/scene/sphere.cpp src/scene/sphere.h src/utils/utils.h src/scene/light.h src/scene/pointlight.cpp src/scene/pointlight.h)

target_include_directories(raytracer PRIVATE
        ${CMAKE_SOURCE_DIR}/src)