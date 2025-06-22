#include <array>
#include <chrono>
#include <SFML/Graphics.hpp>

#include "Avion.hpp"
#include "Pajaro.hpp"
#include "TorreControl.hpp"
#include "Global.hpp"

TorreControl::TorreControl(unsigned char i_level)
{
    generate_level(i_level);
}

void TorreControl::draw(sf::RenderWindow& i_window)
{
    for (Avion& avion : aviones)
    {
        avion.draw(i_window);
    }
}

void TorreControl::generate_level(unsigned char i_level)
{
    aviones.clear();
    switch (i_level)
    {
        case 0:
        {
            aviones.push_back(Avion(1, 0));
            aviones.push_back(Avion(9, 0));

            aviones.push_back(Avion(7, 1));
            aviones.push_back(Avion(11, 1));

            aviones.push_back(Avion(8, 3));
            aviones.push_back(Avion(10, 2));

            aviones.push_back(Avion(2, 3));

            aviones.push_back(Avion(0, 4));
            aviones.push_back(Avion(6, 4));
            aviones.push_back(Avion(13, 4));

            aviones.push_back(Avion(0, 5));
            aviones.push_back(Avion(7, 5));
            aviones.push_back(Avion(14, 5));

            break;
        }
        case 1:
        {
            aviones.push_back(Avion(1, 0)); 
            aviones.push_back(Avion(7, 0));
            aviones.push_back(Avion(13, 0));

            aviones.push_back(Avion(4, 1));
            aviones.push_back(Avion(10, 1));
            aviones.push_back(Avion(14, 1));

            aviones.push_back(Avion(9, 2));
            aviones.push_back(Avion(14, 2));

            aviones.push_back(Avion(5, 3));
            aviones.push_back(Avion(7, 3));

            aviones.push_back(Avion(2, 4));
            aviones.push_back(Avion(10, 4));
            aviones.push_back(Avion(15, 4));
            aviones.push_back(Avion(21, 4));

            aviones.push_back(Avion(0, 5));
            aviones.push_back(Avion(4, 5));
            aviones.push_back(Avion(11, 5));
            aviones.push_back(Avion(18, 5));

            break;
        }
        case 2:
        {
            aviones.push_back(Avion(1, 0));
            aviones.push_back(Avion(5, 0));
            aviones.push_back(Avion(12, 0));
            aviones.push_back(Avion(19, 0));

            aviones.push_back(Avion(4, 1));
            aviones.push_back(Avion(9, 1));
            aviones.push_back(Avion(18, 1));

            aviones.push_back(Avion(2, 2));
            aviones.push_back(Avion(10, 2));
            aviones.push_back(Avion(18, 2));

            aviones.push_back(Avion(4, 3));

            aviones.push_back(Avion(0, 4));
            aviones.push_back(Avion(9, 4));
            aviones.push_back(Avion(13, 4));
            aviones.push_back(Avion(19, 4));

            aviones.push_back(Avion(2, 5));
            aviones.push_back(Avion(6, 5));
            aviones.push_back(Avion(15, 5));
            aviones.push_back(Avion(22, 5));

            break;
        }
        case 3:
        {
            aviones.push_back(Avion(3, 0));
            aviones.push_back(Avion(10, 0));
            aviones.push_back(Avion(16, 0));
            aviones.push_back(Avion(21, 0));

            aviones.push_back(Avion(2, 1));
            aviones.push_back(Avion(7, 1));
            aviones.push_back(Avion(15, 1));

            aviones.push_back(Avion(1, 2));
            aviones.push_back(Avion(5, 2));

            aviones.push_back(Avion(4, 3));
            aviones.push_back(Avion(13, 3));
            aviones.push_back(Avion(10, 3));

            aviones.push_back(Avion(3, 4));
            aviones.push_back(Avion(6, 4));
            aviones.push_back(Avion(13, 4));
            aviones.push_back(Avion(20, 4));

            aviones.push_back(Avion(1, 5));
            aviones.push_back(Avion(4, 5));
            aviones.push_back(Avion(10, 5));
            aviones.push_back(Avion(16, 5));

            break;
        }
        case 4:
        {
            aviones.push_back(Avion(0, 0));
            aviones.push_back(Avion(6, 0));
            aviones.push_back(Avion(11, 0));
            aviones.push_back(Avion(21, 0));

            aviones.push_back(Avion(2, 1));
            aviones.push_back(Avion(7, 1));
            aviones.push_back(Avion(16, 1));
            aviones.push_back(Avion(20, 1));

            aviones.push_back(Avion(1, 2));
            aviones.push_back(Avion(9, 2));
            aviones.push_back(Avion(15, 2));

            aviones.push_back(Avion(7, 3));
            aviones.push_back(Avion(13, 3));

            aviones.push_back(Avion(1, 4));
            aviones.push_back(Avion(8, 4));
            aviones.push_back(Avion(12, 4));
            aviones.push_back(Avion(18, 4));

            aviones.push_back(Avion(1, 5));
            aviones.push_back(Avion(8, 5));
            aviones.push_back(Avion(16, 5));
            aviones.push_back(Avion(21, 5));

            break;
        }
        case 5:
        {
            aviones.push_back(Avion(0, 0));   //(NORMAL_SPEED)
            aviones.push_back(Avion(4, 0));
            aviones.push_back(Avion(10, 0));
            aviones.push_back(Avion(15, 0));

            aviones.push_back(Avion(1, 1));   //(NORMAL_SPEED)
            aviones.push_back(Avion(6, 1));
            aviones.push_back(Avion(14, 1));
            aviones.push_back(Avion(18, 1));

            aviones.push_back(Avion(0, 2));   //(FAST_SPEED)
            aviones.push_back(Avion(6, 2));

            aviones.push_back(Avion(7, 3));   //(FAST_SPEED)
            aviones.push_back(Avion(12, 3));
            aviones.push_back(Avion(15, 3));

            aviones.push_back(Avion(0, 4));   //(SLOW_SPEED)
            aviones.push_back(Avion(9, 4));
            aviones.push_back(Avion(13, 4));
            aviones.push_back(Avion(20, 4));

            aviones.push_back(Avion(0, 5));   //(SLOW_SPEED)
            aviones.push_back(Avion(7, 5));
            aviones.push_back(Avion(15, 5));
            aviones.push_back(Avion(20, 5));

            break;
        }

        case 6:
        {
            aviones.push_back(Avion(0, 0));   //(NORMAL_SPEED)
            aviones.push_back(Avion(3, 0));
            aviones.push_back(Avion(8, 0));
            aviones.push_back(Avion(14, 0));

            aviones.push_back(Avion(0, 1));   //(NORMAL_SPEED)
            aviones.push_back(Avion(7, 1));
            aviones.push_back(Avion(15, 1));
            aviones.push_back(Avion(20, 1));

            aviones.push_back(Avion(1, 2));   //(FAST_SPEED)
            aviones.push_back(Avion(8, 2));

            aviones.push_back(Avion(0, 3));   //(FAST_SPEED)
            aviones.push_back(Avion(10, 3));
            aviones.push_back(Avion(19, 3));

            aviones.push_back(Avion(0, 4));
            aviones.push_back(Avion(7, 4));
            aviones.push_back(Avion(12, 4));
            aviones.push_back(Avion(19, 4));
            aviones.push_back(Avion(21, 4));

            aviones.push_back(Avion(0, 5));
            aviones.push_back(Avion(5, 5));
            aviones.push_back(Avion(16, 5));
            aviones.push_back(Avion(21, 5));

            break;
        }
        case 7:
        {
            aviones.push_back(Avion(1, 0));   //(NORMAL_SPEED)
            aviones.push_back(Avion(5, 0));
            aviones.push_back(Avion(8, 0));
            aviones.push_back(Avion(14, 0));
            aviones.push_back(Avion(18, 0));

            aviones.push_back(Avion(0, 1));   //(NORMAL_SPEED)
            aviones.push_back(Avion(7, 1));
            aviones.push_back(Avion(15, 1));
            aviones.push_back(Avion(20, 1));

            aviones.push_back(Avion(1, 2));   //(FAST_SPEED)
            aviones.push_back(Avion(8, 2));
            aviones.push_back(Avion(15, 2));

            aviones.push_back(Avion(0, 3));   //(FAST_SPEED)
            aviones.push_back(Avion(10, 3));
            aviones.push_back(Avion(19, 3));

            aviones.push_back(Avion(1, 4));   //(SLOW_SPEED)
            aviones.push_back(Avion(7, 4));
            aviones.push_back(Avion(11, 4));
            aviones.push_back(Avion(18, 4));
            aviones.push_back(Avion(22, 4));

            aviones.push_back(Avion(0, 5));   //(SLOW_SPEED)
            aviones.push_back(Avion(4, 5));
            aviones.push_back(Avion(9, 5));
            aviones.push_back(Avion(16, 5));
            aviones.push_back(Avion(20, 5));
            
            break;
        }
    }
}

void TorreControl::update(Pajaro& i_pajaro)  
{
    // Actualizar posición de todos los aviones
    for (Avion& avion : aviones)
    {
        avion.update();
    }

    // Verificar colisiones si el pájaro está vivo
    if (0 == i_pajaro.get_dead())
    {
        for (Avion& avion : aviones)
        {
            if (1 == avion.get_rect().intersects(i_pajaro.get_rect()))
            {
                i_pajaro.set_dead();
                break;
            }
        }
    }
}