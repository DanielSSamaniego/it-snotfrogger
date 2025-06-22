#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Nube.hpp"
#include "GloboAerostatico.hpp"
#include "Pajaro.hpp"

using namespace std;
using namespace sf;

class ClimaControl
{
    vector<Nube> nubes;
    vector<GloboAerostatico> globos; 

public:
    ClimaControl(unsigned char i_level);

    void draw(RenderWindow& i_window);
    void generate_level(unsigned char i_level);
    void update(Pajaro& i_pajaro);
};