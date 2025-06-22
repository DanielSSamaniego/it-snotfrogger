#include <array>
#include <chrono>
#include <cmath>
#include <SFML/Graphics.hpp>

#include "include/Pajaro.hpp"
#include "include/Global.hpp"
#include "include/Nube.hpp"

Nube::Nube(unsigned char i_type, unsigned char i_x, unsigned char i_y) :
    direction(i_y % 2),
    x(CELL_SIZE * i_x),
    animation_timer(AGUILA_ANIMATION_SPEED),
    current_frame(0),
    size(2 * CELL_SIZE * std::min(3, 1 + i_type)),
    type(i_type),
    y(CELL_SIZE * (2 + i_y))
{
    if (0 == direction)
    {
        if (x >= CELL_SIZE * MAP_WIDTH)
        {
            x -= static_cast<short>(CELL_SIZE * floor(1.5f * MAP_WIDTH));
        }
    }
    else
    {
        if (x <= -CELL_SIZE * floor(0.5f * MAP_WIDTH))
        {
            x += static_cast<short>(CELL_SIZE * floor(1.5f * MAP_WIDTH));
        }
    }

    if (2 > i_y)
    {
        speed = SLOW_SPEED;
    }
    else if (4 > i_y)
    {
        speed = NORMAL_SPEED;
    }
    else
    {
        speed = FAST_SPEED;
    }
}

bool Nube::check_pajaro(const Pajaro& i_pajaro) const
{
    if (3 > type) //Cuando la nube es normal
    {
        return i_pajaro.get_rect().intersects(sf::IntRect(static_cast<short>(x + floor(0.25f * CELL_SIZE)), y, static_cast<short>(size - floor(0.5f * CELL_SIZE)), CELL_SIZE));
    }
    else //Cuando es un águila (antes cocodrilo)
    {
        //Verificamos la colisión asumiendo que el águila es una nube de tamaño mediano
        return i_pajaro.get_rect().intersects(sf::IntRect(static_cast<short>(x + floor(0.25f * CELL_SIZE)), y, static_cast<short>(size - floor(2.5f * CELL_SIZE)), CELL_SIZE));
    }
}

void Nube::draw(sf::RenderWindow& i_window)
{
    texture.loadFromFile("assets/images/Nubes.png");

    sprite.setPosition(x, y);
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(6 * CELL_SIZE * current_frame, CELL_SIZE * type, size, CELL_SIZE));

    //No invertiremos las nubes normales
    if (1 == direction && 3 == type)
    {
        sprite.setTextureRect(sf::IntRect(size + 6 * CELL_SIZE * current_frame, CELL_SIZE * type, -size, CELL_SIZE));
    }

    i_window.draw(sprite);
}

void Nube::update(bool i_move_pajaro, Pajaro& i_pajaro)
{
    if (3 == type) //Animación del águila
    {
        if (0 == animation_timer)
        {
            current_frame = (1 + current_frame) % 2;
            animation_timer = AGUILA_ANIMATION_SPEED;
        }
        else
        {
            animation_timer--;
        }
    }

    if (0 == direction) //Movimiento hacia la derecha
    {
        x += speed;

        if (1 == i_move_pajaro)
        {
            i_pajaro.move(speed);
        }

        if (x >= CELL_SIZE * MAP_WIDTH)
        {
            x -= static_cast<short>(CELL_SIZE * floor(1.5f * MAP_WIDTH));
        }
    }
    else //Movimiento hacia la izquierda
    {
        x -= speed;

        if (1 == i_move_pajaro)
        {
            i_pajaro.move(-speed);
        }

        if (x <= -CELL_SIZE * floor(0.5f * MAP_WIDTH))
        {
            x += static_cast<short>(CELL_SIZE * floor(1.5f * MAP_WIDTH));
        }
    }
}

