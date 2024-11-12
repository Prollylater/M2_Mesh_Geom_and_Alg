# Mesh and algorithmic geometry Labwork

This labwork concerned the implementation of a 
The current_implementation add an UI with IMGUI and a quick modification of the mini engine i worked on another project.
 ## Features we aimed for
-Visualisation of a 3d, a 2d Mesh and a cloud point (only obj and txt were tested) : Wireframe, Normal calculated with Laplacian and Mesh Curvature
-Triangulation of a 2d mesh with Delaunay's triangle with iterative method and Bowyer-Watson).
-Ray casting to allow user to add a point/or flip and edge and see the triangulation unfold (Still working on that one)

 ##  Image of some of the results: (Most are before the UI)
Delaunay Mesh:
![image](https://github.com/user-attachments/assets/9f448411-b5da-485b-b731-26ded8a1c777)

Delaunay Mesh Smaller:
![image](https://github.com/user-attachments/assets/a605ee2b-7e9e-4658-9636-e4db063eeff1)

Delaunay Mesh Smaller with 3d coordinate:
![image](https://github.com/user-attachments/assets/32cbce33-1ded-4afb-b985-a08984c563b7)

Normals calculated with Laplacian:
![TItinorm-1](https://github.com/user-attachments/assets/83fe3b85-43bc-44c2-a2ae-84fe35eece9a)

Curvature visualisation:
![Titicurves-1](https://github.com/user-attachments/assets/817e9734-cc59-4aa7-9745-f71af0aa48c9)


## Building and Running the Project

To build the project, follow these steps:

1. **Clone the repository:**
   ```bash
   git clone https://github.com/Prollylater/SeeThing.git
   cd
2. Install dependency
   **GLFW:**
     ```bash
     sudo apt install libglfw3-dev
     ```
   **CMAKE:**
     ```bash
      sudo apt install cmake
     ```
3. Building and running
    ```bash
      mkdir build
      cd build
      cmake ..
      make
    ````







Some crude debug may are still in the current build
