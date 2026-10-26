#include "engine.hpp"

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <unistd.h>
#include <ncurses.h>
#include <vector>

Engine::Engine() { 
    srand(time(NULL));
}


void Engine::Setup() {
    Initncurses();
    score = 0;
    gameOver = false;
    snake.Reset(config.width/2, config.heigth/2);
    SpawnFruit();
}


void Engine::SpawnFruit() {
    fruitPos.x = rand() % (config.width - 2) + 1;
    fruitPos.y = rand() % (config.heigth - 2) + 1;
}


void Engine::Input() {
    int ch = getch();
    switch (ch)
    {
        case KEY_LEFT: if (snake.dir != RIGHT) snake.dir = LEFT; break;
        case KEY_RIGHT: if (snake.dir != LEFT) snake.dir = RIGHT; break;
        case KEY_DOWN: if (snake.dir != UP) snake.dir = DOWN; break;
        case KEY_UP: if (snake.dir != DOWN) snake.dir = UP; break;
        case 'q': gameOver = true; break;
    }
}


void Engine::Initncurses() {
    initscr();
    clear();
    curs_set(0);
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
}


void Engine::GameLogic() {
    if (snake.dir == STOP) return;

    Point prevHead = snake.headPos;
    Input();
    snake.Move();

    if (snake.headPos.x <= 0 || snake.headPos.x >= config.width - 1 ||
        snake.headPos.y <= 0 || snake.headPos.y >= config.heigth - 1) {
        gameOver = true;
        return;
    }

    if (snake.SnakeselfCollision()) {
        gameOver = true;
        return;
    }

    if (snake.headPos == fruitPos) {
        score += config.pointsPerFruit;
        snake.snakeBody.push_front(prevHead);
        SpawnFruit();
    } else if (!snake.snakeBody.empty()) {
        snake.snakeBody.push_front(prevHead);
        snake.snakeBody.pop_back();
    }
}


void Engine::Render() {
    erase();

    std::vector<std::vector<char>> field(config.heigth, std::vector<char>(config.width, ' '));

    for (int i = 0; i < config.width; i++) {
        field[0][i] = '#';
        field[config.heigth - 1][i] = '#';
    }

    for (int i = 0; i < config.heigth; i++) {
        field[i][0] = '#';
        field[i][config.width - 1] = '#';
    }

    field[fruitPos.y][fruitPos.x] = '@';

    for (auto& cell : snake.snakeBody) {
        if (cell.x > 0 && cell.x < config.width && cell.y > 0 && cell.y < config.heigth) {
            field[cell.y][cell.x] = 'o';
        }
    }

    field[snake.headPos.y][snake.headPos.x] = 'O';

    for (int i = 0; i < config.heigth; i++) {
        for (int j = 0; j < config.width; j++) {
            printw("%c", field[i][j]);
        }
        printw("\n");
    }
    printw("Score: %d\n", score);
    printw("Press 'q' to Exit\n");
    refresh();
}


void Engine::Close() {
    endwin();
    std::cout << "Game Over! Your final score: " << score << std::endl;
}


void Engine::SleepTime() const{
    usleep(config.gameSpeed);
}