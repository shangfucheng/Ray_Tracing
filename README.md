<h1>Ray Tracing (Casting)</h1>

<div>
<p>
    Instead of using rasterization, here I'm using Ray Casting to iterate every pixels, shoot a ray through each pixel, and find the closest intersect triangle in every geometry in the scene. Then for each intersected triangle, we need to create a second ray shoot from the hit point to light sources to check for visibility, this will find the shadow if it's not visible by the light. A problem for find shadow is to avoid self-shadow, which will give a bunch of black dots in the scene. To avoid self-shadow, we simply move the hit point a little, in my case, I multiplied hit position by 1.03 and it worked just find. Next is reflection, reflection will need another ray shoots out from the hit point, based on the material normal, it will have different reflected direction. For the reflection, I did recursively with recursion depth 5. Since reflection may never stop, so we need to force it to stop with maximum recursion depth.
</p>
</div>
<div>
<p>
In order to accomplish the functionality of ray tracing, here I created 5 core functions: 
</p>
</div>
![alt text](./write_up_img/core_funcs.png?raw=true)
<div>
<h3 style="color:skyblue">void Raytrace(Camera* cam, RTScene &RTscene, Image& image)</h3><br>
<p>
The parameters passed into this function are Camera pointer, Scene, and Image. Camera pointer is a pointer to Scene camera, Scene is the scene we created for this ray tracing project, Image is the class used to store colors into pixels, and will call Image.draw() in main for display final scene.
</p>
<p>Raytrace function is the main function that iterates through all pixels in a width x height screen. For each pixel, it will call RayThruPixel first that shoots a Ray from Camera through the current pixel. Then it call Intersect_Scene function, that returns the closest hit point of the ray and all triangles in the scene. Last it call FindColor function that return a color and assign to current pixel.
</p>

</div>

<div>
<h3 style="color:skyblue">Ray RayThruPixel(Camera* cam, int i, int j, int width, int height)</h3><br>
<p>
The parameters passed into this function are Camera pointer that points to Scene camera, and i, j are the index of current pixel, width and height is screen width and height.
</p>
<p>
In RayThruPixel function, we basically return a Ray from Camera through current pixel, In order to do so, we have to first calculate the Camera vectors, ![alt text](./write_up_img/cam_vec.png?raw=true).
w is eye to target vector, u is the up vector and v is the right vector, all 3 vectors need to be normalized. 
![alt text](./write_up_img/cam_angle.png?raw=true)
Then we can have the aspect ratio, field of view information from Camera. Since we want the ray to shoot through the center of the pixel, here is what we need to do. ![alt text](./write_up_img/pixel_center.png?raw=true).
Once we have all the values ready, we need to decide whether to do this in world space or camera space. World space is easier and is what I did. So I set the ray position to eye position, and direction is calculated by this formula ![alt text](./write_up_img/ray_dir.png?raw=true). Once we calculated the ray, we can return it and pass it into the next function Intersection Intersect_Triangle. 
</p>

</div>

<div>
<h3 style="color:skyblue">Intersection Intersect_Scene(Ray ray, RTScene &RTscene)</h3><br>
<p>
The parameters passed into this function are the Ray that generated from RayThruPixel function, and the Scene.
</p>
<p>
In Intersect_Scene function, we need to find the closest hit of the Ray, here what I did is a very slow approach that we need to iterate all trangles of the scene in order to find the closest hit. once we find the closest hit, we can return the Intersection and pass it to the Next function FindColor.
</p>

</div>


<div>
<h3 style="color:skyblue">Intersection Intersect_Triangle(Ray ray, Triangle& triangle)</h3><br>
<p>
The parameters passed into this function are the Ray that generated from Intersect_Scene function, intersection triangle.
</p>
<p>
In Intersect_Triangle function, we need to check whether the ray is intersect with the triangle, I used the following equations, ![alt text](./write_up_img/tri_intersect.png?raw=true). 
</p>

</div>


<div>
<h3 style="color:skyblue">glm::vec3 FindColor(RTScene &RTscene, Intersection hit, int recursion_depth)</h3><br>
<p>
The parameters passed into this function are the Scene, Intersectin returned from Intersect_Scene, and the maximum recursion depth.
</p>
<p>
In FindColor function, it need to return a color for each pixel based on the passed in parameters. First check if the hit are actually intersect with any triangles, 
</p>

</div>
