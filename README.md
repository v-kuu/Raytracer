# Software raytracer written in C++
Utilizes SDL3 to handle window management, keyboard input etc.

Work in progress

## Installation (Linux)
Clone the repo wherever and then in the repository root:
```bash
cmake -B build
cmake --build build -j4
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
- Textures and normal maps

## Todo

- PBR approach
- Handle multiple lights
- Full SAH for BVH
- Scene files and parser
- Soft shadows
- GPU
