# Snake by C++

A simple game like [*Snake*](https://en.wikipedia.org/wiki/Snake_(video_game_genre)) written by C++, in order to learn C++ and its modern development.

# Dependencies

- Linux
  - I tested it on Arch Linux on Windows Subsystem for Linux 2.
  - *Windows may be also OK but I have not tested.*
- C++ compiler with C++ 17 support
  - I used GCC 12.2.1.
- GNU ncurses

## Build

```shell
mkdir build
g++ main.cpp -o build/snake -lncurses -std=c++17
```

## Usage

```shell
# In build/ directory
./snake 20 25
```

You can replace `20` and `25` to the width and height of the game area you like. But it is not allowed to make them negative or greater than 1000.