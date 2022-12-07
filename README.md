<h1>Ray Tracing (Casting)</h1>
<h2 style="color:red"> Demonstration:</h2>
<div>
The first image is how the scene looks with Blinnephone Shading.
<img src="./test7.png"
     style="float: left; margin-right: 10px;" />
</div>
The following image is the result after rendering the scene with ray tracing and mirror reflections.
<img src="./test6.png"
     style="float: left; margin-right: 10px;" />
</div>
<div>
We can see the ray tracing scene has the mirror reflection effect and the shadow as well, while light source at the middle top, the table top and both teapot has bright colors and the place that light can not reach, are more dark just like how shadows look like. The left teapot has material "ceramic" and right teapot has material "silver", table has material "wood", based on the material, they have different reflection effect. For "silver" we can see a more clear reflection of another teapot, and the "ceramic" teapot has a more blur reflection of the right teapot. Obviously that wood has the less reflection, but if we zoom in little more, we can still see some reflection on it which is very similar to how real lighting works. Similar to the shadows, the front of the table and table legs are not directly reachable by light, so they are darker compare to the table top. and the shadow of both teapot also demonstrated a shadow effect of real lighting which is what we are looing for by using ray tracing. 
</div>

<h2 style="color:red"> Write Up:</h2>
<div>
<p>
    Instead of using rasterization, here I'm using Ray Casting to iterate every pixels, shoot a ray through each pixel, and find the closest intersect triangle in every geometry in the scene. Then for each intersected triangle, we need to create a second ray shoot from the hit point to light sources to check for visibility, this will find the shadow if it's not visible by the light. A problem for find shadow is to avoid self-shadow, which will give a bunch of black dots in the scene. To avoid self-shadow, we simply move the hit point a little, in my case, I multiplied hit position by 1.03 and it worked just find. Next is reflection, reflection will need another ray shoots out from the hit point, based on the material normal, it will have different reflected direction. For the reflection, I did recursively with recursion depth 5. Since reflection may never stop, so we need to force it to stop with maximum recursion depth.
</p>
</div>
<div>
<p>
Before start with the Raytrace functions, we first need to creat a vector of Triangle triangel_soup that stores all the triangles of the scene. So instead of add each object to vertex buffer, we have to manually add all triangles into Geometry->elements. While building the scene by dfs, we can update the triangle material, position and normal, then push it into triangle_soup. Once we have all the triangles stored, we can look at the 5 core functions for ray tracing: 
    <img src="./write_up_img/core_funcs.png"
     style="float: left; margin-right: 10px;" />
</p>
</div>

<div>
<h3 style="color:skyblue">void Raytrace(Camera* cam, RTScene &RTscene, Image& image)</h3><br>
<h4 style="color:lightgreen">
The parameters passed into this function are Camera pointer, Scene, and Image. Camera pointer is a pointer to Scene camera, Scene is the scene we created for this ray tracing project, Image is the class used to store colors into pixels, and will call Image.draw() in main for display final scene.
</h4>
<p>Raytrace function is the main function that iterates through all pixels in a width x height screen. For each pixel, it will call RayThruPixel first that shoots a Ray from Camera through the current pixel. Then it call Intersect_Scene function, that returns the closest hit point of the ray and all triangles in the scene. Last it call FindColor function that return a color and assign to current pixel.
</p>

</div>

<div>
<h3 style="color:skyblue">Ray RayThruPixel(Camera* cam, int i, int j, int width, int height)</h3><br>
<h4 style="color:lightgreen">
The parameters passed into this function are Camera pointer that points to Scene camera, and i, j are the index of current pixel, width and height is screen width and height.
</h4>
<p>
In RayThruPixel function, we basically return a Ray from Camera through current pixel, In order to do so, we have to first calculate the Camera vectors, 
    <img src="./write_up_img/cam_vec.png"
     style="float: left; margin-right: 10px;" />
w is eye to target vector, u is the up vector and v is the right vector, all 3 vectors need to be normalized. 
    <img src="./write_up_img/cam_angle.png"
     style="float: left; margin-right: 10px;" />
Then we can have the aspect ratio, field of view information from Camera. Since we want the ray to shoot through the center of the pixel, here is what we need to do. 
    <img src="./write_up_img/pixel_center.png"
     style="float: left; margin-right: 10px;" />
Once we have all the values ready, we need to decide whether to do this in world space or camera space. World space is easier and is what I did. So I set the ray position to eye position, and direction is calculated by this formula .
     <img src="./write_up_img/ray_dir.png"
     style="float: left; margin-right: 10px;" />
    Once we calculated the ray, we can return it and pass it into the next function Intersection Intersect_Triangle. 
</p>

</div>

<div>
<h3 style="color:skyblue">Intersection Intersect_Scene(Ray ray, RTScene &RTscene)</h3><br>
<h4 style="color:lightgreen">
The parameters passed into this function are the Ray that generated from RayThruPixel function, and the Scene.
</h4>
<p>
In Intersect_Scene function, we need to find the closest hit of the Ray, here what I did is a very slow approach that we need to iterate all trangles of the scene in order to find the closest hit. once we find the closest hit, we can return the Intersection and pass it to the Next function FindColor.
</p>

</div>


<div>
<h3 style="color:skyblue">Intersection Intersect_Triangle(Ray ray, Triangle& triangle)</h3><br>
<h4 style="color:lightgreen">
The parameters passed into this function are the Ray that generated from Intersect_Scene function, intersection triangle.
</h4>
<p>
In Intersect_Triangle function, we need to check whether the ray is intersect with the triangle, I used the following equations, 
    <img src="./write_up_img/tri_intersect.png"
     style="float: left; margin-right: 10px;" />
The Mat4 is created with triangle parameter positions, and the last column is negative ray direction. the vec4 at the right hand side is ray position pad with 1. Then use the inverse of the Mat4 times the ray position vec4, we will get the vec4 with all the coefficients and t, here t is the distance of the hit. If all the coefficient are greater equal to 0, it means a hit, and we need to update the intersection information. Here is the equation for Intersect position and normal,
<img src="./write_up_img/intersect_pos.png"
     style="float: left; margin-right: 10px;" />
Intersection distance is t, Incoming ray direction is negative of ray direction. Last reference the intersectin triangle to the current triangle. Return this Intersection. if there is no hit, then it will return the Intersection with default initialize value distance to INFINITY.
</p>

</div>


<div>
<h3 style="color:skyblue">glm::vec3 FindColor(RTScene &RTscene, Intersection hit, int recursion_depth)</h3><br>
<h4 style="color:lightgreen">
The parameters passed into this function are the Scene, Intersectin returned from Intersect_Scene, and the maximum recursion depth.
</h4>
<p>
In FindColor function, it need to return a color for each pixel based on the passed in parameters. First create color with background color value, then check if the hit are actually intersect with any triangles, if no just return background color for this pixel. If there is a hit, then we need to give it ambient color with diffuse color from all ligth sources. A general equation is as below,
<img src="./write_up_img/diffuse.png"
     style="float: left; margin-right: 10px;" />.
Next we need to check for shadows, generate another Ray that shoot directly to all the light sources by Calling the function Intersection Intersect_Scene(Ray ray, RTScene &RTscene). To avoid self-shadow, I times the Ray position by 1.03 to move it a little bit. If there is a hit, which means that something is blocking the triangle to reach the light sources, then it should be shadow, so give it black color vec3(0.f).
</p>
<p>
Once done with checking shadows, next is generate a new Ray for mirror reflection. start at the same position, the direction of reflection are calculated as following,
<img src="./write_up_img/reflect_dir.png"
     style="float: left; margin-right: 10px;" />
After create the reflection Ray, we will check for hit by calling function Intersection Intersect_Scene(Ray ray, RTScene &RTscene) again. Then call Find color recursively with the reflection hit information. the recursion will stop if there is no hit or reach the maximum recursive depth.
Now, we need to add the specular color with the reflection color based on the following equation,
<img src="./write_up_img/color_equa.png"
     style="float: left; margin-right: 10px;" />
</p>
<p>
Return color will either return background color, shadow color, or the calculated final color, which gives the mirror reflect effect.
</p>

</div>