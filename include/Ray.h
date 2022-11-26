/**************************************************
Ray class
*****************************************************/
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include "Intersection.h"
#ifndef __RAY_H__
#define __RAY_H__

// Ray trace core functions.
namespace RayTracer {
    void Raytrace(Camera cam, Scene scene, Image& image); //page 9
    Ray RayThruPixel(Camera cam, int i, int j, int width, int height);//page 10, 18
    Intersection Intersect(Ray ray, Triangle triangle); //page 30, 33
    Intersection Intersect(Ray ray, Scene scene); //page 11, 28, 31
    glm::vec3 FindColor(Intersection hit, int recursion_depth); //page 15
};

void RayTracer::Raytrace(Camera cam, Scene scene, Image& image) {
    int w = image.width; int h = image.height;
    for (int j = 0; j < h; j++) {
        for (int i = 0; i < w; i++) {
            Ray ray = RayThruPixel(cam, i, j, w, h);
            Intersection hit = Intersect(ray, scene);
            image.pixel[i][j] = FindColor(hit);
        }
    }

}

class Ray {
public:
    glm::vec3 p0; // basepoint
    glm::vec3 dir; // direction
};

#endif 
