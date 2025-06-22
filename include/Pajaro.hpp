#pragma once
#include <SFML/Graphics.hpp>
#include <array>

using namespace std;
using namespace sf;

class Pajaro
{
    bool dead;

    short x;

    unsigned char animation_timer;
    unsigned char current_frame;
    // Dirección actual del pájaro (0: arriba, 1: derecha, 2: abajo, 3: izquierda)
    unsigned char direction;

    unsigned short y;

    // Estado anterior de las teclas de control
    array<bool, 4> control_keys;

    Sprite sprite;
    Texture texture;

public:
    Pajaro();

    bool get_dead() const;

    bool update_altitude(array<bool, 5>& i_altitude_zones);

    unsigned short get_y() const;

    void draw(RenderWindow& i_window);
    void move(char i_value);
    void reset();
    void set_dead();
    void update();

    IntRect get_rect() const;
};