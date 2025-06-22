#include <iostream>
#include <SFML/Graphics.hpp>

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
    fondo.setTexture(fondoTexture);

    Sprite sprite1(texture,intrect())
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
