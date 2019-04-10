

#include <SFML/Graphics.hpp>
#include <iostream>
#include "menu.h"
//#include <SFML/Audio.hpp>

class juego
{
public:
    juego();
    void update();
    void render();
    void cargador();
    void procesar_eventos();
    void eventos_raton();
   // void playMusica();
private:
    sf::RenderWindow *window;
    sf::Event *evento;
    sf::Mouse *raton;
    //sf::Music *musica;
    //sf::Sound sonido;
    bool menuprincipal = true;
    menu *menu_inicial;
};

