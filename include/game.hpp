#pragma once

#include "player.hpp"
#include "plane.hpp"
#include <vector>

class Game {
private:
    const int width = 20;
    const int height = 10;
    bool gameOver;
    Player player;
    std::vector<Car> cars;

public:
    Game();
    void run();
private:
    void setup();
    void draw();
    void input();
    void logic();
};