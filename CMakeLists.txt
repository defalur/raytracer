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
        src/materials/texturematerial.h
        src/materials/uniformtexture.cpp
        src/materials/uniformtexture.h
        src/utils/color.cpp
        src/scene/sceneobject.h
        src/scene/sphere.cpp
        src/scene/sphere.h
        src/utils/utils.h
        src/scene/light.h
        src/scene/pointlight.cpp
        src/scene/pointlight.h
        src/scene/camera.cpp
        src/scene/camera.h
        src/utils/raycastHit.h
        src/utils/Matrix.h
        src/scene.cpp
        src/scene.h
        src/shader/shader.cpp
        src/shader/shader.h src/utils/utils.cpp src/shader/hitcontext.cpp src/shader/hitcontext.h src/shader/shaderengine.cpp src/shader/shaderengine.h src/shader/diffuseshader.cpp src/shader/diffuseshader.h src/shader/specularshader.cpp src/shader/specularshader.h src/shader/reflectionshader.cpp src/shader/reflectionshader.h src/scene/triangle.cpp src/scene/triangle.h src/shader/ambientshader.cpp src/shader/ambientshader.h src/shader/transparencyshader.cpp src/shader/transparencyshader.h src/fileutils/scenereader.cpp src/fileutils/scenereader.h)

target_include_directories(raytracer PRIVATE
        ${CMAKE_SOURCE_DIR}/src)