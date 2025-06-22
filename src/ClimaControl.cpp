#include <array>
#include <chrono>
#include <cmath>
#include <SFML/Graphics.hpp>

#include "Pajaro.hpp"
#include "Global.hpp"
#include "Nube.hpp"
#include "GloboAerostatico.hpp"
#include "ClimaControl.hpp"

ClimaControl::ClimaControl(unsigned char i_level)
{
    generate_level(i_level);
}

void ClimaControl::draw(sf::RenderWindow &i_window)
{
    for (Nube &nube : nubes)
    {
        nube.draw(i_window);
    }

    for (GloboAerostatico &globo : globos)
    {
        globo.draw(i_window);
    }
}

void ClimaControl::generate_level(unsigned char i_level)
{
    nubes.clear();
    globos.clear();

    // Configuración de niveles con nubes y globos aerostáticos
    switch (i_level)
    {
    case 0:
    {
        nubes.push_back(Nube(1, 1, 0));
        nubes.push_back(Nube(3, 9, 0));
        nubes.push_back(Nube(1, 20, 0));

        globos.push_back(GloboAerostatico(0, 3, 0, 1));
        globos.push_back(GloboAerostatico(0, 3, 4, 1));
        globos.push_back(GloboAerostatico(1, 3, 9, 1));
        globos.push_back(GloboAerostatico(0, 3, 15, 1));

        nubes.push_back(Nube(2, 2, 2));
        nubes.push_back(Nube(2, 16, 2));

        nubes.push_back(Nube(1, 3, 3));
        nubes.push_back(Nube(1, 8, 3));
        nubes.push_back(Nube(1, 13, 3));

        globos.push_back(GloboAerostatico(0, 4, 0, 4));
        globos.push_back(GloboAerostatico(0, 4, 6, 4));
        globos.push_back(GloboAerostatico(1, 4, 12, 4));

        break;
    }
    case 1:
    {
        nubes.push_back(Nube(1, 0, 0));
        nubes.push_back(Nube(1, 5, 0));
        nubes.push_back(Nube(1, 10, 0));

        globos.push_back(GloboAerostatico(0, 3, 0, 1));
        globos.push_back(GloboAerostatico(1, 3, 5, 1));
        globos.push_back(GloboAerostatico(0, 3, 10, 1));
        globos.push_back(GloboAerostatico(0, 3, 15, 1));

        nubes.push_back(Nube(2, 0, 2));
        nubes.push_back(Nube(2, 8, 2));
        nubes.push_back(Nube(2, 16, 2));

        nubes.push_back(Nube(0, 0, 3));
        nubes.push_back(Nube(0, 4, 3));
        nubes.push_back(Nube(0, 8, 3));

        globos.push_back(GloboAerostatico(0, 4, 0, 4));
        globos.push_back(GloboAerostatico(0, 4, 5, 4));
        globos.push_back(GloboAerostatico(1, 4, 10, 4));
        globos.push_back(GloboAerostatico(0, 4, 15, 4));

        break;
    }
    case 2:
    {
        nubes.push_back(Nube(1, 3, 0));
        nubes.push_back(Nube(1, 8, 0));
        nubes.push_back(Nube(1, 15, 0));
        nubes.push_back(Nube(3, 20, 0));

        globos.push_back(GloboAerostatico(1, 3, 0, 1));
        globos.push_back(GloboAerostatico(0, 3, 5, 1));
        globos.push_back(GloboAerostatico(0, 3, 10, 1));
        globos.push_back(GloboAerostatico(0, 3, 19, 1));

        nubes.push_back(Nube(2, 0, 2));
        nubes.push_back(Nube(2, 13, 2));

        nubes.push_back(Nube(1, 1, 3));
        nubes.push_back(Nube(0, 8, 3));
        nubes.push_back(Nube(0, 16, 3));

        globos.push_back(GloboAerostatico(1, 4, 0, 4));
        globos.push_back(GloboAerostatico(0, 4, 7, 4));
        globos.push_back(GloboAerostatico(0, 4, 16, 4));

        break;
    }
    case 3:
    {
        nubes.push_back(Nube(3, 3, 0));
        nubes.push_back(Nube(2, 15, 0));

        globos.push_back(GloboAerostatico(1, 3, 2, 1));
        globos.push_back(GloboAerostatico(0, 2, 7, 1));
        globos.push_back(GloboAerostatico(0, 4, 14, 1));

        nubes.push_back(Nube(0, 1, 2));
        nubes.push_back(Nube(2, 5, 2));
        nubes.push_back(Nube(1, 13, 2));

        nubes.push_back(Nube(0, 2, 3));
        nubes.push_back(Nube(2, 6, 3));
        nubes.push_back(Nube(0, 15, 3));

        globos.push_back(GloboAerostatico(1, 4, 3, 4));
        globos.push_back(GloboAerostatico(0, 4, 10, 4));

        break;
    }

    case 4:
    {
        nubes.push_back(Nube(1, 1, 0));
        nubes.push_back(Nube(1, 8, 0));
        nubes.push_back(Nube(3, 17, 0));

        globos.push_back(GloboAerostatico(0, 2, 0, 1));
        globos.push_back(GloboAerostatico(0, 3, 5, 1));
        globos.push_back(GloboAerostatico(1, 2, 11, 1));
        globos.push_back(GloboAerostatico(0, 3, 16, 1));

        nubes.push_back(Nube(2, 2, 2));
        nubes.push_back(Nube(2, 18, 2));

        nubes.push_back(Nube(0, 0, 3));
        nubes.push_back(Nube(0, 7, 3));
        nubes.push_back(Nube(0, 18, 3));

        globos.push_back(GloboAerostatico(1, 3, 0, 4));
        globos.push_back(GloboAerostatico(0, 3, 6, 4));
        globos.push_back(GloboAerostatico(0, 4, 18, 4));

        break;
    }
    case 5:
    {
        nubes.push_back(Nube(1, 0, 0));
        nubes.push_back(Nube(1, 7, 0));
        nubes.push_back(Nube(3, 15, 0));

        globos.push_back(GloboAerostatico(0, 2, 1, 1));
        globos.push_back(GloboAerostatico(0, 3, 6, 1));
        globos.push_back(GloboAerostatico(1, 2, 12, 1));
        globos.push_back(GloboAerostatico(0, 3, 17, 1));

        nubes.push_back(Nube(1, 0, 2));
        nubes.push_back(Nube(2, 7, 2));
        nubes.push_back(Nube(2, 16, 2));

        nubes.push_back(Nube(0, 1, 3));
        nubes.push_back(Nube(0, 8, 3));
        nubes.push_back(Nube(0, 17, 3));

        globos.push_back(GloboAerostatico(0, 2, 0, 4));
        globos.push_back(GloboAerostatico(0, 3, 6, 4));
        globos.push_back(GloboAerostatico(1, 4, 18, 4));

        break;
    }
    case 6:
    {
        nubes.push_back(Nube(1, 0, 0));
        nubes.push_back(Nube(3, 16, 0));

        globos.push_back(GloboAerostatico(1, 4, 0, 1));
        globos.push_back(GloboAerostatico(0, 3, 7, 1));
        globos.push_back(GloboAerostatico(1, 2, 12, 1));
        globos.push_back(GloboAerostatico(0, 2, 18, 1));

        nubes.push_back(Nube(1, 1, 2));
        nubes.push_back(Nube(1, 8, 2));
        nubes.push_back(Nube(2, 15, 2));

        nubes.push_back(Nube(0, 1, 3));
        nubes.push_back(Nube(0, 8, 3));
        nubes.push_back(Nube(0, 17, 3));

        globos.push_back(GloboAerostatico(0, 2, 0, 4));
        globos.push_back(GloboAerostatico(1, 3, 6, 4));
        globos.push_back(GloboAerostatico(0, 3, 18, 4));

        break;
    }
    case 7:
    {
        nubes.push_back(Nube(3, 3, 0));
        nubes.push_back(Nube(3, 13, 0));

        globos.push_back(GloboAerostatico(1, 3, 0, 1));
        globos.push_back(GloboAerostatico(0, 2, 8, 1));
        globos.push_back(GloboAerostatico(1, 2, 13, 1));

        nubes.push_back(Nube(0, 0, 2));
        nubes.push_back(Nube(1, 6, 2));
        nubes.push_back(Nube(1, 14, 2));

        nubes.push_back(Nube(0, 1, 3));
        nubes.push_back(Nube(0, 10, 3));

        globos.push_back(GloboAerostatico(1, 2, 1, 4));
        globos.push_back(GloboAerostatico(1, 3, 8, 4));
        globos.push_back(GloboAerostatico(0, 2, 19, 4));
    }
    }
}

void ClimaControl::update(Pajaro &i_pajaro)
{
    bool pajaro_en_nube = false;

    for (Nube &nube : nubes)
    {
        if (!pajaro_en_nube && !i_pajaro.get_dead())
        {
            pajaro_en_nube = nube.check_pajaro(i_pajaro);
            nube.update(pajaro_en_nube, i_pajaro);
        }
        else
        {
            nube.update(false, i_pajaro);
        }
    }

    for (GloboAerostatico &globo : globos)
    {
        if (!pajaro_en_nube && !i_pajaro.get_dead())
        {
            pajaro_en_nube = globo.check_pajaro(i_pajaro);
            globo.update(pajaro_en_nube, i_pajaro);
        }
        else
        {
            globo.update(false, i_pajaro);
        }
    }

    if (!pajaro_en_nube && CELL_SIZE < i_pajaro.get_y() && i_pajaro.get_y() < CELL_SIZE * floor(0.5f * MAP_HEIGHT))
    {
        i_pajaro.set_dead();
    }
}