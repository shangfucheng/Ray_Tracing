/**************************************************
RTScene class
*****************************************************/
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
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
#include "RTGeometry.h"
#include "Material.h"
#include "RTModel.h"

#ifndef __RTSCENE_H__
#define __RTSCENE_H__

class RTNode {
public:
    std::vector< RTNode* > childnodes;
    std::vector< glm::mat4 > childtransforms;
    std::vector< RTModel* > models;
    std::vector< glm::mat4 > modeltransforms;
};

class RTScene {
public:
    Camera* camera;
    SurfaceShader* shader;
    // The following are containers of objects serving as the object palettes.
    // The containers store pointers so that they can also store derived class objects.
    std::map< std::string, RTGeometry* > RTgeometry;
    std::map< std::string, Material* > RTmaterial;
    std::map< std::string, RTModel* > RTmodel;
    std::map< std::string, Light* > light;

    // The container of nodes will be the scene graph after we connect the nodes by setting the child_nodes.
    std::map< std::string, RTNode* > RTnode;
    std::vector<Triangle*> triangle_soup;//list of triangles in world or camera coordinate
    RTScene() {
        // the default scene graph already has one node named "world."
        RTnode["world"] = new RTNode;
    }
    // ~RTScene(){
    //     for(Triangle* tri :triangle_soup){
    //         delete tri;
    //     }
    // }
    void init(void);
    void buildTriangleSoup();

};

#endif 
