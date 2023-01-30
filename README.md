# Snake by C++

A simple game like [*Snake*](https://en.wikipedia.org/wiki/Snake_(video_game_genre)) written by C++, in order to learn C++ and its modern development.

# Dependencies

- Linux
  - I tested it on Arch Linux on Windows Subsystem for Linux 2.
  - *Windows may be also OK but I have not tested.*
- C++ compiler with C++ 11 support
- GNU ncurses
- CMake (>= 3.0)

## Build

```shell
mkdir build
cd build
cmake ..
make
```

## Usage

```shell
# In build/ directory
./snake 20 25
```

Replace `20` and `25` to the width and height of the game area you like. But it is not allowed to make them negative or greater than 1000.

Use <kbd>W</kbd>, <kbd>A</kbd>, <kbd>S</kbd>, <kbd>D</kbd> to control the direction. And press <kbd>Q</kbd> to quit.