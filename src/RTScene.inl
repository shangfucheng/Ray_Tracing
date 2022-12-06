/**************************************************
RTScene.inl contains the definition of the scene graph
*****************************************************/
#include "RTScene.h"
#include "RTCube.h"
#include "RTObj.h"
#include "RTModel.h"

using namespace glm;
void RTScene::init(void) {
    // Create a geometry palette
    RTgeometry["cube"] = new RTCube;
    RTgeometry["teapot"] = new RTObj;
    // RTgeometry["bunny"] = new RTObj;
    RTgeometry["cube"]->init();
    RTgeometry["teapot"]->init("models/teapot.obj");// 2464 triangles
    // RTgeometry["bunny"]->init("models/bunny.obj"); // 28576 triangles

    // Create a material palette
    RTmaterial["wood"] = new Material;
    RTmaterial["wood"]->ambient = vec4(0.1f, 0.1f, 0.1f, 1.0f);
    RTmaterial["wood"]->diffuse = vec4(0.3f, 0.15f, 0.1f, 1.0f);
    RTmaterial["wood"]->specular = vec4(0.3f, 0.15f, 0.1f, 1.0f);
    RTmaterial["wood"]->shininess = 100.0f;

    RTmaterial["ceramic"] = new Material;
    RTmaterial["ceramic"]->ambient = vec4(0.02f, 0.07f, 0.2f, 1.0f);
    RTmaterial["ceramic"]->diffuse = vec4(0.1f, 0.25f, 0.7f, 1.0f);
    RTmaterial["ceramic"]->specular = vec4(0.9f, 0.9f, 0.9f, 1.0f);
    RTmaterial["ceramic"]->shininess = 150.0f;

    RTmaterial["silver"] = new Material;
    RTmaterial["silver"]->ambient = vec4(0.1f, 0.1f, 0.1f, 1.0f);
    RTmaterial["silver"]->diffuse = vec4(0.2f, 0.2f, 0.2f, 1.0f);
    RTmaterial["silver"]->specular = vec4(0.9f, 0.9f, 0.9f, 1.0f);
    RTmaterial["silver"]->shininess = 50.0f;

    RTmaterial["turquoise"] = new Material;
    RTmaterial["turquoise"]->ambient = vec4(0.1f, 0.2f, 0.17f, 1.0f);
    RTmaterial["turquoise"]->diffuse = vec4(0.2f, 0.375f, 0.35f, 1.0f);
    RTmaterial["turquoise"]->specular = vec4(0.3f, 0.3f, 0.3f, 1.0f);
    RTmaterial["turquoise"]->shininess = 100.0f;

    RTmaterial["bulb"] = new Material;
    RTmaterial["bulb"]->ambient = vec4(0.5f, 0.5f, 0.0f, 1.0f);
    RTmaterial["bulb"]->diffuse = vec4(0.5f, 0.5f, 0.0f, 1.0f);
    RTmaterial["bulb"]->specular = vec4(1.0f, 1.0f, 1.0f, 1.0f);
    RTmaterial["bulb"]->emision = vec4(1.0f, 0.2f, 0.1f, 1.0f);
    RTmaterial["bulb"]->shininess = 300.0f;

    //Create a model palette
    RTmodel["teapot1"] = new RTModel;
    RTmodel["teapot1"]->RTgeometry = RTgeometry["teapot"];
    RTmodel["teapot1"]->material = RTmaterial["turquoise"];
    RTmodel["teapot2"] = new RTModel;
    RTmodel["teapot2"]->RTgeometry = RTgeometry["teapot"];
    RTmodel["teapot2"]->material = RTmaterial["silver"];
    RTmodel["table piece"] = new RTModel;
    RTmodel["table piece"]->RTgeometry = RTgeometry["cube"];
    RTmodel["table piece"]->material = RTmaterial["wood"];

    RTmodel["left wall"] = new RTModel;
    RTmodel["left wall"]->RTgeometry = RTgeometry["cube"];
    RTmodel["left wall"]->material = RTmaterial["silver"];

    RTmodel["right wall"] = new RTModel;
    RTmodel["right wall"]->RTgeometry = RTgeometry["cube"];
    RTmodel["right wall"]->material = RTmaterial["ceramic"];

    RTmodel["back wall"] = new RTModel;
    RTmodel["back wall"]->RTgeometry = RTgeometry["cube"];
    RTmodel["back wall"]->material = RTmaterial["turquoise"];

    RTmodel["top wall"] = new RTModel;
    RTmodel["top wall"]->RTgeometry = RTgeometry["cube"];
    RTmodel["top wall"]->material = RTmaterial["silver"];

    RTmodel["bottom wall"] = new RTModel;
    RTmodel["bottom wall"]->RTgeometry = RTgeometry["cube"];
    RTmodel["bottom wall"]->material = RTmaterial["wood"];

    RTmodel["front wall"] = new RTModel;
    RTmodel["front wall"]->RTgeometry = RTgeometry["cube"];
    RTmodel["front wall"]->material = RTmaterial["silver"];
    // RTmodel["bunny"] = new RTModel;
    // RTmodel["bunny"]->RTgeometry = RTgeometry["bunny"];
    // RTmodel["bunny"]->material = RTmaterial["turquoise"];
    RTmodel["bulb"] = new RTModel;
    RTmodel["bulb"]->RTgeometry = RTgeometry["cube"];
    RTmodel["bulb"]->material = RTmaterial["bulb"];

    // Create a light palette
    light["sun"] = new Light;
    light["sun"]->position = vec4(0.0f, 2.0f, 1.0f, 0.0f);
    light["sun"]->color = 1.0f * vec4(1.0f, 1.0f, 1.0f, 1.0f);

    light["bulb"] = new Light;
    light["bulb"]->position = vec4(0.0f, 2.0f, 0.0f, 0.0f);
    light["bulb"]->color = 1.5f * vec4(1.0f, 0.2f, 0.1f, 1.0f);

    // Build the scene graph
    RTnode["table"] = new RTNode;
    RTnode["table top"] = new RTNode;
    RTnode["back_wall"] = new RTNode;
    RTnode["front_wall"] = new RTNode;
    RTnode["left_wall"] = new RTNode;
    RTnode["right_wall"] = new RTNode;
    RTnode["top_wall"] = new RTNode;
    RTnode["bottom_wall"] = new RTNode;
    RTnode["table leg"] = new RTNode;
    // RTnode["teapot1"] = new RTNode;
    // RTnode["teapot2"] = new RTNode;
    // RTnode["bunny"] = new RTNode;


    RTnode["table"]->childnodes.push_back(RTnode["table top"]);
    RTnode["table"]->childtransforms.push_back(translate(vec3(0.0f, 1.2f, 0.0f)));
  
    RTnode["table top"]->models.push_back(RTmodel["table piece"]);
    RTnode["table top"]->modeltransforms.push_back(translate(vec3(0.f, -0.1f, 0.0f)) * scale(vec3(2.0f, 2.f, 2.0f)));
    // RTnode["table top"]->childnodes.push_back(RTnode["teapot1"]);
    // RTnode["table top"]->childtransforms.push_back(translate(vec3(-0.5f, 0.0f, 0.0f)));
    // RTnode["table top"]->childnodes.push_back(RTnode["teapot2"]);
    // RTnode["table top"]->childtransforms.push_back(translate(vec3(0.5f, 0.0f, 0.0f)) * rotate(-120.0f * float(M_PI) / 180.0f, vec3(0.0f, 1.0f, 0.0f)));

    // RTnode["teapot1"]->models.push_back(RTmodel["teapot1"]);
    // RTnode["teapot1"]->modeltransforms.push_back(scale(vec3(0.5f)));
    // RTnode["teapot2"]->models.push_back(RTmodel["teapot2"]);
    // RTnode["teapot2"]->modeltransforms.push_back(scale(vec3(1.0f, 1.5f, 1.0f)) * scale(vec3(0.5f)));

    // RTnode["bunny"]->models.push_back(RTmodel["bunny"]);
    // RTnode["bunny"]->modeltransforms.push_back(scale(vec3(0.8f)) * translate(vec3(0.0f, 1.0f, 0.0f)));
     // bottom wall
    RTnode["table"] -> childnodes.push_back( RTnode["bottom_wall"] );
    RTnode["table"] -> childtransforms.push_back( translate(vec3(0.0f,0.0f,-0.05f)) );
    // Left wall 
    RTnode["table"] -> childnodes.push_back( RTnode["left_wall"] );
    RTnode["table"] -> childtransforms.push_back( translate(vec3(-4.0f,1.5f,-1.0f))*rotate( -90.0f*float(M_PI)/180.0f, vec3(0.0f, 0.0f, -0.5f) ) );
    // back wall
    RTnode["table"] -> childnodes.push_back( RTnode["back_wall"] );
    RTnode["table"] -> childtransforms.push_back( translate(vec3(-4.0f,1.5f,-1.0f))*rotate( -180.0f*float(M_PI)/180.0f, vec3(0.0f, 1.0f,1.0f) ) );
    // right wall
    RTnode["table"] -> childnodes.push_back( RTnode["right_wall"] );
    RTnode["table"] -> childtransforms.push_back( translate(vec3(4.0f,1.5f,-1.0f))*rotate( -90.0f*float(M_PI)/180.0f, vec3(0.0f, 0.0f, -0.5f) ) );
    // top wall
    RTnode["table"] -> childnodes.push_back( RTnode["top_wall"] );
    RTnode["table"] -> childtransforms.push_back( translate(vec3(4.0f,1.5f,-1.0f))*rotate( -180.0f*float(M_PI)/180.0f, vec3(0.0f, 0.0f, -0.5f) ) );
    // front wall
    RTnode["table"] -> childnodes.push_back( RTnode["front_wall"] );
    RTnode["table"] -> childtransforms.push_back( translate(vec3(-4.0f,1.5f,5.0f))*rotate( -180.0f*float(M_PI)/180.0f, vec3(0.0f, 1.0f, 1.f) ) );
   
    // bottom wall
    RTnode["bottom_wall"] -> models.push_back( RTmodel["bottom wall"] );
    RTnode["bottom_wall"] -> modeltransforms.push_back( translate(vec3(0.0f,-9.f,0.0f)) * scale(vec3(25.0f,0.3f,25.0f)) );
    // left wall 
    RTnode["left_wall"] -> models.push_back( RTmodel["left wall"] );
    RTnode["left_wall"] -> modeltransforms.push_back( translate(vec3(0.0f,6.f,0.0f)) * scale(vec3(20.0f,0.3f,20.0f)) );
    //back wall
    RTnode["back_wall"] -> models.push_back( RTmodel["back wall"] );
    RTnode["back_wall"] -> modeltransforms.push_back( translate(vec3(-4.0f,-9.0f,0.0f)) * scale(vec3(22.0f,0.3f,22.0f)) );
    //right wall
    RTnode["right_wall"] -> models.push_back( RTmodel["right wall"] );
    RTnode["right_wall"] -> modeltransforms.push_back( translate(vec3(0.0f,-6.f,0.0f)) * scale(vec3(20.0f,0.3f,20.0f))  );
    //top wall
    RTnode["top_wall"] -> models.push_back( RTmodel["top wall"] );
    RTnode["top_wall"] -> modeltransforms.push_back( translate(vec3(3.9f,-9.f,0.0f)) * scale(vec3(20.0f,0.3f,20.0f)) );
    //front wall
    RTnode["top_wall"] -> models.push_back( RTmodel["front wall"] );
    RTnode["top_wall"] -> modeltransforms.push_back( translate(vec3(-4.0f,4.f,0.0f)) * scale(vec3(20.0f,0.3f,20.0f)) );

    
    RTnode["world"]->childnodes.push_back(RTnode["table"]);
    RTnode["world"]->childtransforms.push_back(mat4(1.0f));
    // RTnode["world"]->childnodes.push_back(RTnode["bunny"]);
    // RTnode["world"]->childtransforms.push_back(translate(vec3(-1.8f, 0.0f, 0.0f)) * rotate(90.0f * float(M_PI) / 180.0f, vec3(0.0f, 1.0f, 0.0f)));
    // RTnode["world"]->models.push_back(RTmodel["bulb"]);
    // RTnode["world"]->modeltransforms.push_back(translate(vec3(0.0f, 2.0f, 0.0f)) * scale(vec3(0.1f)));

    // Put a camera
    camera = new Camera;
    camera->target_default = vec3(0.0f, 1.0f, 0.0f);
    camera->eye_default = vec3(3.5f, 1.f, 4.0f);
    camera->up_default = vec3(0.0f, 1.0f, 0.0f);
    camera->reset();

    // Initialize shader
    shader = new SurfaceShader;
    shader->read_source("shaders/projective.vert", "shaders/lighting.frag");
    shader->compile();
    glUseProgram(shader->program);
    shader->initUniforms();
}
