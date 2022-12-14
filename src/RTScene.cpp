/**************************************************
RTScene.cpp contains the implementation of the draw command
*****************************************************/
#include "RTScene.h"
#include "RTCube.h"
#include "RTObj.h"

// The scene init definition 
#include "RTScene.inl"

using namespace glm;
void RTScene::buildTriangleSoup() {
    camera->computeMatrices();
    shader->view = camera->view;
    shader->projection = camera->proj;
    shader->nlights = light.size();
    shader->lightpositions.resize(shader->nlights);
    shader->lightcolors.resize(shader->nlights);
    int count = 0;
    for (std::pair<std::string, Light*> entry : light) {
        shader->lightpositions[count] = (entry.second)->position;
        shader->lightcolors[count] = (entry.second)->color;
        count++;
    }

    // Define stacks for depth-first search (DFS)
    std::stack < RTNode* > dfs_stack;
    std::stack < mat4 >  matrix_stack; // matrix_stack during the depth-first search while loop.

    // Initialize the current state variable for DFS
    RTNode* cur = RTnode["world"]; // root of the tree
    
    // current modelview during the depth first search.  
    // Initially, we are at the "world" node, whose modelview matrix is just camera's view matrix.
    mat4 cur_VM =camera->view; // camera coord
    // mat4 cur_VM = mat4(1.0f); // world coord

    dfs_stack.push(cur);
    matrix_stack.push(cur_VM);

    // Compute total number of connectivities in the graph; this would be an upper bound for
    // the stack size in the depth first search over the directed acyclic graph
    int total_number_of_edges = 0;
    for (const auto& n : RTnode) total_number_of_edges += n.second->childnodes.size();
    while (!dfs_stack.empty()) {
        // Detect whether the search runs into infinite loop by checking whether the stack is longer than the number of edges in the graph.
        if (dfs_stack.size() > total_number_of_edges) {
            std::cerr << "Error: The scene graph has a closed loop." << std::endl;
            exit(-1);
        }

        // top-pop the stacks
        cur = dfs_stack.top();  dfs_stack.pop();
        cur_VM = matrix_stack.top(); matrix_stack.pop();
        // std::cout << cur_VM[1].x << " " << cur_VM[1].y << " " << cur_VM[1].z << std::endl;

        // draw all the models at the current node
        for (size_t i = 0; i < cur->models.size(); i++) {
            // Prepare to draw the geometry. Assign the modelview and the material.
            // Without updating cur_VM, modelview would just be camera's view matrix.

            shader -> modelview = cur_VM * cur->modeltransforms[i]; // Without updating cur_VM, modelview would just be camera's view matrix.
            shader -> material  = ( cur -> models[i] ) -> material;
            shader -> setUniforms();

            for (Triangle j : (cur->models[i])->RTgeometry->elements) {
                j.material = ( cur -> models[i] ) -> material;
                mat4 view_inverse = inverse(shader->view);
                // j.position_update(view_inverse*cur_VM) ;

                j.P[0] = vec3(view_inverse*shader->modelview*vec4(j.P[0],1));
                j.P[1] = vec3(view_inverse*shader->modelview*vec4(j.P[1],1));
                j.P[2] = vec3(view_inverse*shader->modelview*vec4(j.P[2],1));

                j.N[0] = vec3(normalize(inverse(transpose(view_inverse*shader->modelview))*vec4(j.N[0],0)));
                j.N[1] = vec3(normalize(inverse(transpose(view_inverse*shader->modelview))*vec4(j.N[1],0)));
                j.N[2] = vec3(normalize(inverse(transpose(view_inverse*shader->modelview))*vec4(j.N[2],0)));
                triangle_soup.push_back(j);
            }
        }
        // Continue the DFS: put all the child nodes of the current node in the stack
        for (size_t i = 0; i < cur->childnodes.size(); i++) {
            dfs_stack.push(cur->childnodes[i]);
            matrix_stack.push(cur_VM * cur->childtransforms[i]);
        }
    } // End of DFS while loop.
}


