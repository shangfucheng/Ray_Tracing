/**************************************************
Ray class
*****************************************************/
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include "Intersection.h"
#include "Image.h"
#include <limits>
#ifndef __RAY_H__
#define __RAY_H__

class Ray {
public:
    glm::vec3 p0; // basepoint, ray source position
    glm::vec3 dir; // ray direction
};

// Ray trace core functions.
namespace RayTracer {
    void Raytrace(Camera cam, RTScene scene, Image& image); //page 9
    Ray RayThruPixel(Camera cam, int i, int j, int width, int height);//page 10, 18
    Intersection Intersect_Triangle(Ray ray, Triangle* triangle); //page 30, 33
    Intersection Intersect_Scene(Ray ray, RTScene RTscene); //page 11, 28, 31
    glm::vec3 FindColor(RTScene RTscene, Intersection &hit, int recursion_depth); //page 15
};

#endif 
