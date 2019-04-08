
#include <SFML/Graphics.hpp>
#include <iostream>
#include "hud.h"
#include <string>

class juego
{
public:
    juego();
    ~juego();

    void gameloop();
    void procesareventos();
    void render();
    void cargar_hud();

private:
    sf::RenderWindow *window;

    hud *hud_principal;

    sf::Event *evento;

};
