/**************************************************
Intersection class
*****************************************************/
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include "Triangle.h"
#include "Ray.h"
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
    Intersection(Ray ray, RTScene scene) {
        float mindist = INFINITY;
        Intersection hit;
        foreach(object in scene) { // Find closest intersection; test all objects
            Intersection hit_temp = Intersect(ray, object);
            if (hit_temp.dist < mindist) { // closer than previous hit
                mindist = hit_temp.dist;
                hit = hit_temp;
            }
        }
        return hit;
    }
};

#endif 
