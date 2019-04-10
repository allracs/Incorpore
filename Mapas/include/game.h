#include <SFML/Graphics.hpp>
#include <iostream>
#include "player.h"
#include "hud.h"
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
        void cargarHUD();
        void procesarEventos();
        void setView();
        void mostrarMapaColisiones();
        void procesarColisiones();
        void setColisions();
        View getView();

        int* dimensiones;
    private:
        RenderWindow *window;
        player *jugador;
        Event *evento;
        mapa *Mapa;
        hud *hud_principal;
        View view;
        FloatRect* colisiones;

};
