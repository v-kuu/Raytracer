# Software raytracer written in C++
Utilizes SDL3 to handle window management, keyboard input etc.

Work in progress

## Installation (Linux)
Clone the repo wherever and then in the repository root:
```bash
mkdir -p build
(cd build && cmake ..)
cmake --build build -4
```
You will then find the binary in the build directory:
```bash
./build/raytracer
```

## Features

- Spheres and triangles
- A thread pool to distribute rendering to multiple threads
- Bounding volume hierarchy (BVH) to group objects in a scene to drastically cut ray intersection tests
- Shading uses Blinn-Phong reflection model
- Quaternions for camera rotations

## Todo

- Handle multiple lights
- Early exits from rendering for inputs
- Full SAH for BVH
- Textures
- Scene files and parser
- Soft shadows
- GPU
