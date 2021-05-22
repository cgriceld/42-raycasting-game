# Raycasting game

**Raycasting game inspired by Wolfenstein 3D**\
42 graphical project. The code is written in accordance with The Norm (42 coding style).\
Raycasting algorithm is done using [this](https://lodev.org/cgtutor/raycasting.html) tutorial, but with some my improvements and optimizations.\
Besides the raycasting algorithm itself, the project includes most of the parsing and an error handling manager for invalid input data.

<img width="597" alt="cub3d" src="https://user-images.githubusercontent.com/62188694/118179348-db4a0c80-b43d-11eb-8e41-750582ae6d3f.png">

## project structure
* *`engine` folder* -- source files (`utils` folder contains some functions from my own [C library](https://github.com/linpoa/libft).
* *`maps` folder* -- `.cub` files with map examples.
* *`mlx` folder* -- 42 graphical library.
* *`textures` folder* -- wall and sprite textures, taken from Wolfenstein 3D, copyright by ID Software.

***Makefile***
* *`make`* -- compiles `cub3D` executable.
* *`make demo1`* -- compiles `cub3D` and launches the game with `barrels.cub` map.
* *`make demo2`* -- same to `make demo1`, but with `subj.cub` map.
* *`clean`* -- deletes object files.
* *`fclean`* -- deletes object files, `cub3D`, `cub3D.bmp` and runs `clean` rule in `mlx` folder.
* *`re`* -- runs `fclean` and recompiles.

## launching

Start game using following syntax : `./cub3D file.cub [--save]`
* `file.cub` -- nesessary option, file that config map and other parameters, you can find examples in `maps` folder.
* `--save` -- save option that will launch non-interactive mode, makes screenshot of first rendered image, saves it in bmp format (`cub3D.bmp`) and quit.

You can choose from existing maps (`maps` folder) or create your own one (see below).

## file.cub config

* *R x y* -- screen resolution, x > 0, y > 0. If defined resolution is greater that current screen resolution and there is no `--save` option, it will be resized to fit the current screen. In `--save` mode resolution can be greater than current screen.
* *NO path_to_texture* -- texture for north side of the wall.
* *EA path_to_texture* -- texture for east side of the wall.
* *SO path_to_texture* -- texture for south side of the wall.
* *WE path_to_texture* -- texture for west side of the wall.
* *S path_to_texture* -- texture for sprite.
* *C R,G,B* -- ceiling color in RGB format.
* *F R,G,B* -- floor color in RGB format.

These params can be set in any order in the file, but before the map; they can be separated by any number of empty lines; within a parameter there can be any number of spaces between the arguments.\
For `C` and `F` params `R,G,B` argument also can be separated by spaces, e.g. `  42   ,   42   ,42   ` is a valid input.

* *map*\
Map can consists from 4 possible characters -- space, 1 for wall, 0 for blank space, and 2 for sprite. Map also must contain init position of the player -- N (looks to the north), E (to the east), S (to the south), W (to the west). There must be no empty lines inside or below the map.

## gameplay

Use WASD for moving, left arrow to turn head to the left and right arrow to turn head to the right.
Press red cross on the window or ESC to quit.
