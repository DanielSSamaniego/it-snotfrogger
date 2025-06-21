#pragma once

class Player {
public:
    int x, y;
    Player(int startX, int startY);
    void move(char input, int width, int height);
};