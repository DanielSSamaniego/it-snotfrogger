#include "boton.hpp"
#include <iostream>

Boton::Boton(const string& texturaNormal, const string& texturaPresionado, const Vector2f& posicion) {
    if (!m_texturaNormal.loadFromFile(texturaNormal)) {
        cerr << "Error cargando textura normal del botón: " << texturaNormal << endl;
    }
    if (!m_texturaPresionado.loadFromFile(texturaPresionado)) {
        cerr << "Error cargando textura presionado del botón: " << texturaPresionado << endl;
    }
    m_sprite.setTexture(m_texturaNormal);
    m_sprite.setPosition(posicion);
}

void Boton::establecerAccion(function<void()> accion) {
    m_accionClick = accion;
}

void Boton::manejarEvento(const Event& evento, const RenderWindow& ventana) {
    if (!m_visible) return;

    Vector2f posicionMouse = ventana.mapPixelToCoords(Mouse::getPosition(ventana));
    bool mouseEncima = mouseEstaEncima(ventana);

    if (evento.type == Event::MouseButtonPressed && 
        evento.mouseButton.button == Mouse::Left &&
        mouseEncima) {
        m_estaPresionado = true;
        m_sprite.setTexture(m_texturaPresionado);
    }
    else if (evento.type == Event::MouseButtonReleased) {
        if (m_estaPresionado && mouseEncima && m_accionClick) {
            m_accionClick();
        }
        m_estaPresionado = false;
        m_sprite.setTexture(m_texturaNormal);
    }
}

void Boton::dibujar(RenderWindow& ventana) const {
    if (m_visible) {
        ventana.draw(m_sprite);
    }
}

void Boton::establecerPosicion(const Vector2f& posicion) {
    m_sprite.setPosition(posicion);
}

FloatRect Boton::obtenerLimites() const {
    return m_sprite.getGlobalBounds();
}

bool Boton::mouseEstaEncima(const RenderWindow& ventana) const {
    Vector2f posicionMouse = ventana.mapPixelToCoords(Mouse::getPosition(ventana));
    return m_sprite.getGlobalBounds().contains(posicionMouse);
}

void Boton::setVisible(bool visible) {
    m_visible = visible;
}

bool Boton::isVisible() const {
    return m_visible;
}