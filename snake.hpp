#ifndef SNAKE
#define SNAKE

#include "config.hpp"
#include <deque>

class Snake {
public:
    Point headPos;
    std::deque<Point> snakeBody;
    Direction dir;

    void Reset(int startX, int startY) {
        headPos = {startX, startY};
        snakeBody.clear();
        dir = STOP;
}

    bool SnakeselfCollision() {
        for (auto& chast : snakeBody) {
            if (chast == headPos) return true; 
        }
        return false;
    }

    void Move() {
        switch (dir)
        {
            case LEFT: headPos.x--; break;
            case RIGHT: headPos.x++; break;
            case UP: headPos.y--; break;
            case DOWN: headPos.y++; break;
            default: break; 
        }
    }
};

#endif