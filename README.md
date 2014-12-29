Final Project: Kangaroo Renderer
================================

Kangaroo Renderer is a progressive, fast renderer with real-time camera
controls. I tried to make it easily extensible, with use of abstract classes
wherever possible to enable future improvements.

Compiling
---------
To compile, simply type 

	make

This should create a build directory, run CMake, and then compile the program.

Usage
-----
./build/kangaroo <scene_file> <output_file>

Kangaroo renders a scene file with a display to a provided output filepath.
When it opens up, it shows you the render as it happens, pixel by pixel. 

You can move the camera by using the arrow keys, as well as ] to zoom in, [ to
zoom out.  This will cause the render to restart. Once the render is complete,
the camera can no longer be moved. If the render was completed, a file will be
saved when you exit by hitting Escape or closing the window.

Render Files
------------
Kangaroo processes render files, which describe both a camera and the scene that is
being rendered. A simple example:

```xml
<?xml version="1.0" encoding="UTF-8"?>
<render>
  <scene>

    <sphere r='100'>
      <position x='0' y='0' z='900'></position>
      <material>
        <type>Lambertian</type>
        <emit r='0.2' g='1.5' b='2.0'></emit>
        <color r='0' g='0' b='0'></color>
      </material>
    </sphere>

    <triangle>
      <point x='-10000' y='-10000' z='1000'></point>
      <point x='10000' y='-10000' z='1000'></point>
      <point x='0' y='10000' z='1000'></point>
      <material>
        <type>Lambertian</type>
        <color r='0.4' g='0.4' b='0.4'></color>
      </material>
    </triangle>

  </scene>
</render>
```

Render files must have <render> as the root tag, and then a scene, specified
under a <scene> tag. Currently, only triangles and spheres are supported. Their
specifications should be easy to understand from the example above. Multiple
objects of each type can be added by simply using more tags.

In the future, meshes could be added using this syntax:
```xml
    <mesh>
      <position x='-10' y='0' z='0'></position>
      <up x='0' y='1' z='0'></up>
			<file>./bunny.obj</file>
    </mesh>
```

This would load up a mesh from the provided obj file and instantiate it in the
world at a provided position, and with the y-axis of the model pointing at the
provided "up" axis.

Specifying the Camera
---------------------
The camera position can also be specified in the render file like this:
```xml
<?xml version="1.0" encoding="UTF-8"?>
<render>
  <camera>
    <position x='0' y='0' z='-100'></position>
    <direction x='0' y='0' z='1'></direction>
    <up x='0' y='1' z='0'></up>

    <passes>100</passes>
    <image width='800' height='800'></image>

    <fovx>35</fovx>
  </camera>
  <scene>
	...
  </scene>
</render>
```

Direction is the direction the camera is pointing. Up is the up direction of the
camera. Passes is the number of samples per pixel. <image> allows you to specify
the image width and height. Finally, <fovx> allows you to specify the horizontal
field of view angle, in degrees. The focal length is calculated from this
value.

Materials
---------
The materials for each object can also be specified in this scene file, by using
the <material> tag. A <type> tag must be present to specify which Material class
should be used. Further tags are optional and can vary by material, to specify
further parameters of that material. 

For example, Lambertian materials can have
a specified <color>, which encodes how much light of each channel is reflected,
and a specified <emit>, which encodes how much light of each channel is emitted
by the surface.

Currently, the only material that seems correct is Lambertian. The key class
which I have failed to create is BRDFMaterial (src/material/BRDFMaterial.hpp),
which allows you to easily specify materials by inheriting from BRDFMaterial and
defining a BRDF function, which takes in the theta of the incoming light ray
(phi is, for simplicity, assumed to be 0) and returns an AngleSample, which
reflects a direction sampled according to the BRDF and the combined probability
of the BRDF sampling that direction/value of the BRDF in that direction.

TransparentSpecular was an attempt to create a rough approximation of a
semitransparent surface, but it doesn't appear to be physically accurate
(although it looks nice). I'm not exactly sure what went wrong...

Scene Loader
------------
A lot of the extensibility of this program is due to the scene files, which are
a nice interface between XML files and the C++ code. You can add other materials
by going to src/scene/RenderLoader.cpp and defining a new MaterialLoader, then
inserting it with a key (the value of the <type> tag) into the static map
material_loaders.

Similarly, support for other objects than triangles and spheres can be
accomplished by inheriting from SceneObjectLoader and inserting an entry into
the static map object_loaders according to the tag you wish to use for the
object (<triangle> means "triangle", etc.).


Extending to Multithreading
---------------------------
Multithreading would be quite easy to implement, if it weren't for the camera
controls. Nonetheless it is probably only a day or two of work. The way that the
render is performed is by initializing a set of Samples, which represent pixels
and the ray that will be used to determine the value of the pixel. These are
stored in a vector in the Camera class.

My intent was to split up this vector by assigning each of several threads equal
length portions of it. Since neighboring pixels are likely to be colored by the
same object, cache coherency will lead to an important speedup and it is
worthwhile to have a thread process a contiguous region of pixels.

Anyways, if you just split up the vector into pieces, and had each thread
process passes on all of the pieces belonging to it, that would be enough to
make this multithreaded.

Performance was already very good, so I didn't worry about it too much.


Dependencies
------------
Kangaroo depends on SFML for its graphical display and image saving, Eigen for
vector math, and gtest for testing. These dependencies should be satisfied by
CMake, but if not, you can install them manually and try again.
