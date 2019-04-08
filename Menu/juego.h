

#include <SFML/Graphics.hpp>
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
    menu *menu_inicial;
};

