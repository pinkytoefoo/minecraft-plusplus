# minecraft-plusplus

A minimalistic **minecraft clone** built from scratch in **C++** using **OpenGL**

# preview
https://github.com/user-attachments/assets/565d9330-d81a-404d-9639-d2b12d7ff514

# dependencies

this project relies on the following core libraries to handle windowing, math, rendering, and gui:

* **OpenGL** – graphics rendering API.
* **GLFW** – cross-platform window creation and input handling.
* **GLM** – header-only mathematics library for graphics and matrix transformations.
* **stb_image** – lightweight, single-file public domain library for loading textures.
* **Dear ImGui** – Bloat-free immediate mode graphical user interface for debugging and configuration.

# getting started

## prerequisites
you must have a modern C++ compiler (supporting C++20 or higher) and **CMake v3.24** installed on your system.

## installation & build
1. **cloning the repo:**
   ```bash
   git clone https://github.com/pinkytoefoo/minecraft-plusplus
   cd minecraft-plusplus
   ```
2. **generating build files:**
   ```bash
   mkdir build && cd build
   cmake ..
   cmake --build .
   ```
3. **running the executable:**
   ```bash
   ./MC-Clone
   ```


# todos!

track the progress of features planned for this project:

- [x] basic opengl / glfw / imgui setup
- [x] renders basic voxels
- [ ] camera movement
- [ ] chunk management system
- [ ] terrain generation
- [ ] main & settings menu
- [ ] voxel and vertex optimization
- [ ] player movement & physics
- [ ] collisions
- [ ] day / night lighting cycle
