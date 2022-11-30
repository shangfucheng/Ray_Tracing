/**************************************************
Image.cpp contains the implementation Image class
*****************************************************/
#include "Image.h"
#include <iostream>
#include <vector>

void Image::initialize() {
	pixel = std::vector<glm::vec3>(width*height,glm::vec3(0.f));
	std::cout << "pixel size: " << pixel.size() << std::endl;
	// pixel = std::vector<std::vector<glm::vec3>>(width, std::vector<glm::vec3>(height,glm::vec3(1.0f)));
	// std::cout << "pixel size: " << pixel.size() << " x " << pixel[0].size() << std::endl;
	glGenFramebuffers(1, &fbo);
	glGenTextures(1, &tbo);
}

void Image::draw() {
	glBindTexture(GL_TEXTURE_2D, tbo);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, // load texture
		0, GL_RGB, GL_FLOAT, &pixel[0][0]);
	glBindFramebuffer(GL_READ_FRAMEBUFFER, fbo);
	glFramebufferTexture2D(GL_READ_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
		GL_TEXTURE_2D, tbo, 0);// attach texture and the read frame
	glBlitFramebuffer(0, 0, width, height, 0, 0, width, height, GL_COLOR_BUFFER_BIT,
		GL_NEAREST); // copy framebuffer from read to write
}
