#include "player.h"

Player::Player(int startX, int startY) {
    x = startX;
    y = startY;
}

void Player::move(char input, int width, int height) {
    if (input == 'a' && x > 0) x--;
    if (input == 'd' && x < width - 1) x++;
    if (input == 'w' && y > 0) y--;
    if (input == 's' && y < height - 1) y++;
}