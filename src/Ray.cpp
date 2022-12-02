
#include "Ray.h"
#include <iostream>

void RayTracer::Raytrace(Camera* cam, RTScene &RTscene, Image& image) {
    int w = image.width; int h = image.height;
    for (int j = 0; j < h; j++) {
        for (int i = 0; i < w; i++) {
            Ray ray = RayThruPixel(cam, i, j, w, h);
            Intersection hit = Intersect_Scene(ray, RTscene);
            image.pixel[j*w+i] = FindColor(RTscene, hit, 5);
            // std::cout << image.pixel[j*w+i].x << " "<< image.pixel[j*w+i].y << " " << image.pixel[j*w+i].z << std::endl;
        }
        std::cout << j << std::endl;
    }
}


Ray RayTracer::RayThruPixel(Camera* cam, int i, int j, int width, int height) {
    Ray ray; // find the ray source position and direction through pixel[i][[j]
    glm::vec3 w = glm::normalize(cam->eye - cam->target);
    glm::vec3 u = glm::normalize(glm::cross(cam->up,w));
    glm::vec3 v = glm::cross(w, u);
    float fovy_rad = cam->fovy * M_PI/180.0f; // let angle of view be 50 degree
    float alpha =  (2.0f *(i + 0.5f) / (float)width) - 1.0f;
    float beta = 1.0f - (2.0f *(j + 0.5f) / (float)height);
    float aspect = cam->aspect;
    // camera coord
    ray.p0 = glm::vec3(0.0f);
    ray.dir = glm::vec3(alpha*aspect*glm::tan(fovy_rad/2.0f), beta*glm::tan(fovy_rad/2.0), -1.0f);
    
    // world coord
    // ray.p0 = cam->eye;
    // ray.dir = glm::normalize(alpha * aspect * glm::tan(fovy_rad/2.0f) * u + beta * glm::tan(fovy_rad/2.0f) * v - w);
    // std::cout << ray.dir.x <<" "<< ray.dir.y << " " <<ray.dir.z << std::endl;
    return ray;
}

Intersection RayTracer::Intersect_Triangle(Ray ray, Triangle& triangle) {
    Intersection hit_point;
    glm::mat4 tri = {
        glm::vec4(triangle.P[0], 1.0f),
        glm::vec4(triangle.P[1], 1.0f),
        glm::vec4(triangle.P[2], 1.0f),
        glm::vec4(-ray.dir, 0.0f)
    };

    glm::vec4 p0 = glm::vec4(0.0f,0.0f,0.0f, 1.0f); // in camera coord
    // glm::vec4 p0 = glm::vec4(ray.p0, 1.0f); // in world coord

    glm::vec4 coefficient = glm::inverse(tri)*p0; 
    // std::cout << coefficient.x << " " << coefficient.y << " " << coefficient.z << " " << coefficient.w << std::endl;
    if (coefficient.x >= 0 && coefficient.y >= 0 && coefficient.z >= 0 && coefficient.w >= 0) {
        hit_point.P = coefficient.x * triangle.P[0] + coefficient.y * triangle.P[1] + coefficient.z * triangle.P[2]; // intersection positoin
        // hit_point.P = glm::vec3(p0)+coefficient.w*ray.dir;
        hit_point.N = glm::normalize(coefficient.x * triangle.N[0] + coefficient.y * triangle.N[1] + coefficient.z * triangle.N[2]); // normal
        hit_point.dist = coefficient.w; // dist = t
        hit_point.V = -ray.dir; // direction of incoming ray
        hit_point.triangle = triangle;
        hit_point.intersect = 1.0;
        // std::cout << triangle.P[0].x << " " << triangle.P[0].y << " " <<triangle.P[0].z << " " <<std::endl;
    }
    return hit_point;
}

Intersection RayTracer::Intersect_Scene(Ray ray, RTScene &RTscene) {
    float mindist = INFINITY;//std::numeric_limits<float>::infinity();   // distance
    Intersection hit;
    for (Triangle tri : RTscene.triangle_soup) { // Find closest intersection; test all objects       
        Intersection hit_temp = Intersect_Triangle(ray, tri); // intersect triangle
        if (hit_temp.dist < mindist) { // closer than previous hit
            mindist = hit_temp.dist;
            hit = hit_temp;
            // std::cout << mindist << std::endl;
        }
    }
    return hit;
}

glm::vec3 RayTracer::FindColor(RTScene &RTscene, Intersection hit, int recursion_depth) {
    /*** 
     * function to add lighting using BlinnPhone.
    ***/
    std::function<glm::vec4(Intersection)> BlinnPhone = [&](Intersection hit) {
        glm::vec4 fragColor;
        glm::vec3 normal = hit.N;
        glm::mat4 modelview = RTscene.shader->modelview;
        glm::vec4 position = glm::vec4(hit.P,1);
        glm::vec4 sumLight = glm::vec4(0.0f);
        int nlights = RTscene.light.size();
        std::vector<glm::vec4> lightpositions = RTscene.shader->lightpositions;
        glm::mat4 view = RTscene.shader->view;
        glm::vec4 ambient = hit.triangle.material->ambient;
        glm::vec4 diffuse = hit.triangle.material->diffuse;
        glm::vec4 specular = hit.triangle.material->specular;
        float shininess = hit.triangle.material->shininess;
        glm::vec4 emision = hit.triangle.material->emision;
        std::vector<glm::vec4> lightcolors = RTscene.shader->lightcolors;
        glm::vec3 normal_camera = glm::normalize(glm::transpose(glm::inverse(glm::mat3(modelview))) * normal);
        glm::vec4 position_camera = modelview * position;
        glm::vec3 view_cam = glm::normalize(glm::vec3(-position_camera)); // vec3(-position_camera) or will have pixels off.
        // normalize vec4 and vec3 will make slight different.

        for (int j = 0; j < nlights; j++) {
            glm::vec4 lightPos_camera = view * lightpositions[j];

            glm::vec3 lightPos_dir_cam = glm::normalize(position_camera.w * glm::vec3(lightPos_camera) -
                lightPos_camera.w * glm::vec3(position_camera)); // l_j

            glm::vec3 h_j = normalize(view_cam + lightPos_dir_cam);

            sumLight += (ambient + diffuse * std::max(glm::dot(normal_camera, lightPos_dir_cam), (float)0.0) +
                specular * (std::max(pow(dot(normal_camera, h_j), shininess), (float)0.0))) * lightcolors[j];
        }

        fragColor = emision + sumLight;
        return fragColor;
    };

    /***
     * function to check shadows
     * To add shadow for each light, shoot a ray towards the light 
     * and test if the ray intersect with any other triangle 
     * (not including the self triangle). If it hits other triangle that is 
     * between the point and the light, then the light is not visible.
    ***/
    std::function<bool(Ray)> ray_to_lights = [&](Ray ray_to_light){
        for(Triangle tri: RTscene.triangle_soup){
            Intersection hit = Intersect_Triangle(ray_to_light, tri);
            if(hit.intersect==1.0f) return false;
        }
        return true;
    };

    glm::vec3 color = glm::vec3(0.1f, 0.2f, 0.3f);      
    if (recursion_depth == 0) {
       return color;
    }
    
    if (hit.intersect == 1.0) {
        for(auto const& l: RTscene.shader->lightpositions){
            Ray ray_to_light;
            ray_to_light.p0 = 1.05f*hit.P;
            ray_to_light.dir = glm::normalize(glm::vec3(l)-hit.P);
            if(ray_to_lights(ray_to_light)){    // when ray can hit light
                color = glm::vec3(BlinnPhone(hit));
                glm::vec4 diffuse_sum = glm::vec4(0.0f);
                int numLights = RTscene.light.size();
                for (int i = 0; i < numLights; i++) {
                    color += glm::vec3(hit.triangle.material->diffuse* RTscene.shader->lightcolors[i] *
                        std::max(glm::dot(hit.N, glm::vec3(RTscene.shader->lightpositions[i])),0.0f) * hit.intersect);
                }
                
                Ray reflection;
                reflection.p0 = hit.P*1.05f;
                reflection.dir = 2.0f*(glm::dot(hit.N,hit.V))*hit.N-hit.V;
                Intersection reflect_hit = Intersect_Scene(reflection, RTscene);
                color += glm::vec3(hit.triangle.material->specular)*FindColor(RTscene, reflect_hit, --recursion_depth);
            }else{  // when there is some triangles in between.
                color = glm::vec3(0.0f);   // assign black for shadow.
            }
        }
        
        // std::cout << "depth " << recursion_depth << std::endl;
        // std::cout << hit.triangle.P[1].x << " " << hit.triangle.P[1].y << std::endl;
        // color = glm::vec3(0.8,0.8,0.1);


        // color = glm::vec3(glm::normalize(BlinnPhone(hit)));
        // glm::vec4 diffuse_sum = glm::vec4(0.0f);
        // int numLights = RTscene.light.size();

        // for (int i = 0; i < numLights; i++) {
        //     color += glm::vec3(hit.triangle.material->diffuse* RTscene.shader->lightcolors[i] *
        //         std::max(glm::dot(hit.N, glm::vec3(RTscene.shader->lightpositions[i])),(float)0) * hit.intersect);

        // }
        
    }

   
    //std::cout << color.x << " " << color.y << " " << color.z << std::endl;
    return color;
}