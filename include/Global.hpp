#pragma once
#include <SFML/Graphics.hpp>
#include <chrono>
#include <array>

using namespace std;
using namespace sf;

// Constantes del juego
constexpr unsigned char CELL_SIZE = 16;
constexpr unsigned char AGUILA_ANIMATION_SPEED = 32;
constexpr unsigned char FAST_SPEED = 3;
constexpr unsigned char FONT_HEIGHT = 16;
constexpr unsigned char PAJARO_ANIMATION_SPEED = 8;
constexpr unsigned char MAP_WIDTH = 16;
constexpr unsigned char MAP_HEIGHT = 15;
constexpr unsigned char NORMAL_SPEED = 2;
constexpr unsigned char SCREEN_RESIZE = 2;
constexpr unsigned char SLOW_SPEED = 1;
constexpr unsigned char TOTAL_LEVELS = 8;
constexpr unsigned char GLOBO_ANIMATION_SPEED = 16;
// Estados de navegación del globo (4 estados, cada uno dura 32 frames)
constexpr unsigned char GLOBO_NAVIGATION_SPEED = 32;

// Duración en frames
constexpr unsigned short TIMER_INITIAL_DURATION = 4096;
// Reducción del timer al completar nivel
constexpr unsigned short TIMER_REDUCTION = 512;

constexpr chrono::microseconds FRAME_DURATION(16667);