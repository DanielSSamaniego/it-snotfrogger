#include "game.hpp"
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <ctime>

Game::Game() : player(width / 2, height - 1), gameOver(false) {}

void Game::setup() {
    
Airplanes.clear();
    for (int i = 2; i < height - 1; i += 2) {
        int dir = (rand() % 2 == 0) ? 1 : -1;
        Airplanes.emplace_back(rand() % width, i, dir);
    }
}

void Game::draw() {
    system("cls");
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            bool printed = false;

            if (x == player.x && y == player.y) {
                std::cout << "P";
                printed = true;
            } else {
                for (avion& plane : airplanes) {
                    if (x == car.x && y == car.y) {
                        std::cout << "C";
                        printed = true;
                        break;
                    }
                }
            }

            if (!printed) std::cout << ".";
        }
        std::cout << "\n";
    }
}

void Game::input() {
    if (_kbhit()) {
        char ch = _getch();
        player.move(ch, width, height);
    }
}

void Game::logic() {
    for (avion& avion : airplanes) {
        plane.update(width);
        if (plane.x == player.x && plane.y == player.y) {
            gameOver = true;
        }
    }

    if (player.y == 0) {
        std::cout << "¡GANASTE!\n";
        gameOver = true;
    }
}

void Game::run() {
    srand(time(0));
    setup();
    while (!gameOver) {
        draw();
        input();
        logic();
        Sleep(100);
    }
    std::cout << "Juego terminado.\n";
    system("pause");
}
