# Software raytracer written in C++
Utilizes SDL3 to handle window management, keyboard input etc. It is included as a vendored static library as per their zlib license.

Work in progress

## Features

- A thread pool to distribute rendering to multiple threads
- Bounding volume hierarchy (BVH) to group objects in a scene to drastically cut ray intersection tests
- Shading uses Blinn-Phong reflection model
- Quaternions for camera rotations
