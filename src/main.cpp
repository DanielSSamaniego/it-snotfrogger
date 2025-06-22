#include <array>
#include <chrono>
#include <cmath>
#include <SFML/Graphics.hpp>

#include "Avion.hpp"
#include "Pajaro.hpp"
#include "TorreControl.hpp"
#include "DrawMap.hpp"
#include "DrawText.hpp"
#include "Global.hpp"
#include "Nube.hpp"
#include "GloboAerostatico.hpp"
#include "ClimaControl.hpp"

int main()
{
    // ¿Estamos mostrando la transición al siguiente nivel?
    bool next_level = 0;

    unsigned char level = 0;

    unsigned short timer = TIMER_INITIAL_DURATION;
    unsigned short timer_duration = TIMER_INITIAL_DURATION;

    std::array<bool, 5> altitude_zones = {0}; // Cambiado de swamp a altitude_zones

    std::chrono::microseconds lag(0);

    std::chrono::steady_clock::time_point previous_time;

    sf::Event event;

    sf::RenderWindow window(sf::VideoMode(CELL_SIZE * MAP_WIDTH * SCREEN_RESIZE, SCREEN_RESIZE * (FONT_HEIGHT + CELL_SIZE * MAP_HEIGHT)), "SkyCrosser", sf::Style::Close); // Cambiado el título a "SkyCrosser"
    window.setView(sf::View(sf::FloatRect(0, 0, CELL_SIZE * MAP_WIDTH, FONT_HEIGHT + CELL_SIZE * MAP_HEIGHT)));

    TorreControl torre_control(level); // Cambiado CarsManager por TorreControl

    Pajaro pajaro; // Cambiado Frog por Pajaro

    ClimaControl clima_control(level); // Cambiado RiverManager por ClimaControl

    previous_time = std::chrono::steady_clock::now();

    while (1 == window.isOpen())
    {
        std::chrono::microseconds delta_time = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - previous_time);

        lag += delta_time;

        previous_time += delta_time;

        while (FRAME_DURATION <= lag)
        {
            lag -= FRAME_DURATION;

            while (1 == window.pollEvent(event))
            {
                switch (event.type)
                {
                case sf::Event::Closed:
                {
                    window.close();
                }
                }
            }

            if (1 == next_level)
            {
                if (1 == sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
                {
                    next_level = 0;
                }
            }
            else
            {
                if (0 == pajaro.get_dead()) // Cambiado frog por pajaro
                {
                    if (0 == timer)
                    {
                        pajaro.set_dead();
                    }
                    else
                    {
                        timer--;
                    }
                }

                pajaro.update();

                torre_control.update(pajaro); // Cambiado cars_manager por torre_control

                clima_control.update(pajaro); // Cambiado river_manager por clima_control
            }

            if (1 == pajaro.get_dead())
            {
                if (1 == sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
                {
                    level = 0;

                    timer = TIMER_INITIAL_DURATION;
                    timer_duration = TIMER_INITIAL_DURATION;

                    altitude_zones.fill(0); // Cambiado swamp por altitude_zones

                    torre_control.generate_level(level);
                    clima_control.generate_level(level);

                    pajaro.reset();
                }
            }
            else if (1 == pajaro.update_altitude(altitude_zones)) // Cambiado update_swamp por update_altitude
            {
                bool all_zones_reached = 1; // Mejor nombre para la variable

                for (unsigned char a = 0; a < altitude_zones.size(); a++)
                {
                    if (0 == altitude_zones[a])
                    {
                        all_zones_reached = 0;
                        break;
                    }
                }

                if (1 == all_zones_reached)
                {
                    next_level = 1;
                    level++;

                    timer_duration = std::max<unsigned short>(floor(0.25f * TIMER_INITIAL_DURATION), timer_duration - TIMER_REDUCTION);
                    timer = timer_duration;

                    if (TOTAL_LEVELS == level)
                    {
                        level = static_cast<unsigned char>(floor(0.5f * TOTAL_LEVELS));
                    }

                    altitude_zones.fill(0);

                    torre_control.generate_level(level);
                    clima_control.generate_level(level);
                }
                else
                {
                    timer = std::min<unsigned short>(timer_duration, timer + floor(0.5f * timer_duration));
                }

                pajaro.reset();
            }

            if (FRAME_DURATION > lag)
            {
                window.clear();

                if (1 == next_level)
                {
                    draw_text(1, 0, 0, "NEXT LEVEL!", window);
                }
                else
                {
                    draw_map(altitude_zones, window); // Cambiado swamp por altitude_zones

                    if (0 == pajaro.get_dead())
                    {
                        clima_control.draw(window);
                        pajaro.draw(window);
                    }
                    else
                    {
                        pajaro.draw(window);
                        clima_control.draw(window);
                    }

                    torre_control.draw(window);

                    draw_text(0, 0, CELL_SIZE * MAP_HEIGHT, "Time: " + std::to_string(static_cast<unsigned short>(floor(timer / 64.f))), window);
                }

                window.display();
            }
        }
    }
}