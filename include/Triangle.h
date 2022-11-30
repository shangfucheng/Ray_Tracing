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
	void position_update( glm::mat4 modelView){
		P[0] = glm::normalize(glm::mat3(glm::inverse(modelView))*P[0]);
        P[1] = glm::normalize(glm::mat3(glm::inverse(modelView))*P[1]);
        P[2] = glm::normalize(glm::mat3(glm::inverse(modelView))*P[2]);
		N[0] = glm::normalize(glm::inverse(glm::transpose(glm::mat3(modelView)))*N[0]);
		N[1] = glm::normalize(glm::inverse(glm::transpose(glm::mat3(modelView)))*N[1]);
		N[2] = glm::normalize(glm::inverse(glm::transpose(glm::mat3(modelView)))*N[2]);
	}
};
#endif