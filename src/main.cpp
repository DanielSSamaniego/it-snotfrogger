#include <SFML/Graphics.hpp>
#include "boton.hpp"
#include <memory>
#include <iostream>

using namespace std;
using namespace sf;

int main() {
    // Ventana
    RenderWindow window(VideoMode(850, 750), "itsnotFrogger");
    window.setFramerateLimit(60);

    // Cargar texturas de fondo
    Texture texturaFondo1;
    Texture texturaFondo2;
    if (!texturaFondo1.loadFromFile("assets/images/fondo1.png") || 
        !texturaFondo2.loadFromFile("assets/images/fondo2.png")) {
        cout << "Error cargando texturas de fondo" << endl;
        return -1;
    }

    // Función para crear fondos ajustados
    auto crearFondoAjustado = [&window](const Texture& textura) {
        unique_ptr<Sprite> fondo = make_unique<Sprite>(textura);
        Vector2u windowSize = window.getSize();
        fondo->setScale(
            static_cast<float>(windowSize.x) / fondo->getLocalBounds().width,
            static_cast<float>(windowSize.y) / fondo->getLocalBounds().height
        );
        return fondo;
    };

    // Fondo actual (inicia con fondo1)
    unique_ptr<Sprite> fondoActual = crearFondoAjustado(texturaFondo1);

    // Crear botón Play (centrado)
    Boton botonPlay(
        "assets/play_normal.png", 
        "assets/play_presionado.png", 
        Vector2f(
            (window.getSize().x - 200) / 2.0f,  // Asume botón de 200px de ancho
            (window.getSize().y - 100) / 2.0f    // Asume botón de 100px de alto
        )
    );
    
    // Configurar acción del botón
    botonPlay.establecerAccion([&]() {
        static bool primerFondo = true;
        fondoActual = primerFondo 
            ? crearFondoAjustado(texturaFondo2) 
            : crearFondoAjustado(texturaFondo1);
        primerFondo = !primerFondo;
        botonPlay.setVisible(false);
        cout << "Fondo cambiado y botón ocultado" << endl;
    });

    // Mensaje de bienvenida
    cout << "Bienvenido a itsnotFrogger!" << endl;
    cout << "Presiona 'Esc' para salir." << endl;

    // Bucle principal del juego
    while(window.isOpen()){
        Event event;
        while(window.pollEvent(event)){
            if(event.type == Event::Closed){
                window.close();
            }
            
            // Manejar tecla ESC
            if(event.type == Event::KeyPressed && event.key.code == Keyboard::Escape){
                window.close();
            }
            
            // Manejar botón Play
            if(botonPlay.isVisible()){
                botonPlay.manejarEvento(event, window);
            }
        }
        
        window.clear(Color::Black);
        window.draw(*fondoActual);  // Dibujar fondo actual
        
        // Dibujar botón si está visible
        if(botonPlay.isVisible()){
            botonPlay.dibujar(window);
        }
        
        window.display();
    }
    
    return 0;
}