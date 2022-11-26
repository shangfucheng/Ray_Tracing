/**************************************************
 class “image” that contains the arrays of pixels where we store the colors.
*****************************************************/
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtx/rotate_normalized_axis.hpp>
#include <OpenGL/gl3.h>
#include <OpenGL/glext.h>
#include <GLUT/glut.h>
#include <vector>
#ifndef __IMAGE_H__
#define __IMAGE_H__

class Image {
public:
	int width, height;
	std::vector<glm::vec3> pixel;
	Image(int w, int h) {
		width = w;
		height = h;
	}
	void initialize();
	void draw();
private:
	unsigned int fbo; // frame buffer object
	unsigned int tbo; // texture buffer object
};

#endif 