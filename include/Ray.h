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
    void Raytrace(Camera* cam, RTScene &RTscene, Image& image); 
    Ray RayThruPixel(Camera* cam, int i, int j, int width, int height);
    Intersection Intersect_Triangle(Ray ray, Triangle& triangle); 
    Intersection Intersect_Scene(Ray ray, RTScene &RTscene); 
    glm::vec3 FindColor(RTScene &RTscene, Intersection hit, int recursion_depth); 
};

#endif 
