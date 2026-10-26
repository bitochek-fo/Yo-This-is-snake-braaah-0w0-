#include "engine.hpp"

int main() {
    Engine game;

    game.Setup();

    while (!game.gameOver) {
        game.Render();
        game.Input();
        game.GameLogic();
        game.SleepTime();
    }

    game.Close();

    return 0;
}