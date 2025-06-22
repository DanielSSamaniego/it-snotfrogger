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
    bool was_clicked; // Nuevo atributo para detectar clic real

public:
    Button();
    
    void load_textures(const string& normal_path, const string& pressed_path);
    void set_position(float x, float y);
    void update(const Vector2f& mouse_pos, bool mouse_pressed);
    void draw(RenderWindow& window);
    bool is_clicked(); // Quitar const porque modifica was_clicked
    FloatRect get_bounds() const;
    void set_scale(float x, float y) { sprite.setScale(x, y); } // Nuevo método para escalar el sprite
};