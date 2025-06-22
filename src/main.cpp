#include <iostream>
#include <SFML/Graphics.hpp>
#include "boton.hpp"
#include <memory>



using namespace std;
using namespace sf;

int main(){

    //Ventana
    RenderWindow window(VideoMode(850, 750), "itsnotFrogger");
    window.setFramerateLimit(60);

    //fondo
    Texture fondoTexture;
    Sprite fondo;
    if(!fondoTexture.loadFromFile("assets/images/fondo.png"))cout<<"Error al cargar la Textura de fondo"<<endl;
    
    // Fondo actual CON TEXTURA ASIGNADA
    unique_ptr<Sprite> fondoActual = make_unique<Sprite>();
    fondoActual->setTexture(texturaFondo1);  // Textura inicial

        // Crear botón Play
    Boton botonPlay("assets/play_normal.png", "assets/play_presionado.png", Vector2f(300, 250));
    
    // Configurar acción del botón (CON CORRECCIÓN PARA ASIGNAR TEXTURA)
    botonPlay.establecerAccion([&]() {
        static bool primerFondo = true;
        if (primerFondo) {
            fondoActual->setTexture(texturaFondo2);  // Cambia a textura 2
        } else {
            fondoActual->setTexture(texturaFondo1);  // Vuelve a textura 1
        }
        primerFondo = !primerFondo;
        
        botonPlay.setVisible(false);
        cout << "Fondo cambiado y botón ocultado" << endl;
    });
    

        // Cargar texturas de fondo
    Texture texturaFondo1;
    Texture texturaFondo2;
    if (!texturaFondo1.loadFromFile("assets/images/fondo1.png") || 
        !texturaFondo2.loadFromFile("assets/images/fondo2.png")) {
        cout << "Error cargando texturas de fondo" << endl;
        return -1;
    }

    // Ajustar el sprite al tamaño de la ventana
    Vector2u windowSize = window.getSize();
    fondo.setScale(
        static_cast<float>(windowSize.x) / fondo.getLocalBounds().width,
        static_cast<float>(windowSize.y) / fondo.getLocalBounds().height
    );

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
        }
        
        window.clear(Color::Black);
        
        window.draw(fondo);
        
        window.display();
    }
    return 0;
}
