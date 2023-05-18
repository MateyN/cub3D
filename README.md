## Project Structure

```shell
./
├── libs		  # libraries: mlx (MinilibX), libft
├── includes 	          # C header files
├── srcs                  # C source files
├── assets		  # game assets
├── maps		  # game maps
├── Makefile
└── README.md
```

## Environment

- MacOS 13.3.1 (a) (Ventura, Intel)

Developed and tested in this environment.

## Compile

### Mandatory

To compile the mandatory version, run the lines below.

```shell
$ git clone https://github.com/MateyN/cub3d
$ make
```

## Execute

Run compiled executable file in the root folder.

```shell
$ ./cub3d /path/to/maps

# example
$ ./cub3d maps/valid/maze.cub

$ ./cub3d maps/valid/normal.cub

$ ./cub3d maps/valid/egypt.cub
```

### Controls

- `ESC` to exit a game
- `WASD` to move
- `arrow keys` to rotate

## Example

<p align="center">
<img src="./example.gif" alt="animated" />
</p>
