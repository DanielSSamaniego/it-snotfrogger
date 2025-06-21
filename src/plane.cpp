#include "plane.hpp"

Plane::Plane(int startX, int startY, int direction) {
    x = startX;
    y = startY;
    dir = direction;
}

void Plane::update(int width) {
    x += dir;
    if (x < 0) x = width - 1;
    if (x >= width) x = 0;
}