#ifndef ENGINE
#define ENGINE

#include "snake.hpp"
#include "config.hpp"

class Engine
{
public:
    Config config;
    Snake snake;

    Point fruitPos;
    int score;
    bool gameOver;

    Engine();
    void Setup();
    void GameLogic();
    void SpawnFruit();
    void Input();
    void Initncurses();
    void Render();
    void Close();
    void SleepTime() const;
};


#endif