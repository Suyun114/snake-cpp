#include "utils.h"

int randint(int l, int r) {
    static std::random_device rd;
    static std::mt19937 rng(rd());

    return std::uniform_int_distribution<int>(l, r)(rng);
}