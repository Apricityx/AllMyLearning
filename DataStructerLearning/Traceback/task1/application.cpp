#include "application.h"
#include <iostream>
#include <vector>
#include <cmath>

std::vector<Position> solution;

void Application::initialize() {
    solution.clear();
}

Position Application::getStartPosition() {
    return Position(0, 0); // 从第0行开始
}

bool Application::isValid(const Position &p) {
    for (const Position &pos: solution) {
        if (pos.getX() == p.getX() || pos.getY() == p.getY() ||
            std::abs(pos.getX() - p.getX()) == std::abs(pos.getY() - p.getY())) {
            return false; // 如果在同一行、列或对角线上，则位置无效
        }
    }
    return true;
}

void Application::progress(const Position &p) {
    solution.push_back(p); // 添加新的位置到解向量中
}

bool Application::success(const Position &p) {
    return solution.size() == 8; // 检查是否放置了8个皇后
}

void Application::goBack(const Position &p) {
    if (!solution.empty()) {
        solution.pop_back(); // 回退一步
    }
}

void Application::print() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (solution[i].getY() == j) {
                std::cout << "+ ";
            } else {
                std::cout << ". ";
            }
        }
        std::cout << std::endl;
    }
    // for (const Position& pos : solution) {
    //     std::cout << "(" << pos.getX() << ", " << pos.getY() << ")" << std::endl;
    // }
}

// Iterator 类实现
Application::Iterator::Iterator() : currItrPosPtr(new Position(0, 0)) {
}

Application::Iterator::Iterator(const Position &currP) : currItrPosPtr(new Position(currP.getX(), 0)) {
}

Application::Iterator::~Iterator() {
    delete static_cast<Position *>(currItrPosPtr);
}

Position Application::Iterator::getNextPosition() {
    Position *currentPos = static_cast<Position *>(currItrPosPtr);
    int x = currentPos->getX();
    int y = currentPos->getY();

    if (y < 7) {
        y++; // 移动到当前行的下一列
    } else {
        x++; // 移动到下一行的第一个位置
        y = 0;
    }

    delete currentPos;
    currItrPosPtr = new Position(x, y);
    return *static_cast<Position *>(currItrPosPtr);
}

bool Application::Iterator::noNextPosition() {
    Position *currentPos = static_cast<Position *>(currItrPosPtr);
    return currentPos->getX() >= 8; // 检查行数是否超过8
}
