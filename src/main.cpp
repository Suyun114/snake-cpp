#include "main.h"
#include "utils.h"
#include "GameArea.h"

#include <cstdio>
#include <cstdlib>
#include <cctype>

#include <queue>

#include <unistd.h>

int main(int argc, char **argv) {
    try {
        if (argc < 3) {
            throw "Arguments given are too few.";
        }

        GameArea area(atoi(argv[1]), atoi(argv[2]));
        std::queue<GameArea::Point> snake;

        snake.emplace(randint(0, area.width - 1), randint(0, area.height - 1));
        snake.emplace(snake.front().first + 1, snake.front().second);

        if (snake.back().first == area.width) {
            snake.front().first = area.width - 2;
            snake.back().first = area.width - 1;
        }

        area.put(snake.front(), SNAKE_CHAR);
        area.put(snake.back(), SNAKE_CHAR);

        GameArea::Point food(randint(0, area.width - 1), randint(0, area.height - 1));
        area.put(food, FOOD_CHAR);

        GameArea::Point direction(1, 0);

        while (true) {
            int key = tolower(area.input());

            if (key == 'q') {
                break;
            }

            if (key == 'w' || key == 'a' || key == 's' || key == 'd') {
                if (direction.first) {
                    if (key == 'w' || key == 's') {
                        direction = (key == 'w' ? GameArea::Point(0, -1) : GameArea::Point(0, 1));
                    }
                } else {
                    if (key == 'a' || key == 'd') {
                        direction = (key == 'a' ? GameArea::Point(-1, 0) : GameArea::Point(1, 0));
                    }
                }
            }

            snake.emplace(
                (snake.back().first + direction.first + area.width) % area.width,
                (snake.back().second + direction.second + area.height) % area.height
            );

            if (snake.back() == food) {
                area.take(food);
                food = { randint(0, area.width - 1), randint(0, area.height - 1) };
                area.put(food, FOOD_CHAR);
            } else {
                area.take(snake.front());

                if (snake.front() != food && area.get(snake.front()) == '@') {
                    area.take(snake.front());
                }
                
                snake.pop();
            }

            area.put(snake.back(), SNAKE_CHAR);

            area.refresh();
            usleep(SLEEP_TIME_MS * 1000);
        }
    } catch (const char *msg) {
        fputs(msg, stderr);

        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}