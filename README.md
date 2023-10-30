# cub3D

	A simple raycasting engine in C.

## More details

This project is inspired by the world-famous [Wolfenstein 3D](https://en.wikipedia.org/wiki/Wolfenstein_3D) game. The first ever FPS game, developed in the early 90's.

The goal was to make a dynamic view inside a *maze*, using the [raycasting](https://en.wikipedia.org/wiki/Ray_casting#:~:text=Ray%20casting%20is%20the%20most,scenes%20to%20two%2Ddimensional%20images.) method.

## Showcase

The program accepts the following input on run-time:

* `W,S,A,D` to move forward, backward, left and right, respectively.
* `Arrows` or `Mouse` to turn left and right.
* `ESC` to quit the program.


![](./.showfile/show3.gif)


## How?

This project was entirely written in C, using MLX42 and our LibFT library.

MLX42 is a minimalist graphics library, provided by our school, that allows you to quickly open a window and draw in it.