#include "GameArea.h"

#include <algorithm>

#include <curses.h>
#include <ncurses.h>

GameArea::GameArea(int width, int height) {
    if (width < 0 || width > MAX_WIDTH) {
        throw "The width given is overrange.";
    }

    if (height < 0 || height > MAX_HEIGHT) {
        throw "The height given is overrange.";
    }

    this->width = width;
    this->height = height;

    area.resize(width * height);
    for (auto &q : area) q.push(' ');

    initscr();
    noecho();
    nodelay(stdscr, TRUE);
}

GameArea::~GameArea() {
    endwin();
}

void GameArea::put(Point pt, char ch) {
    area[to_id(pt)].push(ch);
    mvaddch(pt.second, pt.first, ch);
}

void GameArea::take(Point pt) {
    if (area.size() > 1) {
        area[to_id(pt)].pop();
    }
    
    mvaddch(pt.second, pt.first, area[to_id(pt)].top());
}

char GameArea::get(Point pt) {
    return area[to_id(pt)].top();
}

char GameArea::input() {
    return getch();
}

void GameArea::refresh() {
    ::refresh();
}

int GameArea::to_id(Point pt) {
    return pt.first * this->height + pt.second;
}