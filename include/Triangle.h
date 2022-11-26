/**************************************************
Triangle class that stores will contain 3 point coordinates,
3 normal vectors, and a pointer to material. 
*****************************************************/
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <vector>
#include "Material.h"
#ifndef __TRIANGLE_H__
#define __TRIANGLE_H__
struct Triangle {
	std::vector<glm::vec3> P; // 3 positions
	std::vector<glm::vec3> N; // 3 normals
	Material* material = NULL;
};
#endif