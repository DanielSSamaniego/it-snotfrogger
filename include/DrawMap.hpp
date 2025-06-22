#pragma once
#include <SFML/Graphics.hpp>
#include <array>

using namespace std;
using namespace sf;

void draw_map(const array<bool, 5>& i_swamp, RenderWindow& i_window);