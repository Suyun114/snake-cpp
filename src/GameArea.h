#pragma once

#include <utility>
#include <stack>
#include <vector>

class GameArea {
    std::vector< std::stack<char> > area;

public:
    using Point = std::pair<int, int>;

    static const int MAX_WIDTH = 1000;
    static const int MAX_HEIGHT = 1000;

    int width, height;

    GameArea(int height, int width);
    ~GameArea();

    void put(Point pt, char ch);
    void take(Point pt);
    char get(Point pt);
    char input();
    void refresh();

private:
    int to_id(Point pt);
};