#include "../include/Button.hpp"

Button::Button() : is_pressed(false), is_hovered(false), was_clicked(false) {}

void Button::load_textures(const string& normal_path, const string& pressed_path)
{
    if (!normal_texture.loadFromFile(normal_path) ||
        !pressed_texture.loadFromFile(pressed_path))
    {
        throw runtime_error("Failed to load button textures");
    }
    sprite.setTexture(normal_texture);
}

void Button::set_position(float x, float y)
{
    sprite.setPosition(x, y);
}

void Button::update(const Vector2f& mouse_pos, bool mouse_pressed)
{
    is_hovered = sprite.getGlobalBounds().contains(mouse_pos);

    if (is_hovered)
    {
        if (mouse_pressed)
        {
            if (!is_pressed) {
                is_pressed = true;
            }
            sprite.setTexture(pressed_texture);
        }
        else if (is_pressed && !mouse_pressed)
        {
            is_pressed = false;
            was_clicked = true; // Solo se activa cuando se suelta el mouse sobre el botón
            sprite.setTexture(normal_texture);
        }
    }
    else if (is_pressed && !mouse_pressed)
    {
        is_pressed = false;
        sprite.setTexture(normal_texture);
    }
}

void Button::draw(RenderWindow& window)
{
    if (is_hovered && !is_pressed)
        sprite.setColor(Color(220, 220, 220));
    else
        sprite.setColor(Color::White);
    
    window.draw(sprite);
}

bool Button::is_clicked()
{
    if (was_clicked) {
        was_clicked = false;
        return true;
    }
    return false;
}

FloatRect Button::get_bounds() const
{
    return sprite.getGlobalBounds();
}