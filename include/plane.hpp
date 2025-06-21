#pragma once

class Plane {
public:
    int x, y, dir;
    Plane(int startX, int startY, int direction);
    void update(int width);
};
