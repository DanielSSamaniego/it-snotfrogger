#pragma once
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Avion
{
	bool direction;

	short x;

	unsigned char size;
	unsigned char speed;
	unsigned char type;

	unsigned short y;

	Sprite sprite;

	Texture texture;
public:
	Avion(unsigned char i_x, unsigned char i_y);

	void draw(RenderWindow& i_window);
	void update();

	IntRect get_rect() const;
};