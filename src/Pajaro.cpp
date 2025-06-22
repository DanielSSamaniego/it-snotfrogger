#include <array>
#include <chrono>
#include <cmath>
#include <SFML/Graphics.hpp>

#include "include/Pajaro.hpp"
#include "include/Global.hpp"

Pajaro::Pajaro()
{
    reset();
}

bool Pajaro::get_dead() const
{
    return dead;
}

bool Pajaro::update_altitude(std::array<bool, 5>& i_altitude_zones)
{
    if (CELL_SIZE >= y)
    {
        if (floor(0.75f * CELL_SIZE) <= x % (3 * CELL_SIZE) && floor(2.25f * CELL_SIZE) >= x % (3 * CELL_SIZE))
        {
            unsigned char altitude_spot = static_cast<unsigned char>(floor(x / static_cast<float>(3 * CELL_SIZE)));

            if (0 == i_altitude_zones[altitude_spot])
            {
                i_altitude_zones[altitude_spot] = 1;

                return 1;
            }
            else
            {
                set_dead();
            }
        }
        else
        {
            set_dead();
        }
    }

    return 0;
}

unsigned short Pajaro::get_y() const
{
    return y;
}

void Pajaro::draw(sf::RenderWindow& i_window)
{
    if (0 == dead)
    {
        texture.loadFromFile("assets/images/Pajaro.png");
    }
    else
    {
        texture.loadFromFile("assets/images/PajaroDeath.png");
    }

    sprite.setPosition(x, y);
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(CELL_SIZE * current_frame, CELL_SIZE * direction, CELL_SIZE, CELL_SIZE));

    i_window.draw(sprite);
}

void Pajaro::move(char i_value)
{
    x = std::clamp(i_value + x, 0, CELL_SIZE * (MAP_WIDTH - 1));
}

void Pajaro::reset()
{
    dead = 0;

    x = static_cast<short>(CELL_SIZE * floor(0.5f * MAP_WIDTH));

    animation_timer = 0;
    current_frame = 1;
    direction = 1;

    y = CELL_SIZE * (MAP_HEIGHT - 1);

    control_keys[0] = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
    control_keys[1] = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
    control_keys[2] = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
    control_keys[3] = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
}

void Pajaro::set_dead()
{
    if (0 == dead)
    {
        dead = 1;

        animation_timer = 0;
        current_frame = 0;
    }
}

void Pajaro::update()
{
    if (0 == dead)
    {
        bool moved = 0;

        if (0 == control_keys[0] && 1 == sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            moved = 1;

            x = std::min(CELL_SIZE + x, CELL_SIZE * (MAP_WIDTH - 1));

            direction = 0;
        }
        else if (0 == control_keys[1] && 1 == sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            moved = 1;

            y = std::max(y - CELL_SIZE, 0);

            direction = 1;
        }
        else if (0 == control_keys[2] && 1 == sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            moved = 1;

            x = std::max(x - CELL_SIZE, 0);

            direction = 2;
        }
        else if (0 == control_keys[3] && 1 == sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            moved = 1;

            y = std::min(CELL_SIZE + y, CELL_SIZE * (MAP_HEIGHT - 1));

            direction = 3;
        }

        control_keys[0] = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
        control_keys[1] = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
        control_keys[2] = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
        control_keys[3] = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);

        if (1 == moved)
        {
            animation_timer = PAJARO_ANIMATION_SPEED;
            current_frame = 0;
        }

        if (0 == animation_timer)
        {
            current_frame = 1;
        }
        else
        {
            animation_timer--;
        }
    }
    else if (y < CELL_SIZE * floor(0.5f * MAP_HEIGHT))
    {
        if (0 == animation_timer)
        {
            animation_timer = PAJARO_ANIMATION_SPEED;
            current_frame = std::min(3, 1 + current_frame);
        }
        else
        {
            animation_timer--;
        }
    }
}

sf::IntRect Pajaro::get_rect() const
{
    return sf::IntRect(x, y, CELL_SIZE, CELL_SIZE);
}