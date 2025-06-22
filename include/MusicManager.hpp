#pragma once
#include <SFML/Audio.hpp>

using namespace std;
using namespace sf;

class MusicManager
{
    Music menu_music;
    Music game_music;
    bool music_enabled;

public:
    MusicManager();
    
    void load_music();
    void play_menu_music();
    void play_game_music();
    void stop_music();
    void toggle_music(bool enabled);
};