#include <SFML/Graphics.hpp>
#include <iostream>
#include "player.h"

using namespace sf;

class game
{
    public:
        game();
        void gameLoop();
        void render();
        void cargaPlayer();
    private:
        RenderWindow *window;
        player *jugador;

};
