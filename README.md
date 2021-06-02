# Arcade

## Build

### Cross platform

- [x] Linux (GCC/GNU)
- [x] Windows (MSVC)
- [x] MacOS (GCC/GNU)

### Build with CMake

```bash
$ cmake -B build -DFETCH_DEPENDENCIES=True -DCMAKE_BUILD_TYPE=Release
$ cmake --build build
$ ls ./arcade ./lib/
./arcade(.exe)

./lib/:
arcade_menu(.so/.dylib/.dll)
arcade_ncurses(.so/.dylib/.dll)
arcade_nibbler(.so/.dylib/.dll)
arcade_pacman(.so/.dylib/.dll)
arcade_sdl2(.so/.dylib/.dll)
arcade_sfml(.so/.dylib/.dll)
```

### Build on Linux/MacOS

```
$ make
```

### Build on Windows

```
$ ./make.bat
```

## Usage

```
./arcade
./arcade path_to_graphic_lib
./arcade path_to_graphic_lib path_to_game_lib
./arcade path_to_graphic_lib -n username
./arcade path_to_graphic_lib path_to_game_lib --name username
```

## Controls

- P -> pause/resume game
- F1 -> previous graphic lib
- F2 -> next graphic lib
- F3 -> previous game lib
- F4 -> next game lib
- F5 -> reload game

## Libraries

- Graphic:
  - [x] arcade_sdl2 (SDL2) (Mandatory)
  - [x] arcade_sfml (SFML)
  - [x] arcade_ncurses (Ncurses) (Mandatory)
- Game:
  - [x] arcade_nibbler (Nibbler)
  - [x] arcade_pacman (Nibbler)
