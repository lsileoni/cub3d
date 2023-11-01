# cub3D

	A simple raycasting engine in C

## Introduction

"Cub3D" is a project inspired by the iconic game [Wolfenstein 3D](https://en.wikipedia.org/wiki/Wolfenstein_3D), one of the pioneers of first-person shooter (FPS) games developed in the early 90s. The project's primary goal is to create a pseudo 3D view using the [raycasting](https://en.wikipedia.org/wiki/Ray_casting#:~:text=Ray%20casting%20is%20the%20most,scenes%20to%20two%2Ddimensional%20images.) method to render a 2D map loaded from a file. It serves as a foundational framework for future game development projects.

This raycasting engine is designed to work on MacOS and Linux platforms.

## Building and running the project

1. Clone the repository and initialize submodules:
```
git clone https://github.com/lsileoni/cub3d.git
git submodule update --init --recursive
```

2. Build the project:
```
make
```

3. Run the program with a map file (e.g., "subject_example.cub"):
```
./cub3D maps/subject_example.cub
```

## User Interaction

Once the program is running, users can interact with it as follows:

- Use `W`, `S`, `A`, and `D` keys to move forward, backward, left, and right, respectively.
- Utilize the arrow keys or the mouse to rotate the view left or right.
- Press `ESC` to exit and quit the program.

## Showcase

Here's a glimpse of what the program looks like in action:

![Cub3D Showcase](./.showfile/show3.gif)

## Dependencies

This project was implemented entirely in the C programming language and relies on the following libraries:

- **MLX42**: A minimalist graphics library that interfaces with the X-window system and leverages GLFW and OpenGL under the hood for graphics rendering. You can find MLX42 [here](https://github.com/codam-coding-college/MLX42).

- **LibFT**: Our custom standard library that provides various utility functions used in the project.
