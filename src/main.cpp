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
#include "MusicManager.hpp"
#include "Button.hpp"

using namespace std;
using namespace sf;

enum class GameState {
    MAIN_MENU,
    PLAYING,
    NEXT_LEVEL,
    GAME_OVER
};

int main()
{
    GameState game_state = GameState::MAIN_MENU;
    unsigned char level = 0;
    unsigned short timer = TIMER_INITIAL_DURATION;
    unsigned short timer_duration = TIMER_INITIAL_DURATION;
    array<bool, 5> altitude_zones = {0};
    chrono::microseconds lag(0);

    RenderWindow window(VideoMode(CELL_SIZE * MAP_WIDTH * SCREEN_RESIZE, 
                       SCREEN_RESIZE * (FONT_HEIGHT + CELL_SIZE * MAP_HEIGHT)), 
                       "SkyCrosser", Style::Close);
    window.setView(View(FloatRect(0, 0, CELL_SIZE * MAP_WIDTH, FONT_HEIGHT + CELL_SIZE * MAP_HEIGHT)));

    // Cargar recursos
    Texture menu_texture;
    if (!menu_texture.loadFromFile("assets/images/menu_background.png")) {
        return EXIT_FAILURE;
    }
    Sprite menu_sprite(menu_texture);
    menu_sprite.setScale(
        (CELL_SIZE * MAP_WIDTH) / menu_sprite.getLocalBounds().width,
        (FONT_HEIGHT + CELL_SIZE * MAP_HEIGHT) / menu_sprite.getLocalBounds().height
    );

    // Botones
    Button play_button;
    play_button.load_textures("assets/images/play_button.png", "assets/images/play_button_pressed.png");
    play_button.set_position(CELL_SIZE * MAP_WIDTH / 2 - 100, CELL_SIZE * MAP_HEIGHT / 2);

    Button exit_button;
    exit_button.load_textures("assets/images/exit_button.png", "assets/images/exit_button_pressed.png");
    exit_button.set_position(CELL_SIZE * MAP_WIDTH / 2 - 100, CELL_SIZE * MAP_HEIGHT / 2 + 120);

    // Música
    MusicManager music_manager;
    music_manager.play_menu_music();

    // Objetos del juego
    TorreControl torre_control(level);
    Pajaro pajaro;
    ClimaControl clima_control(level);

    chrono::steady_clock::time_point previous_time = chrono::steady_clock::now();
    bool mouse_pressed = false;

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::MouseButtonPressed)
                mouse_pressed = true;
            else if (event.type == Event::MouseButtonReleased)
                mouse_pressed = false;
        }

        Vector2f mouse_pos = window.mapPixelToCoords(Mouse::getPosition(window));

        if (game_state == GameState::MAIN_MENU)
        {
            play_button.update(mouse_pos, mouse_pressed);
            exit_button.update(mouse_pos, mouse_pressed);

            if (play_button.is_clicked())
            {
                game_state = GameState::PLAYING;
                music_manager.play_game_music();
            }
            else if (exit_button.is_clicked())
            {
                window.close();
            }
        }

        chrono::microseconds delta_time = chrono::duration_cast<chrono::microseconds>(
            chrono::steady_clock::now() - previous_time);
        lag += delta_time;
        previous_time += delta_time;

        while (FRAME_DURATION <= lag)
        {
            lag -= FRAME_DURATION;

            if (game_state == GameState::PLAYING)
            {
                if (0 == pajaro.get_dead())
                {
                    if (0 == timer)
                    {
                        pajaro.set_dead();
                        game_state = GameState::GAME_OVER;
                        music_manager.play_menu_music();
                    }
                    else
                    {
                        timer--;
                    }
                }

                pajaro.update();
                torre_control.update(pajaro);
                clima_control.update(pajaro);

                if (1 == pajaro.update_altitude(altitude_zones))
                {
                    bool all_zones_reached = 1;
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
                        game_state = GameState::NEXT_LEVEL;
                        level++;
                        timer_duration = max<unsigned short>(floor(0.25f * TIMER_INITIAL_DURATION), timer_duration - TIMER_REDUCTION);
                        timer = timer_duration;

                        if (TOTAL_LEVELS == level)
                        {
                            level = static_cast<unsigned char>(floor(0.5f * TOTAL_LEVELS));
                        }

                        altitude_zones.fill(0);
                        torre_control.generate_level(level);
                        clima_control.generate_level(level);
                    }
                    pajaro.reset();
                }
            }
            else if (game_state == GameState::GAME_OVER)
            {
                if (Keyboard::isKeyPressed(Keyboard::Enter))
                {
                    level = 0;
                    timer = TIMER_INITIAL_DURATION;
                    timer_duration = TIMER_INITIAL_DURATION;
                    altitude_zones.fill(0);
                    torre_control.generate_level(level);
                    clima_control.generate_level(level);
                    pajaro.reset();
                    game_state = GameState::PLAYING;
                    music_manager.play_game_music();
                }
            }
            else if (game_state == GameState::NEXT_LEVEL)
            {
                if (Keyboard::isKeyPressed(Keyboard::Enter))
                {
                    game_state = GameState::PLAYING;
                }
            }
        }

        window.clear();

        if (game_state == GameState::MAIN_MENU)
        {
            window.draw(menu_sprite);
            play_button.draw(window);
            exit_button.draw(window);
            
            draw_text(1, CELL_SIZE * MAP_WIDTH / 2, CELL_SIZE * MAP_HEIGHT / 4, 
                     "SKYCROSSER", window);
        }
        else if (game_state == GameState::PLAYING)
        {
            draw_map(altitude_zones, window);
            clima_control.draw(window);
            pajaro.draw(window);
            torre_control.draw(window);
            draw_text(0, 0, CELL_SIZE * MAP_HEIGHT, 
                      "Time: " + to_string(static_cast<unsigned short>(floor(timer / 64.f))), window);
        }
        else if (game_state == GameState::NEXT_LEVEL)
        {
            draw_text(1, 0, 0, "NEXT LEVEL!", window);
        }
        else if (game_state == GameState::GAME_OVER)
        {
            draw_text(1, 0, 0, "GAME OVER - PRESIONA ENTER", window);
        }

        window.display();
    }

    return 0;
}