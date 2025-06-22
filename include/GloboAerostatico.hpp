#pragma once
#include <SFML/Graphics.hpp>
#include "Pajaro.hpp"

using namespace sf;

class GloboAerostatico
{
    bool direction;      // true = derecha
    bool diving; 
    bool diving_down;

    short x;       
    unsigned short y;   

    // Animación
    unsigned char animation_timer;
    unsigned char current_frame;
    unsigned char diving_state;
    unsigned char diving_timer;
    unsigned char size;
    unsigned char speed; 

    Sprite sprite;     
    Texture texture;   

public:
    GloboAerostatico(bool i_diving, unsigned char i_size, unsigned char i_x, unsigned char i_y);


    bool check_pajaro(const Pajaro& i_pajaro) const;  
    void draw(RenderWindow& i_window);
    void update(bool i_move_pajaro, Pajaro& i_pajaro);

    IntRect get_rect() const; // Hitbox
};