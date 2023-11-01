# cub3D

	A simple raycasting engine in C.

## More details

This project is inspired by the world-famous [Wolfenstein 3D](https://en.wikipedia.org/wiki/Wolfenstein_3D) game. The first ever FPS game, developed in the early 90's.

The goal was to make a dynamic view inside a *map* parsed from a file, using the [raycasting](https://en.wikipedia.org/wiki/Ray_casting#:~:text=Ray%20casting%20is%20the%20most,scenes%20to%20two%2Ddimensional%20images.) method.

## Building and running the project
```
git submodule update --init --recursive
make && ./cub3D maps/subject_example.cub
```

## Showcase

The program accepts the following input on run-time:

* `W,S,A,D` to move forward, backward, left and right, respectively.
* `Arrows` or `Mouse` to rotate left or right.
* `ESC` to quit the program.


![](./.showfile/show3.gif)


## How?

This project was entirely written in C, using [MLX42](https://github.com/codam-coding-college/MLX42) and our LibFT library.

MLX42 is a minimalist graphics library, which interfaces with the X-window system and implements glfw under the hood for graphics.
