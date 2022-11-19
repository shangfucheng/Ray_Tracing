/**************************************************
Scene.inl contains the definition of the scene graph
*****************************************************/
#include "Scene.h"
#include "Cube.h"
#include "Obj.h"
#include <random>
#include <ctime>

using namespace glm;
void Scene::init(void){
    // Create a geometry palette
    geometry["cube"] = new Cube;
    geometry["teapot"] = new Obj;
    geometry["bunny"] = new Obj;
    geometry["bunny2"] = new Obj;
    geometry["bunny3"] = new Obj;
    geometry["bunny4"] = new Obj;
    geometry["cube"] -> init();
    geometry["teapot"] -> init("models/teapot.obj");
    geometry["bunny"] -> init("models/bunny.obj");
    geometry["bunny2"] -> init("models/bunny.obj");
    geometry["bunny3"] -> init("models/bunny.obj");
    geometry["bunny4"] -> init("models/bunny.obj");
    
    // Create a material palette
    material["wood"] = new Material;
    material["wood"] -> ambient = vec4(0.1f,0.1f,0.1f,1.0f);
    material["wood"] -> diffuse = vec4(0.3f,0.15f,0.1f,1.0f);
    material["wood"] -> specular = vec4(0.3f,0.15f,0.1f,1.0f);
    material["wood"] -> shininess = 100.0f;
    
    material["ceramic"] = new Material;
    material["ceramic"] -> ambient = vec4(0.02f, 0.07f, 0.2f, 1.0f);
    material["ceramic"] -> diffuse = vec4(0.1f, 0.25f, 0.7f, 1.0f);
    material["ceramic"] -> specular = vec4(0.9f, 0.9f, 0.9f, 1.0f);
    material["ceramic"] -> shininess = 150.0f;
 
    material["silver"] = new Material;
    material["silver"] -> ambient = vec4(0.1f, 0.1f, 0.1f, 1.0f);
    material["silver"] -> diffuse = vec4(0.2f, 0.2f, 0.2f, 1.0f);
    material["silver"] -> specular = vec4(0.9f, 0.9f, 0.9f, 1.0f);
    material["silver"] -> shininess = 50.0f;
    
    material["turquoise"] = new Material;
    material["turquoise"] -> ambient = vec4(0.1f, 0.2f, 0.17f, 1.0f);
    material["turquoise"] -> diffuse = vec4(0.2f, 0.375f, 0.35f, 1.0f);
    material["turquoise"] -> specular = vec4(0.3f, 0.3f, 0.3f, 1.0f);
    material["turquoise"] -> shininess = 100.0f;
    
    material["bulb"] = new Material;
    material["bulb"] -> ambient = vec4(0.0f, 0.0f, 0.0f, 1.0f);
    material["bulb"] -> diffuse = vec4(0.0f, 0.0f, 0.0f, 1.0f);
    material["bulb"] -> specular = vec4(1.0f, 1.0f, 1.0f, 1.0f);
    material["bulb"] -> emision = vec4(1.0f,0.2f,0.1f,1.0f);
    material["bulb"] -> shininess = 900.0f;
    
    // Create a model palette
    model["teapot1"] = new Model;
    model["teapot1"] -> geometry = geometry["teapot"];
    model["teapot1"] -> material = material["silver"];
    model["teapot2"] = new Model;
    model["teapot2"] -> geometry = geometry["teapot"];
    model["teapot2"] -> material = material["ceramic"];
    model["table piece"] = new Model;
    model["table piece"] -> geometry = geometry["cube"];
    model["table piece"] -> material = material["wood"];
    model["bunny"] = new Model;
    model["bunny"] -> geometry = geometry["bunny"];
    model["bunny"] -> material = material["turquoise"];
    model["bunny2"] = new Model;
    model["bunny2"] -> geometry = geometry["bunny2"];
    model["bunny2"] -> material = material["wood"];
    model["bunny3"] = new Model;
    model["bunny3"] -> geometry = geometry["bunny3"];
    model["bunny3"] -> material = material["silver"];
    model["bunny4"] = new Model;
    model["bunny4"] -> geometry = geometry["bunny4"];
    model["bunny4"] -> material = material["ceramic"];
    model["bulb"] = new Model;
    model["bulb"] -> geometry = geometry["cube"];
    model["bulb"] -> material = material["bulb"];
    
    // Create a light palette
    light["sun"] = new Light;
    light["sun"] -> position = vec4(3.0f,2.0f,1.0f,0.0f);
    light["sun"] -> color = 1.0f*vec4(0.5f,0.5f,1.0f,1.0f);
    
    light["bulb"] = new Light;
    light["bulb"] -> position = vec4(0.0f,2.0f,0.0f,0.0f);
    light["bulb"] -> color = 1.5f * vec4(0.8f,0.2f,0.9f,1.0f);
    
    // Build the scene graph
    node["table"] = new Node;
    node["table2"] = new Node;
    node["table top"] = new Node;
    node["table top1"] = new Node;
    node["table top2"] = new Node;
    node["table top3"] = new Node;
    node["table top4"] = new Node;
    node["table top5"] = new Node;
    node["table top6"] = new Node;
    node["table top7"] = new Node;
    node["table leg"] = new Node;
    node["teapot1"] = new Node;
    node["teapot2"] = new Node;
    node["bunny"] = new Node;
    node["bunny2"] = new Node;
    node["bunny3"] = new Node;
    node["bunny4"] = new Node;
    
    
    node["table"] -> childnodes.push_back( node["table top"] );
    node["table"] -> childtransforms.push_back( translate(vec3(0.0f,0.0f,-0.05f)) );
    // Left wall 
    node["table"] -> childnodes.push_back( node["table top1"] );
    node["table"] -> childtransforms.push_back( translate(vec3(-4.0f,1.5f,-1.0f))*rotate( -90.0f*float(M_PI)/180.0f, vec3(0.0f, 0.0f, -0.5f) ) );
    // back wall
    node["table"] -> childnodes.push_back( node["table top2"] );
    node["table"] -> childtransforms.push_back( translate(vec3(-4.0f,1.5f,-1.0f))*rotate( -180.0f*float(M_PI)/180.0f, vec3(0.0f, 1.0f,1.0f) ) );
    // right wall
    node["table"] -> childnodes.push_back( node["table top3"] );
    node["table"] -> childtransforms.push_back( translate(vec3(4.0f,1.5f,-1.0f))*rotate( -90.0f*float(M_PI)/180.0f, vec3(0.0f, 0.0f, -0.5f) ) );
    // top wall
    node["table"] -> childnodes.push_back( node["table top4"] );
    node["table"] -> childtransforms.push_back( translate(vec3(4.0f,1.5f,-1.0f))*rotate( -180.0f*float(M_PI)/180.0f, vec3(0.0f, 0.0f, -0.5f) ) );
    // roof left
    node["table"] -> childnodes.push_back( node["table top5"] );
    node["table"] -> childtransforms.push_back( translate(vec3(-1.0f,2.0f,-1.0f))*rotate( -40.0f*float(M_PI)/180.0f, vec3(0.0f, 0.0f, -0.5f) ) );
    // roof right
    node["table"] -> childnodes.push_back( node["table top6"] );
    node["table"] -> childtransforms.push_back( translate(vec3(3.0f,3.0f,-1.0f))*rotate( 40.0f*float(M_PI)/180.0f, vec3(0.0f, 0.0f, -0.5f) ) );
   // table top for teapots
    // node["table"] -> childnodes.push_back( node["table top7"] );
    // node["table"] -> childtransforms.push_back( translate(vec3(0.0f,1.0f,5.0f)) );
   
    // srand (static_cast <unsigned> (time(0)));
    // int lb = 0, ub = 1;
    // float x = -1, y = -1, z = -1;
    // for (int i = 0; i < 1000; i++){
    //     if (!(i % 5)){
    //         x = static_cast <float> (rand()) / static_cast <float> (RAND_MAX) -1;
    //         y = static_cast <float> (rand()) / static_cast <float> (RAND_MAX) - 1;
    //         z = static_cast <float> (rand()) / static_cast <float> (RAND_MAX) -1;
    //     }
    //     node["table"] ->childnodes.push_back(node["table leg"]);
    //     node["table"] ->childtransforms.push_back(translate(vec3(x,y,z)));
    //     x += 0.3;
    //     y += 0.4;
    //     z += 0.5;
    // }

    
    node["table leg"] -> models.push_back( model["table piece"] );
    node["table leg"] -> modeltransforms.push_back( translate(vec3(0.0f,0.5f,0.0f)) * scale(vec3(0.05f,1.5f,0.05f)) );
    
    node["table top"] -> models.push_back( model["table piece"] );
    node["table top"] -> modeltransforms.push_back( translate(vec3(0.0f,-0.1f,0.0f)) * scale(vec3(15.0f,0.3f,15.0f)) );

    // front wall 
    node["table top1"] -> models.push_back( model["table piece"] );
    node["table top1"] -> modeltransforms.push_back( translate(vec3(0.0f,-0.1f,0.0f)) * scale(vec3(3.0f,0.3f,6.0f)) );

    //back wall
    node["table top2"] -> models.push_back( model["table piece"] );
    node["table top2"] -> modeltransforms.push_back( translate(vec3(-4.0f,-3.0f,0.0f)) * scale(vec3(8.0f,0.3f,3.0f)) );
    //right wall
    node["table top3"] -> models.push_back( model["table piece"] );
    node["table top3"] -> modeltransforms.push_back( translate(vec3(0.0f,-0.1f,0.0f)) * scale(vec3(3.0f,0.3f,6.0f)) );
    //top wall
    node["table top4"] -> models.push_back( model["table piece"] );
    node["table top4"] -> modeltransforms.push_back( translate(vec3(3.9f,-1.5f,0.0f)) * scale(vec3(8.0f,0.3f,8.0f)) );
    //roof left
    node["table top5"] -> models.push_back( model["table piece"] );
    node["table top5"] -> modeltransforms.push_back( translate(vec3(0.0f,3.0f,0.0f)) * scale(vec3(8.0f,0.3f,8.0f)) );
    //roof right
    node["table top6"] -> models.push_back( model["table piece"] );
    node["table top6"] -> modeltransforms.push_back( translate(vec3(-1.0f,1.0f,0.0f)) * scale(vec3(8.0f,0.3f,8.0f)) );
    //table for teapots
    // node["table top7"] -> models.push_back( model["table piece"] );
    // node["table top7"] -> modeltransforms.push_back( translate(vec3(-1.0f,1.0f,8.0f)) * scale(vec3(3.0f,0.3f,3.0f)) );

    // left fences
    float f = -7.0;
    for(int i = 0; i < 140; i++){
        node["table"] ->childnodes.push_back(node["table leg"]);
        node["table"] ->childtransforms.push_back(translate(vec3(-7.0f,0.0f,f)));
        f += 0.1;
    }
    // back fences
    f = -7;
    for(int i = 0; i < 140; i++){
        node["table"] ->childnodes.push_back(node["table leg"]);
        node["table"] ->childtransforms.push_back(translate(vec3(f,0.0f,-7.0f)));
        f += 0.1;
    }
    // right fences
    f = -7;
    for(int i = 0; i < 140; i++){
        node["table"] ->childnodes.push_back(node["table leg"]);
        node["table"] ->childtransforms.push_back(translate(vec3(7.0f,0.0f,f)));
        f += 0.1;
    }
    // left front fences
    f = -7;
    for(int i = 0; i < 50; i++){
        node["table"] ->childnodes.push_back(node["table leg"]);
        node["table"] ->childtransforms.push_back(translate(vec3(f,0.0f,7.0f)));
        f += 0.1;
    }
    // right front fences
    f = 7;
    for(int i = 0; i < 50; i++){
        node["table"] ->childnodes.push_back(node["table leg"]);
        node["table"] ->childtransforms.push_back(translate(vec3(f,0.0f,7.0f)));
        f -= 0.1;
    }
    // add bunnies
    node["bunny"] -> models.push_back( model["bunny"] );
    node["bunny"] -> modeltransforms.push_back( scale(vec3(0.5f)) * translate(vec3(3.0f,1.0f,0.0f)) );
    node["bunny2"] -> models.push_back( model["bunny2"] );
    node["bunny2"] -> modeltransforms.push_back( scale(vec3(0.3f)) * translate(vec3(-0.5,1.0f,0.5f)) );
    node["table top"] -> childnodes.push_back( node["bunny"] );
    node["table top"] -> childtransforms.push_back( translate(vec3(0.5f,0.1f,0.0f)) );
    node["table top"] -> childnodes.push_back( node["bunny2"] );
    node["table top"] -> childtransforms.push_back( translate(vec3( 0.0f,0.1f,0.0f)) * rotate( -120.0f*float(M_PI)/180.0f, vec3(0.0f, 1.0f, 0.0f) ) );
    node["table top"] -> childnodes.push_back( node["bunny2"] );
    node["table top"] -> childtransforms.push_back( translate(vec3( 1.0f,0.1f,2.0f)) * rotate( -90.0f*float(M_PI)/180.0f, vec3(0.0f, 1.0f, 0.0f) ) );
    node["table top"] -> childnodes.push_back( node["bunny2"] );
    node["table top"] -> childtransforms.push_back( translate(vec3( 1.5f,0.1f,3.0f)) * rotate( 90.0f*float(M_PI)/180.0f, vec3(0.0f, 1.0f, 0.0f) ) );
    node["table top"] -> childnodes.push_back( node["bunny2"] );
    node["table top"] -> childtransforms.push_back( translate(vec3( 2.0f,0.1f,2.0f)) * rotate( 120.0f*float(M_PI)/180.0f, vec3(0.0f, 1.0f, 0.0f) ) );
    node["table top"] -> childnodes.push_back( node["bunny2"] );
    node["table top"] -> childtransforms.push_back( translate(vec3( 3.0f,0.1f,4.0f)) * rotate( 30.0f*float(M_PI)/180.0f, vec3(0.0f, 1.0f, 0.0f) ) );

    node["table top"] -> childnodes.push_back( node["bunny2"] );
    node["table top"] -> childtransforms.push_back( translate(vec3( -6.0f,0.1f,-4.0f)) * rotate( -30.0f*float(M_PI)/180.0f, vec3(0.0f, 1.0f, 0.0f) ) );
    node["table top"] -> childnodes.push_back( node["bunny2"] );
    node["table top"] -> childtransforms.push_back( translate(vec3( -2.0f,0.1f,3.0f)) * rotate( 60.0f*float(M_PI)/180.0f, vec3(0.0f, 1.0f, 0.0f) ) );
    node["table top"] -> childnodes.push_back( node["bunny2"] );
    node["table top"] -> childtransforms.push_back( translate(vec3( -5.0f,0.1f,4.0f)) * rotate( 30.0f*float(M_PI)/180.0f, vec3(0.0f, 1.0f, 0.0f) ) );
    node["table top"] -> childnodes.push_back( node["bunny2"] );
    node["table top"] -> childtransforms.push_back( translate(vec3( -3.0f,0.1f,4.0f)) * rotate( -60.0f*float(M_PI)/180.0f, vec3(0.0f, 1.0f, 0.0f) ) );

    node["table top"] -> childnodes.push_back( node["bunny2"] );
    node["table top"] -> childtransforms.push_back( translate(vec3( 0.0f,3.1f,0.0f)) * rotate( 30.0f*float(M_PI)/180.0f, vec3(0.0f, 1.0f, 0.0f) ) );
    node["table top"] -> childnodes.push_back( node["bunny2"] );
    node["table top"] -> childtransforms.push_back( translate(vec3( 3.0f,3.1f,-1.0f)) * rotate( -30.0f*float(M_PI)/180.0f, vec3(0.0f, 1.0f, 0.0f) ) );

    // add table and teapots
    node["table"] -> childnodes.push_back( node["table top7"] );
    node["table"] -> childtransforms.push_back( translate(vec3(1.2f,0.6f,3.0f)) );

    node["table top7"] -> models.push_back( model["table piece"] );
    node["table top7"] -> modeltransforms.push_back( translate(vec3(-4.0f,0.0f,-2.0f)) * scale(vec3(2.0f,0.2f,1.0f)) );
    node["table top7"] -> childnodes.push_back( node["teapot1"] );
    node["table top7"] -> childtransforms.push_back( translate(vec3(-4.5f,0.0f,-2.0f)) );
    node["table top7"] -> childnodes.push_back( node["teapot2"] );
    node["table top7"] -> childtransforms.push_back( translate(vec3( -3.5f,0.0f,-2.0f)) * rotate( -120.0f*float(M_PI)/180.0f, vec3(0.0f, 1.0f, 0.0f) ) );
    
    node["teapot1"] -> models.push_back( model["teapot1"] );
    node["teapot1"] -> modeltransforms.push_back( scale(vec3(0.5f)) );
    node["teapot2"] -> models.push_back( model["teapot2"] );
    node["teapot2"] -> modeltransforms.push_back( scale(vec3(1.0f,1.5f,1.0f)) * scale(vec3(0.5f)) );
    // end table

    node["world"] -> childnodes.push_back( node["table"] );
    node["world"] -> childtransforms.push_back( mat4(1.0f) );
    node["world"] -> childnodes.push_back( node["bunny"] );
    node["world"] -> childtransforms.push_back( translate(vec3(-1.8f,0.3f,0.0f)) * rotate( 90.0f*float(M_PI)/180.0f, vec3(0.0f, 1.0f, 0.0f) ));
    node["world"] -> childnodes.push_back( node["bunny2"] );
    node["world"] -> childtransforms.push_back( translate(vec3(1.5f,0.3f,-0.2f)) * rotate( 45.0f*float(M_PI)/180.0f, vec3(0.0f, 1.0f, 0.0f) ));
    node["world"] -> models.push_back( model["bulb"] );
    node["world"] -> modeltransforms.push_back( translate(vec3(0.0f,2.0f,0.0f))*scale(vec3(0.5f)) );
    
    // Put a camera
    camera = new Camera;
    camera -> target_default = vec3( 0.0f, 1.0f, 0.0f );
    camera -> eye_default = vec3( 0.0f, 5.0f, 15.0f );
    camera -> up_default = vec3( 0.0f, 1.0f, 0.0f );
    camera -> reset();
    
    // Initialize shader
    shader = new SurfaceShader;
    shader -> read_source( "shaders/projective.vert", "shaders/lighting.frag" );
    shader -> compile();
    glUseProgram(shader -> program);
    shader -> initUniforms();
}
