//
// Created by apricityx on 24-11-3.
//

#ifndef POSITION_H
#define POSITION_H

class Position {
public:
    Position();

    Position(int x, int y);

    // getter
    int getX() const;

    int getY() const;

private:
    int x;
    int y;
};

#endif //POSITION_H
