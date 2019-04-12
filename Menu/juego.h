

#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <iostream>
#include "menu.h"

class juego
{
public:
    juego();
    void update();
    void render();
    void cargador();
    void procesar_eventos();
    void eventos_raton();
private:
    sf::RenderWindow *window;
    sf::Event *evento;
    sf::Mouse *raton;
    bool menuprincipal = true;
    bool sel_raton = false;
    bool sel_teclado = true;
    menu *menu_inicial;
};

