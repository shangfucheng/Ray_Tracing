/**************************************************
Intersection class
*****************************************************/
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include "Triangle.h"
#include "RTScene.h"
#ifndef __INTERSECTION_H__
#define __INTERSECTION_H__

class Intersection {
public:
    glm::vec3 P; // position of the intersection
    glm::vec3 N; // surface normal
    glm::vec3 V; // direction to incoming ray
    Triangle* triangle; // pointer to geometric primitive (and material info)
    float dist; // distance to the source of ray
    float intersect; // 0 means no intersect, 1 means intersect
    Intersection() {
        P = glm::vec3(0);
        N = glm::vec3(0);
        V = glm::vec3(0);
        triangle = nullptr;
        dist = std::numeric_limits<float>::infinity();
        intersect = 0.0;
    }
};

#endif 
