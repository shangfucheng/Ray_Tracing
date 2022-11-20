/**************************************************
 class “image” that contains the arrays of pixels where we store the colors.
*****************************************************/
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtx/rotate_normalized_axis.hpp>
#include <math.h>

#include <stdlib.h>
#include <vector>
#include <string>
#include <map>
#include <stack>

#include "Camera.h"
#include "SurfaceShader.h"
#include "Light.h"
#include "Geometry.h"
#include "Material.h"
#include "Model.h"
#ifndef __IMAGE_H__
#define __IMAGE_H__

class Image{
public:
    int width;
    int height;
    std::vector<glm::vec3> pixels; // RGB colors;
    Image(const int w, const int h){
        width = w;
        height = h;
        // pixels(w*h, 0.f);
    }
    ~Image(){
        pixels.clear();
    }

    void init();
    void draw();
    
private:

    unsigned int fbo; // framebuffer object
    unsigned int tbo; // texture buffer object
};

#endif