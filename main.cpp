#include <cstdio>
#include <cstdlib>
#include <cctype>

#include <random>
#include <string>
#include <utility>
#include <deque>

#include <curses.h>
#include <ncurses.h>
#include <unistd.h>

using Point = std::pair<int, int>;

const int MAX_WIDTH = 1000;
const int MAX_HEIGHT = 1000;
const int SLEEP_TIME_MS = 250;

template<typename RangeType>
auto randint(RangeType l, RangeType r) {
    static std::random_device rd;
    static std::mt19937 rng(rd());

    return std::uniform_int_distribution<RangeType>(l, r)(rng);
}

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

        std::deque<Point> snake;
        
        snake.emplace_back(randint(0, width - 1), randint(0, height - 1));
        snake.emplace_back(snake[0].first + 1, snake[0].second);

        if (snake[1].first == width) {
            snake[0].first = width - 2;
            snake[1].first = width - 1;
        }

        for (auto [ x, y ] : snake) {
            mvaddch(y, x, '*');
        }

        Point food(randint(0, width - 1), randint(0, height - 1));
        mvaddch(food.second, food.first, '@');

        refresh();

        Point direction(1, 0);

        while (true) {
            snake.emplace_back(
                (snake.back().first + direction.first + width) % width,
                (snake.back().second + direction.second + height) % height
            );

            if (snake.back() == food) {
                food = { randint(0, width - 1), randint(0, height - 1) };
                mvaddch(food.second, food.first, '@');
            } else {
                mvaddch(snake.front().second, snake.front().first, ' ');
                snake.pop_front();
            }

            int key = tolower(getch());
            refresh();

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

            mvaddch(snake.back().second, snake.back().first, '*');
            refresh();

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