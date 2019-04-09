#include <SFML/Graphics.hpp>
#include <iostream>
#include "player.h"
#include "mapa.h"

using namespace sf;

class game
{
    public:
        game();
        void gameLoop();
        void render();
        void cargaPlayer();
        void cargaMapa();
        void procesarEventos();
        void setView();
        void mostrarMapaColisiones();
        void procesarColisiones();
        void setColisions();
    private:
        RenderWindow *window;
        player *jugador;
        Event *evento;
        mapa *Mapa;
        View view;
        FloatRect* colisiones;

};
