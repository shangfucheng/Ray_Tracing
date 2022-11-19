#version 330 core

in vec4 position; // raw position in the model coord
in vec3 normal;   // raw normal in the model coord

uniform mat4 modelview; // from model coord to eye coord
uniform mat4 view;      // from world coord to eye coord

// Material parameters
uniform vec4 ambient;
uniform vec4 diffuse;
uniform vec4 specular;
uniform vec4 emision;
uniform float shininess;

// Light source parameters
const int maximal_allowed_lights = 10;
uniform bool enablelighting;
uniform int nlights;
uniform vec4 lightpositions[ maximal_allowed_lights ];
uniform vec4 lightcolors[ maximal_allowed_lights ];

// Output the frag color
out vec4 fragColor;


void main (void){
    if (!enablelighting){
        // Default normal coloring (you don't need to modify anything here)
        vec3 N = normalize(normal);
        fragColor = vec4(0.5f*N + 0.5f , 1.0f);
    } else {
        
        // HW3: You will compute the lighting here.
        vec4 sumLight= vec4(0.0f);
        vec3 normal_camera = normalize(transpose(inverse(mat3(modelview))) * normal);
        vec4 position_camera = modelview * position;
        vec3 view_cam = normalize(vec3(-position_camera)); // vec3(-position_camera) or will have pixels off.
        // normalize vec4 and vec3 will make slight different.
        
        for(int j = 0; j < nlights; j++){
            vec4 lightPos_camera = view * lightpositions[j];

            vec3 lightPos_dir_cam = normalize(position_camera.w * vec3(lightPos_camera) - 
                        lightPos_camera.w * vec3(position_camera)); // l_j
                        
            vec3 h_j = normalize(view_cam + lightPos_dir_cam);

            sumLight += (ambient + diffuse * max(dot(normal_camera, lightPos_dir_cam),0.0) + 
                        specular * (max(pow(dot(normal_camera, h_j), shininess), 0.0))) * lightcolors[j];
        }
 
        fragColor = emision + sumLight;
        
    }
}
