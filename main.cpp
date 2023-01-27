#include "main.h"
#include "utils.h"

#include <cstdio>
#include <cstdlib>
#include <cctype>

#include <queue>

#include <curses.h>
#include <ncurses.h>
#include <unistd.h>

int main(int argc, char **argv) {
    try {
        if (argc < 3) {
            throw "Arguments given are too few.";
        }

        int width = atoi(argv[1]);
        int height = atoi(argv[2]);

        if (width < 0 || width > MAX_WIDTH) {
            throw "The width given is overrange.";
        }

        if (height < 0 || height > MAX_HEIGHT) {
            throw "The height given is overrange.";
        }

        initscr();
        noecho();
        nodelay(stdscr, TRUE);

        std::queue<Point> snake;
        
        snake.emplace(randint(0, width - 1), randint(0, height - 1));
        snake.emplace(snake.front().first + 1, snake.front().second);

        if (snake.back().first == width) {
            snake.front().first = width - 2;
            snake.back().first = width - 1;
        }

        
        mvaddch(snake.front().second, snake.front().first, SNAKE_CHAR);
        mvaddch(snake.back().second, snake.back().first, SNAKE_CHAR);

        Point food(randint(0, width - 1), randint(0, height - 1));
        mvaddch(food.second, food.first, FOOD_CHAR);

        refresh();

        Point direction(1, 0);

        while (true) {
            snake.emplace(
                (snake.back().first + direction.first + width) % width,
                (snake.back().second + direction.second + height) % height
            );

            if (snake.back() == food) {
                food = { randint(0, width - 1), randint(0, height - 1) };
                mvaddch(food.second, food.first, FOOD_CHAR);
            } else {
                mvaddch(snake.front().second, snake.front().first, AREA_CHAR);
                snake.pop();
            }

            int key = tolower(getch());

            if (key == 'w' || key == 'a' || key == 's' || key == 'd') {
                if (direction.first) {
                    if (key == 'w' || key == 's') {
                        direction = (key == 'w' ? Point(0, -1) : Point(0, 1));
                    }
                } else {
                    if (key == 'a' || key == 'd') {
                        direction = (key == 'a' ? Point(-1, 0) : Point(1, 0));
                    }
                }
            }

            mvaddch(snake.back().second, snake.back().first, SNAKE_CHAR);

            refresh();
            usleep(SLEEP_TIME_MS * 1000);
        }

        endwin();
    } catch (const char *msg) {
        fputs(msg, stderr);

        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}