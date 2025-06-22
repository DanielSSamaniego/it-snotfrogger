#include <SFML/Graphics.hpp>
#include <functional>
#include <memory>

using namespace std;
using namespace sf;

class Boton
{
public:
    Boton(const string &texturaNormal, const string &texturaPresionado, const Vector2f &posicion);

    void establecerAccion(function<void()> accion);
    void manejarEvento(const Event &evento, const RenderWindow &ventana);
    void dibujar(RenderWindow &ventana) const;
    void establecerPosicion(const Vector2f &posicion);
    FloatRect obtenerLimites() const;
    void setVisible(bool visible);
    bool isVisible() const;

private:
    Texture m_texturaNormal;
    Texture m_texturaPresionado;
    Sprite m_sprite;
    function<void()> m_accionClick;
    bool m_estaPresionado = false;
    bool m_visible = true;

    bool mouseEstaEncima(const RenderWindow &ventana) const;
};
