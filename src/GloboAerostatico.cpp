#include <array>
#include <chrono>
#include <cmath>
#include <SFML/Graphics.hpp>

#include "Pajaro.hpp"
#include "Global.hpp"
#include "GloboAerostatico.hpp"

GloboAerostatico::GloboAerostatico(bool i_diving, unsigned char i_size, unsigned char i_x, unsigned char i_y) :
    direction(i_y % 2),
    diving(i_diving),
    diving_down(1),
    x(CELL_SIZE * i_x),
    animation_timer(AGUILA_ANIMATION_SPEED),
    current_frame(0),
    diving_state(0),
    diving_timer(GLOBO_NAVIGATION_SPEED),
    size(i_size),
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

bool GloboAerostatico::check_pajaro(const Pajaro& i_pajaro) const
{
    // El globo tiene 4 estados de navegación. Si el estado es 3 o 4, el pájaro no puede aterrizar en él.
    if (1 < diving_state)
    {
        return false;
    }
    else
    {
        return i_pajaro.get_rect().intersects(sf::IntRect(static_cast<short>(x + floor(0.25f * CELL_SIZE)), y, static_cast<short>(CELL_SIZE * size - floor(0.5f * CELL_SIZE)), CELL_SIZE));
    }
}

void GloboAerostatico::draw(sf::RenderWindow& i_window)
{
    texture.loadFromFile("assets/images/GloboAerostatico.png");

    sprite.setTexture(texture);

    if (0 == direction)
    {
        sprite.setTextureRect(sf::IntRect(CELL_SIZE * current_frame, CELL_SIZE * diving_state, CELL_SIZE, CELL_SIZE));
    }
    else
    {
        sprite.setTextureRect(sf::IntRect(CELL_SIZE * (1 + current_frame), CELL_SIZE * diving_state, -CELL_SIZE, CELL_SIZE));
    }

    for (unsigned char a = 0; a < size; a++)
    {
        sprite.setPosition(static_cast<float>(x + CELL_SIZE * a), y);

        i_window.draw(sprite);
    }
}

void GloboAerostatico::update(bool i_move_pajaro, Pajaro& i_pajaro)
{
    if (0 == animation_timer)
    {
        current_frame = (1 + current_frame) % 2;

        animation_timer = GLOBO_ANIMATION_SPEED;
    }
    else
    {
        animation_timer--;
    }

    if (0 == direction)
    {
        x += speed;

        // Movemos el pájaro si está aterrizado y el globo no está en estado de "inmersión"
        if (2 > diving_state && true == i_move_pajaro)
        {
            i_pajaro.move(speed);
        }

        if (x >= CELL_SIZE * MAP_WIDTH)
        {
            x -= static_cast<short>(CELL_SIZE * floor(1.5f * MAP_WIDTH));
        }
    }
    else
    {
        x -= speed;

        if (2 > diving_state && true == i_move_pajaro)
        {
            i_pajaro.move(-speed);
        }

        if (x <= -CELL_SIZE * floor(0.5f * MAP_WIDTH))
        {
            x += static_cast<short>(CELL_SIZE * floor(1.5f * MAP_WIDTH));
        }
    }

    // Usamos animación ping-pong (0 -> 1 -> 2 -> 3 -> 2 -> 1 -> 0 -> 1 -> ...) para la navegación del globo
    if (true == diving)
    {
        if (0 == diving_timer)
        {
            if (false == diving_down)
            {
                if (0 == diving_state)
                {
                    diving_down = true;
                    diving_state = 1;
                }
                else
                {
                    diving_state--;
                }
            }
            else
            {
                if (3 == diving_state)
                {
                    diving_down = false;
                    diving_state = 2;
                }
                else
                {
                    diving_state++;
                }
            }

            diving_timer = GLOBO_NAVIGATION_SPEED;
        }
        else
        {
            diving_timer--;
        }
    }
}

IntRect GloboAerostatico::get_rect() const
{
    return sf::IntRect(static_cast<short>(x + floor(0.25f * CELL_SIZE)), y, static_cast<short>(CELL_SIZE * size - floor(0.5f * CELL_SIZE)), CELL_SIZE);
}