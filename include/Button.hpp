#pragma once
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Button
{
    Texture normal_texture;
    Texture pressed_texture;
    Sprite sprite;
    bool is_pressed;
    bool is_hovered;

public:
    Button();
    
    void load_textures(const string& normal_path, const string& pressed_path);
    void set_position(float x, float y);
    void update(const Vector2f& mouse_pos, bool mouse_pressed);
    void draw(RenderWindow& window);
    bool is_clicked() const;
    FloatRect get_bounds() const;
};