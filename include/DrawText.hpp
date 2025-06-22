#pragma once
#include <SFML/Graphics.hpp>
#include <string>

using namespace std;
using namespace sf;

void draw_text(bool i_center, unsigned short i_x, unsigned short i_y, const string& i_text, RenderWindow& i_window);