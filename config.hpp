#ifndef CONFIG
#define CONFIG

struct Config
{
    static constexpr int width = 60;
    static constexpr int heigth = 30;
    static constexpr int gameSpeed = 100000;
    static constexpr int pointsPerFruit = 10;
};

struct Point
{
    int x, y;
    bool operator==(Point& other) {
        return x == other.x && y == other.y;
    } 
};

enum Direction {STOP, UP, DOWN, LEFT, RIGHT};

#endif