#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Avion.hpp"  
#include "Pajaro.hpp" 

using namespace std;
using namespace sf;

class TorreControl
{
	vector<Avion> aviones;  
public:
	TorreControl(unsigned char i_level);

	void draw(RenderWindow& i_window);
	void generate_level(unsigned char i_level);
	void update(Pajaro& i_pajaro);  
};