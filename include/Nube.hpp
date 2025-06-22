#pragma once
#include <SFML/Graphics.hpp>
#include "Pajaro.hpp"  // Cambiado de Frog.hpp a Pajaro.hpp

using namespace std;
using namespace sf;

class Nube
{
    bool direction;  // Dirección de movimiento de la nube

    short x;  // Posición horizontal

    unsigned char animation_timer;
    unsigned char current_frame;
    unsigned char size;    // Tamaño de la nube
    unsigned char speed;   // Velocidad de movimiento
    unsigned char type;    // Tipo de nube

    unsigned short y;  // Posición vertical

    Sprite sprite;
    Texture texture;

public:
    Nube(unsigned char i_type, unsigned char i_x, unsigned char i_y);

    bool check_pajaro(const Pajaro& i_pajaro) const;

    void draw(RenderWindow& i_window);
    void update(bool i_move_pajaro, Pajaro& i_pajaro);
};