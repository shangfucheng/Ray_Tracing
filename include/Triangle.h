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
		this->P[0] = glm::vec3(modelView*glm::vec4(this->P[0],1));
        this->P[1] = glm::vec3(modelView*glm::vec4(this->P[1],1));
        this->P[2] = glm::vec3(modelView*glm::vec4(this->P[2],1));
		this->N[0] = glm::normalize(glm::inverse(glm::transpose(glm::mat3(modelView)))*this->N[0]);
		this->N[1] = glm::normalize(glm::inverse(glm::transpose(glm::mat3(modelView)))*this->N[1]);
		this->N[2] = glm::normalize(glm::inverse(glm::transpose(glm::mat3(modelView)))*this->N[2]);
	}
};
#endif