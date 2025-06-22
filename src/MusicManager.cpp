#include "MusicManager.hpp"

MusicManager::MusicManager() : music_enabled(true)
{
    load_music();
}

void MusicManager::load_music()
{
    if (!menu_music.openFromFile("assets/music/menu_theme.ogg") ||
        !game_music.openFromFile("assets/music/game_theme.ogg"))
    {
        throw runtime_error("Failed to load music files");
    }
    
    menu_music.setLoop(true);
    game_music.setLoop(true);
}

void MusicManager::play_menu_music()
{
    if (music_enabled)
    {
        game_music.stop();
        menu_music.play();
    }
}

void MusicManager::play_game_music()
{
    if (music_enabled)
    {
        menu_music.stop();
        game_music.play();
    }
}

void MusicManager::stop_music()
{
    menu_music.stop();
    game_music.stop();
}

void MusicManager::toggle_music(bool enabled)
{
    music_enabled = enabled;
    if (!music_enabled) stop_music();
}