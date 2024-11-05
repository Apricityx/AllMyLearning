#include "position.h"

Position::Position() : x(0), y(0) {}

Position::Position(int x, int y) : x(x), y(y) {}

int Position::getX() const {
    return x;
}

int Position::getY() const {
    return y;
}
