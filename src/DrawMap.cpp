#include <array>
#include <chrono>
#include <cmath>
#include <SFML/Graphics.hpp>

#include "include/DrawMap.hpp"
#include "include/Global.hpp"

using namespace std;
using namespace sf;

void dibujar_mapa(const array<bool, 5> &update_swamp, RenderWindow &ventana)
{
    Sprite sprite;

    Texture textura;
    textura.loadFromFile("assets/images/MapaCielo.png"); // Cambiado a ruta assets/images

    sprite.setTexture(textura);

    for (unsigned char a = 0; a < MAP_HEIGHT; a++) // Usando constante en español
    {
        if (a == floor(0.5f * MAP_HEIGHT) || a == MAP_HEIGHT - 1)
        {
            sprite.setTextureRect(IntRect(4 * CELL_SIZE, 0, CELL_SIZE, CELL_SIZE));
        }
        else if (a == 1 + floor(0.5f * MAP_HEIGHT) || a == MAP_HEIGHT - 3)
        {
            sprite.setTextureRect(IntRect(5 * CELL_SIZE, 0, CELL_SIZE, CELL_SIZE));
        }
        else if (a == 2 + floor(0.5f * MAP_HEIGHT) || a == MAP_HEIGHT - 2)
        {
            sprite.setTextureRect(IntRect(6 * CELL_SIZE, 0, CELL_SIZE, CELL_SIZE));
        }
        else if (a == 3 + floor(0.5f * MAP_HEIGHT))
        {
            sprite.setTextureRect(IntRect(7 * CELL_SIZE, 0, CELL_SIZE, CELL_SIZE));
        }
        else if (a == MAP_HEIGHT - 4)
        {
            sprite.setTextureRect(IntRect(8 * CELL_SIZE, 0, CELL_SIZE, CELL_SIZE));
        }
        else
        {
            sprite.setTextureRect(IntRect(3 * CELL_SIZE, 0, CELL_SIZE, CELL_SIZE));
        }
        for (unsigned char b = 0; b < MAP_WIDTH; b++)
        {
            sprite.setPosition(static_cast<float>(CELL_SIZE * b), static_cast<float>(CELL_SIZE * a));

            if (0 == a)
            {
                if (0 == b % 3)
                {
                    sprite.setTextureRect(IntRect(0, 0, CELL_SIZE, CELL_SIZE));
                }
                else
                {
                    sprite.setTextureRect(IntRect(CELL_SIZE, 0, CELL_SIZE, CELL_SIZE));
                }
            }
            else if (1 == a)
            {
                if (0 == b % 3)
                {
                    sprite.setTextureRect(IntRect(2 * CELL_SIZE, 0, CELL_SIZE, CELL_SIZE));
                }
                else
                {
                    sprite.setTextureRect(IntRect(3 * CELL_SIZE, 0, CELL_SIZE, CELL_SIZE));
                }
            }

            ventana.draw(sprite);
        }
        // Dibujamos los pájaros en las zonas de anidación
        sprite.setTextureRect(IntRect(9 * CELL_SIZE, 0, CELL_SIZE, CELL_SIZE));

        for (unsigned char i = 0; i < update_swamp.size(); i++)
        {
            if (1 == update_swamp[i])
            {
                sprite.setPosition(3 * CELL_SIZE * (0.5f + i), CELL_SIZE);

                ventana.draw(sprite);
            }
        }
    }
}